#pragma once
#include <vector>
#include <span>
#include <functional>
#include <memory>
#include "jitify2.hpp"
#include "cuda_runtime.h"

using PermList = std::vector<std::vector<std::vector<int>>>;

class UncompressKernel {
    struct LaunchParams {
        dim3 block_dim;
        unsigned int shared_mem;
        unsigned int ffts_per_block;
        unsigned int workspace_size;
        dim3 blue_block_dim;
        unsigned int blue_smem_size;
    };

    int order;
    int compress;
    int new_compress;
    int paf_constant;
    size_t length;
    size_t new_length;
    const PermList& permutations;
    jitify2::Kernel kernel;
    LaunchParams launch_params;
    void* workspace = nullptr;

public:
    UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant);
    ~UncompressKernel();
    UncompressKernel(const UncompressKernel&) = delete;
    UncompressKernel& operator=(const UncompressKernel&) = delete;

    void run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer);
};
