#pragma once
#include <vector>
#include <span>
#include <functional>
#include <cuda_runtime.h>
#include "uncompress_kernel.cuh"

using PermList = std::vector<std::vector<std::vector<int>>>;

class UncompressKernel {
    int order;
    int compress;
    int new_compress;
    int paf_constant;
    size_t length;
    size_t new_length;
    const PermList& permutations;

public:
    UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant);
    ~UncompressKernel() = default;
    UncompressKernel(const UncompressKernel&) = delete;
    UncompressKernel& operator=(const UncompressKernel&) = delete;

    void run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer);
};
