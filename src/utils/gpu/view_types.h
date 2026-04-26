#pragma once
// CUDA-only — do not include from g++-compiled files

#include <cuda/std/mdspan>
#include <cuda/std/span>
#include <cstdint>
#include <cstddef>
#include <cuComplex.h>

#include "flat_perm_list.h"


using PermSpan = cuda::std::mdspan<
    int,
    cuda::std::extents<int, cuda::std::dynamic_extent, cuda::std::dynamic_extent>
>;

struct FlatPermList::View {
    int* indexes;
    int  indexes_size;
    int* data;
    int  data_size;
    int  permutation_size;

    __host__ __device__
    View(int* indexes, int indexes_size, int* data, int data_size, int permutation_size)
      : indexes(indexes), indexes_size(indexes_size),
        data(data), data_size(data_size),
        permutation_size(permutation_size) {}

    __host__ __device__
    View(const FlatPermListData& d)
      : indexes(d.indexes), indexes_size(d.indexes_size),
        data(d.data), data_size(d.data_size),
        permutation_size(d.permutation_size) {}

    __device__ __host__
    PermSpan operator[](int i) const {
        int index = indexes[i];
        int size  = (i == indexes_size - 1)
                  ? (data_size - indexes[i])
                  : (indexes[i + 1] - indexes[i]);
        return PermSpan(&data[index], size / permutation_size, permutation_size);
    }
};
