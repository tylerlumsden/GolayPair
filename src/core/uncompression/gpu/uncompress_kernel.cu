#include <vector>
#include <map>
#include <span>
#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <format>
#include <functional>
#include <stdexcept>
#include <string>

#include <thrust/device_vector.h>
#include <cuda/std/mdspan>
#include <cuda/std/span>
#include <cufft.h>

#include "uncompress_kernel.h"

void check_cuda_error(cudaError_t err) {
  if(err != cudaSuccess) {
    throw std::runtime_error("CUDA malloc failed: " + std::string(cudaGetErrorString(err)));
  }
}

using SeqVal = float;
using Fourier = cuComplex;

using PermSpan = cuda::std::mdspan <
  int,
  cuda::std::extents<
    int,
    cuda::std::dynamic_extent,
    cuda::std::dynamic_extent
    >
>;

using Perm = cuda::std::span<int>;

class FlatPermView {
  int* indexes;
  int indexes_size;

  int* data;
  int data_size;

  int permutation_size;

  public:
    // TODO: correctly return error if key is invalid
    // Actually maybe have a separate .contains(key) func and let this return garbage
    __device__ __host__
    PermSpan operator[](int i) const {
      int index = indexes[i];
      int size;
      if(i == indexes_size - 1) {
        size = data_size - indexes[i];
      } else {
        size = indexes[i + 1] - indexes[i];
      }
      return PermSpan(&data[index], size / permutation_size, permutation_size);
    } 

    FlatPermView(
      int* indexes,
      int indexes_size,
      int* data,
      int data_size,
      int permutation_size
    ) : 
      indexes(indexes),
      indexes_size(indexes_size),
      data(data),
      data_size(data_size),
      permutation_size(permutation_size) {}
};

// Store a list of indexes, where indexes[i] is the index which the value of the ith key is stored.
// If the ith key does not exist, indexes[i] = -1.

// If you construct this with any empty data I will kill you
class FlatPermList {
  int *indexes;
  int indexes_size;

  int *data;
  int data_size;

  int permutation_size;
  
  public:
    __device__ __host__
    int size() const {
      return indexes_size;
    }

    __host__ 
    FlatPermList(const PermList& list, const std::vector<int>& input_seq) {
      permutation_size = list[0][0].size();

      std::vector<int> host_indexes;
      std::vector<int> host_data;

      int running_index = 0;
      for(auto sublist : list) {
        host_indexes.push_back(running_index);
        running_index += sublist.size() * permutation_size;
        for(auto permutation : sublist) {
          for(int num : permutation) {
            host_data.push_back(num);
          }
        }
      }

      indexes_size = host_indexes.size();
      data_size = host_data.size();
      check_cuda_error(cudaMalloc(&indexes, host_indexes.size() * sizeof(int)));
      check_cuda_error(cudaMalloc(&data, host_data.size() * sizeof(int)));

      cudaMemcpy(indexes, host_indexes.data(), host_indexes.size() * sizeof(int), cudaMemcpyHostToDevice);
      cudaMemcpy(data, host_data.data(), host_data.size() * sizeof(int), cudaMemcpyHostToDevice);
    }

    FlatPermView view() {
      return FlatPermView(indexes, indexes_size, data, data_size, permutation_size);
    }

    ~FlatPermList() {
      cudaFree(indexes);
      cudaFree(data);
    }
};

using MixedRadix = cuda::std::span<int>;
class MixedRadixView {
  int* num_pool;
  int* base_num;
  int* radices;
  int digits;

  public:

    __host__ __device__
    MixedRadixView(int* num_pool, int* base_num, int* radices, int digits)
      : num_pool(num_pool), base_num(base_num), radices(radices), digits(digits) {}

    __host__ __device__
    MixedRadix operator[](uint64_t i) const { 
      return MixedRadix(&num_pool[i * digits], digits);
    }

    __device__
    void init(uint64_t thread_id) {
      MixedRadix slot = (*this)[thread_id]; 
      for(int i = 0; i < digits; ++i) {
        slot[i] = base_num[i];
      }

      uint64_t carry = thread_id;
      for (int i = digits - 1; i >= 0 && carry; i--) {
        uint64_t sum = slot[i] + carry;
        slot[i] = sum % radices[i];
        carry = sum / radices[i];
      }
    }
};

