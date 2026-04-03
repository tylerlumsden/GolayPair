#include <vector>
#include <map>
#include <span>
#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <format>
#include <functional>

#include <boost/multiprecision/cpp_int.hpp>
#include <thrust/device_vector.h>
#include <cuda/std/mdspan>
#include <cuda/std/span>

#include "vkFFT.h"
#include "io.h"

void check_cuda_error(cudaError_t err) {
  if(err != cudaSuccess) {
    throw std::runtime_error("CUDA malloc failed: " + std::string(cudaGetErrorString(err)));
  }
}

using SeqVal = float;
using Fourier = cuComplex;

using BigInt = boost::multiprecision::cpp_int;

using PermMap = std::map<
  int,
  std::vector<std::vector<int>>
>;

using PermList = std::vector<
  std::vector<std::vector<int>>
>;

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
    FlatPermList(const PermMap& input_map, const std::vector<int>& input_seq) {
      PermList list;
      for(int num : input_seq) {
        list.push_back(input_map.at(num));
      }

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
  int* radices;
  int digits;

  std::vector<int> host_radices;

  public:
    __host__
    MixedRadixPool(const std::vector<int>& input_radices, uint64_t num_threads, BigInt base = 0) {
      digits = input_radices.size();
      check_cuda_error(cudaMalloc(&radices, digits * sizeof(int)));
      check_cuda_error(cudaMalloc(&base_num, digits * sizeof(int)));
      check_cuda_error(cudaMalloc(&num_pool, num_threads * digits * sizeof(int)));

      check_cuda_error(cudaMemcpy(radices, input_radices.data(), digits * sizeof(int), cudaMemcpyHostToDevice));
      host_radices = input_radices;

      set_base(base);
    }

    __host__
    void set_base(BigInt base) {
      std::vector<int> mixed_base(digits);
      for(int i = digits - 1; i >= 0; --i) {
        mixed_base[i] = static_cast<int>(base % host_radices[i]);
        base /= host_radices[i];
      }
      check_cuda_error(cudaMemcpy(base_num, mixed_base.data(), digits * sizeof(int), cudaMemcpyHostToDevice));
    } 
    __host__ __device__
    MixedRadixView view() {
      return MixedRadixView(num_pool, base_num, radices, digits);
    }

    ~MixedRadixPool() {
      cudaFree(num_pool);
      cudaFree(base_num);
      cudaFree(radices);
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
  size_t stride;

  __host__
  CoalescedView(T* v, size_t len, size_t batch, size_t stride) :
    values(v), length(len), batch_size(batch), stride(stride) {}
  
  __host__ __device__
  SequenceView<T> operator[](size_t thread_id) {
    return SequenceView(values + thread_id * (length / stride), length, stride);
  }
};

template <typename T>
struct CoalescedMemoryPool {
  thrust::device_vector<T> values;
  size_t length;
  size_t batch_size;
  size_t stride;

  __host__
  CoalescedMemoryPool(size_t len, size_t num_threads, size_t stride) : 
    values(len * num_threads), length(len), batch_size(num_threads), stride(stride) {}

  CoalescedView<T> view() {
    return CoalescedView(thrust::raw_pointer_cast(values.data()), length, batch_size, stride);
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
    size_t in_bytes;
    size_t out_bytes;
    size_t work_bytes;
    void* work_buffer = nullptr;
    void* input_ptr = nullptr;
    void* output_ptr = nullptr;
    int device = 0;

  public:

    VkFFTApplication app = {};

    void launch_batch() {
      // --- Launch Parameters ---
      VkFFTLaunchParams launchParams = {};

      // --- Forward FFT (in-place) ---
      // inverse = 0 → forward FFT
      // inverse = 1 → inverse FFT
      auto result = VkFFTAppend(&app, 0, &launchParams);
      if (result != VKFFT_SUCCESS) {
          printf("VkFFT launch failed: %d\n", result);
          throw std::runtime_error(std::format("VkFFT launch failed: {}\n", static_cast<int>(result)));
      }
    }

    GPUFourier(CoalescedMemoryPool<SeqVal>& input_pool, CoalescedMemoryPool<Fourier>& output_pool) {
      // --- VkFFT Application Config ---
      VkFFTConfiguration config = {};
      config.FFTdim      = 1;           // 1D FFT
      config.size[0]     = input_pool.length;           // Sequence length
      config.numberBatches = input_pool.batch_size; // Number of sequences
      config.inputBufferStride[0] = input_pool.stride;
      config.inputBufferStride[1] = input_pool.length / input_pool.stride;

      config.outputBufferStride[0] = output_pool.stride;
      config.outputBufferStride[1] = output_pool.length / output_pool.stride;

      config.isInputFormatted = 1;
      config.isOutputFormatted = 1;
https://www.youtube.com/watch?v=4QToz2SM2mM&t=1721s
      // Target CUDA
      config.performR2C  = 1;           // 0 = complex-to-complex; 1 = real-to-complex
      config.device      = &device;  // CUDA device index

      // Separate working buffer for VkFFT's internal in-place FFT
      work_bytes = (input_pool.length / 2 + 1) * input_pool.batch_size * sizeof(cuComplex);
      check_cuda_error(cudaMalloc(&work_buffer, work_bytes));
      config.bufferSize = &work_bytes;
      config.buffer     = &work_buffer;

      // Store raw device pointers so VkFFT gets valid void** targets
      input_ptr  = thrust::raw_pointer_cast(input_pool.values.data());
      output_ptr = thrust::raw_pointer_cast(output_pool.values.data());

      in_bytes = input_pool.bytes();
      config.inputBufferSize  = &in_bytes;
      config.inputBuffer = &input_ptr;

      out_bytes = output_pool.bytes();
      config.outputBufferSize = &out_bytes;
      config.outputBuffer = &output_ptr;

      // --- Initialize VkFFT ---
      VkFFTResult result = initializeVkFFT(&app, config);
      if (result != VKFFT_SUCCESS) {
          throw std::runtime_error(std::format("VkFFT init failed: {}\n", static_cast<int>(result)));
      }
    }

    GPUFourier(const GPUFourier&) = delete;

    ~GPUFourier() {
      deleteVkFFT(&app);
      cudaFree(work_buffer);
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

    printf("%f\n", psd);

    if(psd > 2 * order - paf_constant) {
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

void uncompress_kernel(
  std::vector<int> seq, 
  PermMap permutations, 
  size_t new_length, 
  int order, 
  int paf_constant,
  std::function<void(std::span<int>, std::span<double>)> writer
) {   
  size_t seq_length = seq.size();

  FlatPermList flat_perm_list(permutations, seq);

  std::vector<int> radices;
  for(int num : seq) {
    radices.push_back(permutations[num].size());
  }

  BigInt count = 1;
  for(int num : radices) {
    count *= num;
  }

  printf("Pre-allocation VRAM:\n");
  print_vram();

  std::size_t free_mem, total_mem;
  cudaMemGetInfo(&free_mem, &total_mem);

  // TODO: free_mem division should be designated somewhere else
  size_t items_per_iter = static_cast<size_t>(
    std::min(count, static_cast<BigInt>(CoalescedMemoryPool<float>::items_storable(seq_length, free_mem / 128)))
  );

  MixedRadixPool rad_pool(radices, items_per_iter);
  CoalescedMemoryPool<SeqVal> seq_pool(new_length, items_per_iter, 1);
  CoalescedMemoryPool<Fourier> psd_pool(new_length, items_per_iter, 1);

  CoalescedMemoryPool<SeqVal> seq_filtered(new_length, items_per_iter, 1);
  CoalescedMemoryPool<Fourier> psd_filtered(new_length, items_per_iter, 1);

  GPUFourier fft(seq_pool, psd_pool);

  printf("Post-allocation VRAM, %lu sequences allocated:\n", items_per_iter);
  print_vram();

  size_t filtered_count = 0;
  printf("Uncompressing with a count of: %s\n", count.str().c_str());
  for(BigInt offset = 0; offset < count;) {
    printf("Current offset: %s\n", offset.str().c_str());
    
    rad_pool.set_base(offset);
    BigInt remaining = count - offset;

    // TODO: refactor... ugly if else chain
    std::size_t threads_per_block, num_blocks;
    if(remaining < items_per_iter) {
      if(remaining < 256) {
        threads_per_block = static_cast<int>(remaining);
        num_blocks = 1;
      } else {
        threads_per_block = std::min(static_cast<std::size_t>(256), items_per_iter);
        num_blocks = static_cast<std::size_t>(remaining / static_cast<BigInt>(threads_per_block));
      } 
    } else {
      threads_per_block = std::min(static_cast<std::size_t>(256), items_per_iter);
      num_blocks = static_cast<std::size_t>(items_per_iter / threads_per_block);
    }
    std::size_t num_threads = num_blocks * threads_per_block;
    std::cout << "num_threads: " << num_threads << "\n";

    printf("Launching cartesian product\n");
    cartesian_product<<<num_blocks, threads_per_block>>>(
      flat_perm_list.view(), 
      rad_pool.view(), 
      seq_pool.view()
    );
    check_cuda_error(cudaDeviceSynchronize());

    printf("Launching FFT batch\n");
    fft.launch_batch();
    check_cuda_error(cudaDeviceSynchronize());

    printf("Filtering batch\n");
    
    // Initialize a device vector containing one counter element
    // We do this so that we can pass a raw pointer to the kernel but with RAII on the host side
    thrust::device_vector<size_t> counter(1, 0);
    sequence_filter<<<num_blocks, threads_per_block>>>(
      seq_pool.view(), 
      seq_filtered.view(), 
      psd_pool.view(),
      psd_filtered.view(),
      thrust::raw_pointer_cast(counter.data()),
      order,
      paf_constant
    );
    check_cuda_error(cudaDeviceSynchronize());

    size_t count = counter[0];
    filtered_count += count;

    printf("Filtered count: %lu\n", count);

    std::vector<float> filtered_values(count * new_length);
    thrust::copy(
        seq_pool.values.begin(),
        seq_pool.values.begin() + count * new_length,
        filtered_values.begin()
    );

    std::vector<cuComplex> filtered_fourier(count * new_length);
    thrust::copy(
        psd_pool.values.begin(),
        psd_pool.values.begin() + count * new_length,
        filtered_fourier.begin()
    );

    printf("Copying sequence data\n");
    thrust::device_vector<int> int_vals(count * new_length);
    thrust::transform(
        seq_filtered.values.begin(),
        seq_filtered.values.begin() + count * new_length,
        int_vals.begin(),
        [] __device__ (SeqVal f) { return static_cast<int>(f); }
    );
    std::vector<int> flat_sequences(count * new_length);
    thrust::copy(int_vals.begin(), int_vals.end(), flat_sequences.begin());

    printf("Copying PSD data\n");
    thrust::device_vector<float> psd_device(count * new_length);
    thrust::transform(
        psd_filtered.values.begin(),
        psd_filtered.values.begin() + count * new_length,
        psd_device.begin(),
        [] __device__ (cuComplex c) { return c.x; }
    );
    std::vector<double> psds(count * new_length);
    thrust::copy(psd_device.begin(), psd_device.end(), psds.begin());
    
    printf("Writing sequence data\n");
    for(size_t i = 0; i < count; ++i) {
      writer(
        std::span<int>(&flat_sequences[i], seq_filtered.length),
        std::span<double>(&psds[i], seq_filtered.length / 2)
      );
    }

    offset += num_threads;
  }

  printf("Done uncompressing, total output: %lu\n", filtered_count);
}