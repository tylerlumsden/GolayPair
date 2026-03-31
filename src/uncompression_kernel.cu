#include <vector>
#include <map>
#include <span>
#include <cstdio>
#include <cstdint>
#include <algorithm>

#include <boost/multiprecision/cpp_int.hpp>
#include <thrust/device_vector.h>
#include <cuda/std/mdspan>
#include <cuda/std/span>

void check_cuda_error(cudaError_t err) {
  if(err != cudaSuccess) {
    throw std::runtime_error("CUDA malloc failed: " + std::string(cudaGetErrorString(err)));
  }
}

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

      check_cuda_error(cudaMemcpy(radices, input_radices.data(), digits, cudaMemcpyHostToDevice));
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
      check_cuda_error(cudaMemcpy(base_num, mixed_base.data(), digits, cudaMemcpyHostToDevice));
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

using SequenceView = cuda::std::span<int>;
class OutputView {
  int* values;
  size_t length;

  public: 
    __host__
    OutputView(int* v, size_t len) : values(v), length(len) {}

    __host__ __device__
    SequenceView operator[](uint64_t thread_id) {
      return SequenceView(&values[length * thread_id], length);
    }
};

class OutputPool {
  int* values;
  size_t length;

  public:
    __host__ 
    OutputPool(size_t len, uint64_t num_threads) : length(len) {
      check_cuda_error(cudaMalloc(&values, num_bytes(len, num_threads)));
    }

    OutputView view() {
      return OutputView(values, length);
    }

    static size_t num_bytes(size_t len, uint64_t num_threads) {
      return num_threads * len * sizeof(int);
    }

    static size_t items_storable(std::size_t len, std::size_t total_bytes) {
      return total_bytes / (len * sizeof(int));
    }

    ~OutputPool() {
      cudaFree(values);
    }
};

__global__
void cartesian_product(
  FlatPermView permutations, 
  MixedRadixView radi, 
  OutputView output
) {
  uint64_t threadId = blockIdx.x * blockDim.x + threadIdx.x;

  radi.init(threadId);
  MixedRadix local_radix = radi[threadId];

  SequenceView local_seq = output[threadId];

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

void uncompress_kernel(std::vector<int> seq, PermMap permutations, size_t new_length) {   
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
  size_t items_per_iter = static_cast<size_t>(std::min(count, static_cast<BigInt>(OutputPool::items_storable(seq_length, free_mem / 8))));

  MixedRadixPool rad_pool(radices, items_per_iter);
  OutputPool out_pool(new_length, items_per_iter);

  printf("Post-allocation VRAM, %lu sequences allocated:\n", items_per_iter);
  print_vram();

  printf("Uncompressing with a count of: %s", count.str().c_str());
  for(BigInt offset = 0; offset < count;) {
    std::cout << offset << "\n";
    
    rad_pool.set_base(offset);
    BigInt remaining = count - offset;

    // TODO: refactor
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

    printf("Launching kernel\n");
    cartesian_product<<<num_blocks, threads_per_block>>>(flat_perm_list.view(), rad_pool.view(), out_pool.view());
    cudaDeviceSynchronize();

    /*
    OutputView out_view = out_pool.view();
    printf("count: %s\n", count.str().c_str());
    for(int i = 0; i < num_threads; ++i) {
      printf("i: %d\n", i);
      for(int j = 0; j < out_view[i].size(); ++j) {
          printf("%d ", out_view[i][j]);
      }
      printf("\n");
    }
    */
    offset += num_threads;
  }
}