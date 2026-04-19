#pragma once
// CUDA-only — do not include from g++-compiled files
#include <string>
#include <stdexcept>

inline void check_cuda_error(cudaError_t err) {
    if(err != cudaSuccess)
        throw std::runtime_error("CUDA error: " + std::string(cudaGetErrorString(err)));
}