class MixedRadixPool {
  int* num_pool;
  int* base_num;
  int* d_radices;
  int digits;

  std::vector<int> host_radices;

  public:
    __host__
    MixedRadixPool(const std::vector<int>& input_radices, uint64_t num_threads) {
      digits = input_radices.size();
      check_cuda_error(cudaMalloc(&d_radices, digits * sizeof(int)));
      check_cuda_error(cudaMalloc(&base_num, digits * sizeof(int)));
      check_cuda_error(cudaMalloc(&num_pool, num_threads * digits * sizeof(int)));

      check_cuda_error(cudaMemcpy(d_radices, input_radices.data(), digits * sizeof(int), cudaMemcpyHostToDevice));
      host_radices = input_radices;

      std::vector<int> zeros(digits, 0);
      set_base(zeros);
    }

    __host__
    void set_base(const std::vector<int>& mixed_base) {
      check_cuda_error(cudaMemcpy(base_num, mixed_base.data(), digits * sizeof(int), cudaMemcpyHostToDevice));
    }

    const std::vector<int>& radices() const {
      return host_radices;
    }

    __host__ __device__
    MixedRadixView view() {
      return MixedRadixView(num_pool, base_num, d_radices, digits);
    }

    ~MixedRadixPool() {
      cudaFree(num_pool);
      cudaFree(base_num);
      cudaFree(d_radices);
    }
};

__host__ __device__
Perm get_permutation(PermSpan perm_list, int i) {
  auto row = cuda::std::submdspan(perm_list, i, cuda::std::full_extent);

  return Perm(row.data_handle(), row.size());
}

template <typename T>
struct SequenceView {
  T* values;
  size_t length;
  size_t stride;

  __host__ __device__
  SequenceView(T* v, size_t len, size_t stride) :
    values(v), length(len), stride(stride) {} 

  __host__  __device__
  T& operator[](size_t index) {
    return values[index * stride];
  }

  __host__ __device__
  size_t size() {
    return length;
  }
};

template <typename T>
struct CoalescedView {
  T* values;
  size_t length;
  size_t batch_size;

  __host__
  CoalescedView(T* v, size_t len, size_t batch) :
    values(v), length(len), batch_size(batch) {}
  
  __host__ __device__
  SequenceView<T> operator[](size_t thread_id) {
    return SequenceView(values + thread_id, length, batch_size);
  }
};

template <typename T>
struct CoalescedMemoryPool {
  thrust::device_vector<T> values;
  size_t length;
  size_t batch_size;

  __host__
  CoalescedMemoryPool(size_t len, size_t num_threads) : 
    values(len * num_threads), length(len), batch_size(num_threads) {}

  CoalescedView<T> view() {
    return CoalescedView(thrust::raw_pointer_cast(values.data()), length, batch_size);
  }

  size_t bytes() {
    return length * batch_size * sizeof(T);
  }

  static size_t items_storable(std::size_t len, std::size_t total_bytes) {
    return total_bytes / (len * sizeof(T));
  }
};

struct GPUFourier {
  private:
    cufftHandle plan;
    void* input_ptr = nullptr;
    void* output_ptr = nullptr;

  public:

    void launch_batch() {
      auto result = cufftExecR2C(
          plan,
          reinterpret_cast<cufftReal*>(input_ptr),
          reinterpret_cast<cufftComplex*>(output_ptr)
      );
      if (result != CUFFT_SUCCESS) {
          throw std::runtime_error(std::format("cuFFT launch failed: {}\n", static_cast<int>(result)));
      }
    }

    GPUFourier(CoalescedMemoryPool<SeqVal>& input_pool, CoalescedMemoryPool<Fourier>& output_pool) {
      input_ptr  = thrust::raw_pointer_cast(input_pool.values.data());
      output_ptr = thrust::raw_pointer_cast(output_pool.values.data());

      int n[]     = { (int)input_pool.length };
      int batch   = (int)input_pool.batch_size;

      int istride = batch;   // stride between real input elements of same sequence
      int idist   = 1;       // stride between sequence starts
      int ostride = batch;   // stride between complex output elements of same sequence
      int odist   = 1;

      auto result = cufftPlanMany(
          &plan,
          1, n,              // 1D FFT of length n[0]
          n, istride, idist, // input layout (real)
          n, ostride, odist, // output layout (complex)
          CUFFT_R2C,
          batch
      );
      if (result != CUFFT_SUCCESS) {
          throw std::runtime_error(std::format("cuFFT plan failed: {}\n", static_cast<int>(result)));
      }
    }

