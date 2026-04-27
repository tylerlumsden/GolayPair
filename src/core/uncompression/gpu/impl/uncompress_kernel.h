#pragma once
#include <vector>
#include <span>
#include <functional>
#include <memory>
#include "jitify2.hpp"

using PermList = std::vector<std::vector<std::vector<int>>>;

class UncompressKernel {
    struct LaunchParams {
        unsigned int block_dim_x;
        unsigned int shared_mem;
        unsigned int ffts_per_block;
    };

    int order;
    int compress;
    int new_compress;
    int paf_constant;
    const PermList& permutations;
    jitify2::Kernel kernel;
    LaunchParams launch_params;

public:
    UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant);
    ~UncompressKernel();
    UncompressKernel(const UncompressKernel&) = delete;
    UncompressKernel& operator=(const UncompressKernel&) = delete;

    void run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer);
};
