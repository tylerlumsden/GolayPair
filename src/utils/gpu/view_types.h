#pragma once
// CUDA-only — do not include from g++-compiled files

#include <cuda/std/mdspan>
#include <cuda/std/span>
#include <cstdint>
#include <cstddef>
#include <cuComplex.h>

#include "flat_perm_list.h"
#include "mixed_radix_pool.h"
#include "sequence_pool.h"
#include "fourier_pool.h"

using PermSpan = cuda::std::mdspan<
    int,
    cuda::std::extents<int, cuda::std::dynamic_extent, cuda::std::dynamic_extent>
>;
using MixedRadix = cuda::std::span<int>;

template <typename T>
struct SequenceView {
    T*     values;
    size_t length;
    size_t stride;

    __host__ __device__
    SequenceView(T* v, size_t len, size_t stride) : values(v), length(len), stride(stride) {}

    __host__ __device__ T& operator[](size_t i) { return values[i * stride]; }
    __host__ __device__ size_t size() { return length; }
};

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

    __device__ __host__
    PermSpan operator[](int i) const {
        int index = indexes[i];
        int size  = (i == indexes_size - 1)
                  ? (data_size - indexes[i])
                  : (indexes[i + 1] - indexes[i]);
        return PermSpan(&data[index], size / permutation_size, permutation_size);
    }
};

struct MixedRadixPool::View {
    int* num_pool;
    int* base_num;
    int* radices;
    int  digits;

    __host__ __device__
    View(int* num_pool, int* base_num, int* radices, int digits)
      : num_pool(num_pool), base_num(base_num), radices(radices), digits(digits) {}

    __host__ __device__
    MixedRadix operator[](uint64_t i) const {
        return MixedRadix(&num_pool[i * digits], digits);
    }

    __device__
    void init(uint64_t thread_id) {
        MixedRadix slot = (*this)[thread_id];
        for(int i = 0; i < digits; ++i) slot[i] = base_num[i];
        uint64_t carry = thread_id;
        for(int i = digits - 1; i >= 0 && carry; i--) {
            uint64_t sum = slot[i] + carry;
            slot[i] = sum % radices[i];
            carry   = sum / radices[i];
        }
    }
};

struct SequencePool::View {
    float* values;
    size_t length;
    size_t batch;

    __host__
    View(float* v, size_t len, size_t batch) : values(v), length(len), batch(batch) {}

    __host__ __device__
    SequenceView<float> operator[](size_t thread_id) {
        return SequenceView<float>(values + thread_id, length, batch);
    }
};

struct FourierPool::View {
    cuComplex* values;
    size_t     length;
    size_t     batch;

    __host__
    View(cuComplex* v, size_t len, size_t batch) : values(v), length(len), batch(batch) {}

    __host__ __device__
    SequenceView<cuComplex> operator[](size_t thread_id) {
        return SequenceView<cuComplex>(values + thread_id, length, batch);
    }
};
