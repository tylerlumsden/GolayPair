#include <vector>
#include <span>
#include <cstdio>
#include <cstdint>
#include <format>
#include <functional>
#include <stdexcept>

#include <thrust/device_vector.h>
#include <cuda/std/mdspan>
#include <cuda_error.h>
#include <view_types.h>

#include "uncompress_kernel_impl.h"

using Perm = cuda::std::span<int>;

__host__ __device__
Perm get_permutation(PermSpan perm_list, int i) {
    auto row = cuda::std::submdspan(perm_list, i, cuda::std::full_extent);
    return Perm(row.data_handle(), row.size());
}

__global__
void cartesian_product(FlatPermList::View permutations,
                       MixedRadixPool::View radi,
                       SequencePool::View output)
{
    uint64_t threadId = blockIdx.x * blockDim.x + threadIdx.x;
    radi.init(threadId);
    MixedRadix local_radix = radi[threadId];
    SequenceView<float> local_seq = output[threadId];
    for(int i = 0; i < local_radix.size(); ++i) {
        auto perm = get_permutation(permutations[i], local_radix[i]);
        for(size_t j = 0; j < perm.size(); ++j)
            local_seq[i + (local_radix.size() * j)] = perm[j];
    }
}

__global__
void sequence_filter(SequencePool::View  input_seq,
                     SequencePool::View  filtered_seq,
                     FourierPool::View   input_fourier,
                     FourierPool::View   filtered_fourier,
                     size_t*             counter,
                     int                 order,
                     int                 paf_constant)
{
    uint64_t thread_id = blockIdx.x * blockDim.x + threadIdx.x;
    SequenceView<float>    local_seq     = input_seq[thread_id];
    SequenceView<cuComplex> local_fourier = input_fourier[thread_id];

    for(size_t i = 1; i <= local_seq.size() / 2; ++i) {
        float psd = local_fourier[i].x * local_fourier[i].x
                  + local_fourier[i].y * local_fourier[i].y;
        local_fourier[i].x = psd;
        if(psd > 2 * order - paf_constant + 0.001f) return;
    }

    size_t next_buffer = atomicAdd((unsigned long long*)counter, 1);
    SequenceView<float>    write_seq     = filtered_seq[next_buffer];
    SequenceView<cuComplex> write_fourier = filtered_fourier[next_buffer];
    for(size_t i = 0; i < write_seq.size(); ++i) {
        write_seq[i]     = local_seq[i];
        write_fourier[i] = local_fourier[i];
    }
}

static std::vector<int> repack_sequences(float* raw, size_t batch, size_t len, size_t count) {
    thrust::device_vector<int> d(count * len);
    thrust::transform(
        thrust::make_counting_iterator<size_t>(0),
        thrust::make_counting_iterator<size_t>(count * len),
        d.begin(),
        [raw, batch, len] __device__ (size_t k) {
            return static_cast<int>(raw[k / len + (k % len) * batch]);
        }
    );
    std::vector<int> h(count * len);
    thrust::copy(d.begin(), d.end(), h.begin());
    return h;
}

static std::vector<float> repack_psds(cuComplex* raw, size_t batch, size_t len, size_t count) {
    thrust::device_vector<float> d(count * len);
    thrust::transform(
        thrust::make_counting_iterator<size_t>(0),
        thrust::make_counting_iterator<size_t>(count * len),
        d.begin(),
        [raw, batch, len] __device__ (size_t k) {
            return raw[k / len + (k % len) * batch].x;
        }
    );
    std::vector<float> h(count * len);
    thrust::copy(d.begin(), d.end(), h.begin());
    return h;
}

// ---- UncompressKernel::Impl ----

UncompressKernel::Impl::Impl(PermList& permutations, size_t new_length, size_t items_per_iter,
                               const std::vector<int>& radices, int order, int paf_constant)
    : flat_perm_list(permutations)
    , rad_pool(radices, items_per_iter)
    , seq_pool(new_length, items_per_iter)
    , psd_pool(new_length, items_per_iter)
    , seq_filtered(new_length, items_per_iter)
    , psd_filtered(new_length, items_per_iter)
    , fft(seq_pool, psd_pool)
    , order(order)
    , paf_constant(paf_constant)
{}

UncompressKernel::Impl::~Impl() = default;

size_t UncompressKernel::Impl::execute_batch(
    const std::vector<int>& mixed_radix, size_t blocks, size_t threads,
    const std::function<void(std::span<int>, std::span<double>)>& writer)
{
    rad_pool.set_base(mixed_radix);

    cartesian_product<<<blocks, threads>>>(
        flat_perm_list.get_view(),
        rad_pool.get_view(),
        seq_pool.get_view()
    );
    check_cuda_error(cudaDeviceSynchronize());

    fft.launch_batch();
    check_cuda_error(cudaDeviceSynchronize());

    thrust::device_vector<size_t> counter(1, 0);
    sequence_filter<<<blocks, threads>>>(
        seq_pool.get_view(),
        seq_filtered.get_view(),
        psd_pool.get_view(),
        psd_filtered.get_view(),
        thrust::raw_pointer_cast(counter.data()),
        order, paf_constant
    );
    check_cuda_error(cudaDeviceSynchronize());
    size_t count = counter[0];

    std::vector<int> flat_sequences = repack_sequences(
        seq_filtered.device_data(),
        seq_filtered.batch_size(),
        seq_filtered.length(),
        count
    );
    std::vector<float> psds_f = repack_psds(
        reinterpret_cast<cuComplex*>(psd_filtered.device_data()),
        psd_filtered.batch_size(),
        psd_filtered.length(),
        count
    );
    std::vector<double> psds(psds_f.begin(), psds_f.end());

    size_t seq_len = seq_filtered.length();
    size_t psd_len = psd_filtered.length();
    for(size_t i = 0; i < count; ++i) {
        writer(
            std::span<int>   (&flat_sequences[i * seq_len], seq_len),
            std::span<double>(&psds[i * psd_len], psd_len / 2)
        );
    }

    return count;
}

// ---- UncompressKernel ----

UncompressKernel::UncompressKernel(PermList& permutations, int compress, int new_compress,
                                    int order, int paf_constant) {
    size_t new_length = order / new_compress;
    std::vector<int> radices;
    for(auto& list : permutations) radices.push_back(list.size());

    std::size_t free_mem, total_mem;
    cudaMemGetInfo(&free_mem, &total_mem);
    size_t items_per_iter = (free_mem / 256) / (new_length * sizeof(float));

    impl = std::make_unique<Impl>(permutations, new_length, items_per_iter, radices, order, paf_constant);
}

UncompressKernel::~UncompressKernel() = default;
