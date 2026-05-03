#include <cstdio>
#include <vector>
#include <cuda_runtime.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <stdexcept>
#include <format>

#include "uncompress_kernel.h"
#include "cuda_error.h"
#include "flat_perm_list.h"
#include "jit_headers.h"
#include "memorypool.h"

const std::string program = R"(

// Compile time variables:
// FFT_SIZE
// COMPRESS
// NEWCOMPRESS
// SM_ARCH

#include "view_types.h"
#include "cufftdx.hpp"
#include <cuda/std/span>

using namespace cufftdx;

using FFT_base = decltype(
    Size<FFT_SIZE>() + Type<fft_type::r2c>() +
    Precision<float>() + SM<SM_ARCH>() + Block()
);

using FFT = decltype(FFT_base() + FFTsPerBlock<FFT_base::suggested_ffts_per_block>());

__device__ constexpr decltype(FFT::block_dim) fft_block_dim    = FFT::block_dim;
__device__ constexpr unsigned int fft_shared_mem         = (unsigned int)FFT::shared_memory_size;
__device__ constexpr unsigned int fft_suggested_ffts     = FFT::suggested_ffts_per_block;

__device__ constexpr unsigned int new_length = FFT_SIZE;
__device__ constexpr unsigned int length = FFT_SIZE / (COMPRESS / NEWCOMPRESS);

__device__ constexpr float threshold = 2 * ORDER - PAFCONSTANT + 0.01;

__global__ void uncompress_kernel(
    int* base_radices,
    int* offset,
    FlatPermListData perm_data,
    float* output,
    int* input_output,
    unsigned int* output_count,
    unsigned int num_ffts
) {
    __shared__ int  radix_indexes[length * fft_suggested_ffts];
    extern __shared__ __align__(alignof(FFT::value_type)) FFT::value_type smem[];
    __shared__ bool         fft_passed[fft_suggested_ffts];
    __shared__ unsigned int out_indices[fft_suggested_ffts];

    cuda::std::span<int, length> base_view(base_radices, length);
    cuda::std::span<int, length> offset_view(offset, length);
    cuda::std::mdspan<int, cuda::std::extents<int, fft_suggested_ffts, length>> radices_view(radix_indexes);

    const unsigned int global_fft_id = blockIdx.x * fft_suggested_ffts + threadIdx.y;
    const unsigned int local_fft_id  = threadIdx.y;
    const unsigned int elements_id   = threadIdx.x;

    if (global_fft_id >= num_ffts) return;

    if(elements_id == 0) {
        int temp = global_fft_id;
        int carry = 0;
        for (int i = length - 1; i >= 0; i--) {
            int fft_digit = temp % base_view[i];
            temp /= base_view[i];
            int sum = offset_view[i] + fft_digit + carry;
            radices_view(local_fft_id, i) = sum % base_view[i];
            carry = sum / base_view[i];
        }
    }
    __syncthreads();

    FlatPermList::View permutations(perm_data);
    int input_data[new_length];
    FFT::value_type thread_data[FFT::storage_size];

    for (unsigned int i = 0; i < new_length; i++) {
        unsigned int idx = elements_id + i * FFT::block_dim.x;
        constexpr int stride = (new_length / (COMPRESS / NEWCOMPRESS));
        int list_index = idx % stride;
        int perm_index = idx / stride;
        input_data[i] = permutations[list_index](radices_view(local_fft_id, list_index), perm_index);
    }

    for (unsigned int i = 0; i < FFT::elements_per_thread; i++) {
        float re = (2*i     < new_length) ? (float)input_data[2*i]     : 0.0f;
        float im = (2*i + 1 < new_length) ? (float)input_data[2*i + 1] : 0.0f;
        thread_data[i] = FFT::value_type(re, im);
    }

    if (elements_id == 0) fft_passed[local_fft_id] = true;
    __syncthreads();

    FFT().execute(thread_data, smem);

    // Compute magnitude squared and check threshold
    float mag_sq[FFT::storage_size];
    bool local_pass = true;
    for (unsigned int i = 0; i < FFT::elements_per_thread; i++) {
        mag_sq[i] = thread_data[i].x * thread_data[i].x + thread_data[i].y * thread_data[i].y;
        if (mag_sq[i] >= threshold) local_pass = false;
    }

    if (!local_pass) fft_passed[local_fft_id] = false;
    __syncthreads();

    if (fft_passed[local_fft_id] && elements_id == 0)
        out_indices[local_fft_id] = atomicAdd(output_count, 1);
    __syncthreads();

    if (fft_passed[local_fft_id]) {
        unsigned int out_idx = out_indices[local_fft_id];
        for (unsigned int i = 0; i < FFT::elements_per_thread; i++) {
            unsigned int idx = elements_id + i * FFT::block_dim.x;
            output[out_idx * new_length + idx]       = mag_sq[i];
            input_output[out_idx * new_length + idx] = input_data[i];
        }
    }
}
)";

using BigInt = boost::multiprecision::cpp_int;

