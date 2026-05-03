#pragma once

#include <span>
#include <cuda_runtime.h>
#include "cuda_error.h"

template <typename T>
struct MemoryPool {
    T* values;
    size_t size;
    size_t length;

    MemoryPool(size_t size, size_t length) : size(size), length(length) {
        check_cuda_error(cudaMalloc(&values, size * length * sizeof(T)));
    }

    ~MemoryPool() {
        cudaFree(values);
    }

    static size_t items_storable(size_t len, size_t total_bytes) {
        return total_bytes / (len * sizeof(T));
    }
};