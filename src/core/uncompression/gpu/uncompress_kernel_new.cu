#include <thrust/device_vector.h>
#include <cuda/std/mdspan>
#include <cuda/std/span>
#include <cuda/std/complex>

#include "cufftdx.hpp"

void check_cuda_error(cudaError_t err) {
  if(err != cudaSuccess) {
    throw std::runtime_error("CUDA malloc failed: " + std::string(cudaGetErrorString(err)));
  }
}

using SeqVal = float;
using Fourier = cuda::std::complex<float>;
using PermList = std::vector<std::vector<std::vector<int>>>;

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