    GPUFourier(const GPUFourier&) = delete;

    ~GPUFourier() {
      cufftDestroy(plan);
    }
};

// TODO: Instead of outputting an entire copy of the filtered sequences,
// We could write a bitmap of the sequences which pass the filter
__global__
void sequence_filter(
  CoalescedView<SeqVal> input_seq, 
  CoalescedView<SeqVal> filtered_seq,
  CoalescedView<Fourier> input_fourier,
  CoalescedView<Fourier> filtered_fourier,
  size_t* counter,
  int order,
  int paf_constant
) {
  uint64_t thread_id = blockIdx.x * blockDim.x + threadIdx.x;

  SequenceView<SeqVal> local_seq = input_seq[thread_id];
  SequenceView<Fourier> local_fourier = input_fourier[thread_id];

  // Filtering logic
  for(size_t i = 1; i <= local_seq.size() / 2; ++i) {
    float real_squared = local_fourier[i].x * local_fourier[i].x;
    float imag_squared = local_fourier[i].y * local_fourier[i].y;
    float psd = real_squared + imag_squared;

    local_fourier[i].x = psd;

    if(psd > 2 * order - paf_constant + 0.001) {
      return;
    }
  }

  // The local sequence has passed the filter
  size_t next_buffer = atomicAdd((unsigned long long*)counter, 1);
  SequenceView<SeqVal> write_seq = filtered_seq[next_buffer];
  SequenceView<Fourier> write_fourier = filtered_fourier[next_buffer];
  for(size_t i = 0; i < write_seq.size(); ++i) {
    write_seq[i] = local_seq[i];
    write_fourier[i] = local_fourier[i];
  }
}

__global__
void cartesian_product(
  FlatPermView permutations, 
  MixedRadixView radi, 
  CoalescedView<SeqVal> output
) {
  uint64_t threadId = blockIdx.x * blockDim.x + threadIdx.x;

  radi.init(threadId);
  MixedRadix local_radix = radi[threadId];

  SequenceView<SeqVal> local_seq = output[threadId];

  for(int i = 0; i < local_radix.size(); ++i) {
    auto perm = get_permutation(permutations[i], local_radix[i]);

    for(size_t j = 0; j < perm.size(); ++j) {
      local_seq[i + (local_radix.size() * j)] = perm[j];
    }
  }
}

void print_vram() {
  std::size_t free_mem, total_mem;
  cudaMemGetInfo(&free_mem, &total_mem);

  printf("Free:  %.2f GB\n", free_mem  / 1e9);
  printf("Total: %.2f GB\n", total_mem / 1e9);
  printf("Used:  %.2f GB\n", (total_mem - free_mem) / 1e9);
}

struct UncompressKernel::Impl {
  FlatPermList                 flat_perm_list;
  MixedRadixPool               rad_pool;
  CoalescedMemoryPool<SeqVal>  seq_pool;
  CoalescedMemoryPool<Fourier> psd_pool;
  CoalescedMemoryPool<SeqVal>  seq_filtered;
  CoalescedMemoryPool<Fourier> psd_filtered;
  GPUFourier                   fft;

  Impl(PermList& permutations, const std::vector<int>& seq,
       size_t new_length, size_t items_per_iter, const std::vector<int>& radices)
    : flat_perm_list(permutations, seq)
    , rad_pool(radices, items_per_iter)
    , seq_pool(new_length, items_per_iter)
    , psd_pool(new_length, items_per_iter)
    , seq_filtered(new_length, items_per_iter)
    , psd_filtered(new_length, items_per_iter)
    , fft(seq_pool, psd_pool)
  {}
};

