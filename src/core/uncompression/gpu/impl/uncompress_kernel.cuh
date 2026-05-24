#pragma once
#include <cuda_runtime.h>
#include <cstdint>
#include "flat_perm_list.h"

constexpr unsigned int THREADS_PER_BLOCK = 128;

// Per-thread stride in bytes for int8_t shared memory.
// Smallest multiple of 4 >= fft_size with stride/4 odd → bank-conflict-free for 32-thread warps.
inline __host__ __device__ int smem_char_stride(int fft_size) {
    int k = (fft_size + 3) / 4;
    if (k % 2 == 0) k++;
    return k * 4;
}

void launch_uncompress_kernel(
    dim3 grid, dim3 block, size_t smem_bytes,
    int* base_radices, int* offset,
    FlatPermListData perm_data,
    float* output, int* input_output,
    unsigned int* output_count,
    unsigned int num_ffts,
    int fft_size, int length, float threshold,
    unsigned int max_output_count
);