UncompressKernel::UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant)
    : order(order), compress(compress), new_compress(new_compress), paf_constant(paf_constant), permutations(permutations) {

    this->length = order / compress;
    this->new_length = order / new_compress;

    cudaFree(0);

    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);
    int sm_arch = prop.major * 100 + prop.minor * 10;

    static jitify2::ProgramCache<> cache(100, *jitify2::Program("uncompress_program", program,
        {{"flat_perm_list.h", flat_perm_list_jit},
         {"view_types.h", view_types_jit}})
        ->preprocess({
            "-I" + jitify2::get_cuda_include_dir(),
            "-I" + jitify2::get_cuda_include_dir() + "/cccl",
            "-I" + jit_third_party_dir,
            "-DFFT_SIZE=" + std::to_string(order / new_compress),
            "-DSM_ARCH=" + std::to_string(sm_arch),
            "-DORDER=" + std::to_string(order),
            "-DCOMPRESS=" + std::to_string(compress),
            "-DNEWCOMPRESS=" + std::to_string(new_compress),
            "-DPAFCONSTANT=" + std::to_string(paf_constant)
        }));

    this->kernel = cache.get_kernel("uncompress_kernel");

    dim3 block_dim;
    unsigned int shared_mem, suggested_ffts;
    this->kernel->program().get_global_value("fft_block_dim",      &block_dim);
    this->kernel->program().get_global_value("fft_shared_mem",     &shared_mem);
    this->kernel->program().get_global_value("fft_suggested_ffts", &suggested_ffts);
    cudaDeviceSynchronize();

    this->launch_params = {block_dim, shared_mem, suggested_ffts};
}

UncompressKernel::~UncompressKernel() {}

void UncompressKernel::run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer) {
    if(seq.size() != this->length) {
        throw std::invalid_argument(
            std::format("Compressed sequence length of {} is not equal to kernel length of {}", seq.size(), this->length)
        );
    }
    
    std::vector<int> radices;
    for (auto list : this->permutations) {
        radices.push_back(list.size());
    }

    BigInt search_count = 1;
    for (int num : radices) {
        search_count *= num;
    }
    std::cout << "Uncompression search space size: " << search_count << "\n";

    FlatPermList perm_list(this->permutations);

    size_t free_mem, total_mem;
    cudaMemGetInfo(&free_mem, &total_mem);

    constexpr size_t max_per_iter = 1000000;
    size_t items_per_iter = static_cast<size_t>(
        std::min(
            search_count,
            static_cast<BigInt>(std::min(
                MemoryPool<int>::items_storable(this->new_length, free_mem),
                max_per_iter
            ))
        )
    );

    printf("Iterating with %lu sequences per iteration\n", items_per_iter);

    MemoryPool<int>   radix_offset(1, this->length);
    MemoryPool<int>   base_radices(1, this->length);
    MemoryPool<float> output(items_per_iter, this->new_length);
    MemoryPool<int>   input_output(items_per_iter, this->new_length);

    unsigned int* output_count;
    check_cuda_error(cudaMalloc(&output_count, sizeof(unsigned int)));
    check_cuda_error(cudaMemset(output_count, 0, sizeof(unsigned int)));
    check_cuda_error(cudaMemcpy(base_radices.values, radices.data(), this->length * sizeof(int), cudaMemcpyHostToDevice));

    BigInt total_count = 0;

    for (BigInt offset = 0; offset < search_count; offset += items_per_iter) {
        std::cout << "Current Offset:" << offset << "\n";
        BigInt remaining = search_count - offset;
        size_t items_this_iter = static_cast<size_t>(std::min(remaining, static_cast<BigInt>(items_per_iter)));

        check_cuda_error(cudaMemset(output_count, 0, sizeof(unsigned int)));

        // Convert the current offset to the mixed radix form
        std::vector<int> offset_radix(this->length);
        BigInt temp_offset = offset;
        for (int i = this->length - 1; i >= 0; i--) {
            offset_radix[i] = static_cast<int>(temp_offset % radices[i]);
            temp_offset /= radices[i];
        }
        check_cuda_error(cudaMemcpy(radix_offset.values, offset_radix.data(), this->length * sizeof(int), cudaMemcpyHostToDevice));

        dim3 grid((items_this_iter + launch_params.ffts_per_block - 1) / launch_params.ffts_per_block);
        //printf( "block.x : %u, block.y: %u, block.z: %u\n", launch_params.block_dim.x, launch_params.block_dim.y, launch_params.block_dim.z);
        //printf("  grid: %u, ffts_per_block: %u\n", grid.x, launch_params.ffts_per_block);

        this->kernel
            ->configure(grid, launch_params.block_dim, launch_params.shared_mem)
            ->launch(base_radices.values, radix_offset.values, perm_list.data(), output.values, input_output.values, output_count, (unsigned int)items_this_iter);

        check_cuda_error(cudaDeviceSynchronize());

        unsigned int count;
        check_cuda_error(cudaMemcpy(&count, output_count, sizeof(unsigned int), cudaMemcpyDeviceToHost));
        total_count += count;

        if (count > 0) {
            std::vector<int>    h_input(count * this->new_length);
            std::vector<float>  h_output_f(count * this->new_length);
            std::vector<double> h_output(count * this->new_length);

            check_cuda_error(cudaMemcpy(h_input.data(),    input_output.values, count * this->new_length * sizeof(int),   cudaMemcpyDeviceToHost));
            check_cuda_error(cudaMemcpy(h_output_f.data(), output.values,        count * this->new_length * sizeof(float), cudaMemcpyDeviceToHost));

            std::transform(h_output_f.begin(), h_output_f.end(), h_output.begin(), [](float v) { return (double)v; });

            for (unsigned int i = 0; i < count; i++) {
                writer(
                    std::span<int>   (h_input.data()  + i * this->new_length, this->new_length),
                    std::span<double>(h_output.data() + i * this->new_length, this->new_length)
                );
            }
        }
    }

    std::cout << "Total passing sequences: " << total_count << "\n";

    check_cuda_error(cudaFree(output_count));
}
