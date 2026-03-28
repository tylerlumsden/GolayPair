#include <vector>
#include <map>
#include <span>
#include <cstdio>
#include<cstdint>

#include <boost/multiprecision/cpp_int.hpp>
#include <thrust/device_vector.h>
#include <cuda/std/mdspan>
#include <cuda/std/span>

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
      cudaMallocManaged(&indexes, host_indexes.size() * sizeof(int));
      cudaMallocManaged(&data, host_data.size() * sizeof(int));

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

  public:
    __host__
    MixedRadixPool(const std::vector<int>& input_radices, boost::multiprecision::cpp_int input_num, uint64_t num_threads) {
      digits = input_radices.size();
      cudaMallocManaged(&radices, digits * sizeof(int));
      cudaMallocManaged(&base_num, digits * sizeof(int));
      cudaMallocManaged(&num_pool, num_threads * digits * sizeof(int));

      for(int i = 0; i < digits; ++i) {
        radices[i] = input_radices[i];
      }
      for(int i = digits - 1; i >= 0; --i) {
        base_num[i] = static_cast<int>(input_num % radices[i]);
        input_num /= radices[i];
      }
    }

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
      cudaMallocManaged(&values, num_threads * len * sizeof(int));
    }

    OutputView view() {
      return OutputView(values, length);
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

void uncompress_kernel(std::vector<int> seq, PermMap permutations, size_t new_length) {   
  FlatPermList flat_perm_list(permutations, seq);

  std::vector<int> radices;
  for(int num : seq) {
    radices.push_back(permutations[num].size());
  }

  boost::multiprecision::cpp_int count = 1;
  for(int num : radices) {
    count *= num;
  }

  int num_blocks = 1, threads_per_block = 256;
  uint64_t num_threads = num_blocks * threads_per_block;
  MixedRadixPool rad_pool(radices, 0, num_threads);

  OutputPool out_pool(new_length, num_threads);
  OutputView out_view = out_pool.view();

  cartesian_product<<<num_blocks, threads_per_block>>>(flat_perm_list.view(), rad_pool.view(), out_pool.view());
  cudaDeviceSynchronize();

  printf("count: %s\n", count.str().c_str());
  for(int i = 0; i < num_threads; ++i) {
    printf("i: %d\n", i);
    for(int j = 0; j < out_view[i].size(); ++j) {
        printf("%d ", out_view[i][j]);
    }
    printf("\n");
  }
}