UncompressKernel::UncompressKernel(PermList& permutations, const std::vector<int>& seq,
                                   size_t new_length, size_t items_per_iter) {
  std::vector<int> radices;
  for(auto list : permutations) {
    radices.push_back(list.size());
  }
  impl = std::make_unique<Impl>(permutations, seq, new_length, items_per_iter, radices);
}

UncompressKernel::~UncompressKernel() = default;

const std::vector<int>& UncompressKernel::radices() const {
  return impl->rad_pool.radices();
}

size_t UncompressKernel::items_per_iter() const {
  return impl->seq_pool.batch_size;
}

void UncompressKernel::set_offset(const std::vector<int>& mixed_radix) {
  impl->rad_pool.set_base(mixed_radix);
}

void UncompressKernel::launch_cartesian_product(size_t blocks, size_t threads) {
  cartesian_product<<<blocks, threads>>>(
    impl->flat_perm_list.view(),
    impl->rad_pool.view(),
    impl->seq_pool.view()
  );
  check_cuda_error(cudaDeviceSynchronize());
}

void UncompressKernel::launch_fft() {
  impl->fft.launch_batch();
  check_cuda_error(cudaDeviceSynchronize());
}

size_t UncompressKernel::launch_sequence_filter(size_t blocks, size_t threads,
                                                 int order, int paf_constant) {
  // Initialize a device vector containing one counter element
  // We do this so that we can pass a raw pointer to the kernel but with RAII on the host side
  thrust::device_vector<size_t> counter(1, 0);
  sequence_filter<<<blocks, threads>>>(
    impl->seq_pool.view(),
    impl->seq_filtered.view(),
    impl->psd_pool.view(),
    impl->psd_filtered.view(),
    thrust::raw_pointer_cast(counter.data()),
    order,
    paf_constant
  );
  check_cuda_error(cudaDeviceSynchronize());
  return counter[0];
}

void UncompressKernel::write_filtered(size_t count,
                                       std::function<void(std::span<int>, std::span<double>)> writer) {
  //printf("Copying sequence data\n");
  // Repack from coalesced layout (values[seq_idx + elem_idx * batch_size])
  // into packed layout (values[seq_idx * length + elem_idx]) for the writer.
  auto seq_raw = thrust::raw_pointer_cast(impl->seq_filtered.values.data());
  size_t seq_batch = impl->seq_filtered.batch_size;
  size_t seq_len   = impl->seq_filtered.length;
  thrust::device_vector<int> int_vals(count * seq_len);
  thrust::transform(
      thrust::make_counting_iterator<size_t>(0),
      thrust::make_counting_iterator<size_t>(count * seq_len),
      int_vals.begin(),
      [seq_raw, seq_batch, seq_len] __device__ (size_t k) {
          size_t seq_idx  = k / seq_len;
          size_t elem_idx = k % seq_len;
          return static_cast<int>(seq_raw[seq_idx + elem_idx * seq_batch]);
      }
  );
  std::vector<int> flat_sequences(count * seq_len);
  thrust::copy(int_vals.begin(), int_vals.end(), flat_sequences.begin());

  printf("Copying PSD data\n");
  auto psd_raw = thrust::raw_pointer_cast(impl->psd_filtered.values.data());
  size_t psd_batch = impl->psd_filtered.batch_size;
  size_t psd_len   = impl->psd_filtered.length;
  thrust::device_vector<float> psd_device(count * psd_len);
  thrust::transform(
      thrust::make_counting_iterator<size_t>(0),
      thrust::make_counting_iterator<size_t>(count * psd_len),
      psd_device.begin(),
      [psd_raw, psd_batch, psd_len] __device__ (size_t k) {
          size_t seq_idx  = k / psd_len;
          size_t elem_idx = k % psd_len;
          return psd_raw[seq_idx + elem_idx * psd_batch].x;
      }
  );
  std::vector<double> psds(count * psd_len);
  thrust::copy(psd_device.begin(), psd_device.end(), psds.begin());

  //printf("Writing sequence data\n");
  for(size_t i = 0; i < count; ++i) {
    writer(
      std::span<int>(&flat_sequences[i * seq_len], seq_len),
      std::span<double>(&psds[i * psd_len], psd_len / 2)
    );
  }
}