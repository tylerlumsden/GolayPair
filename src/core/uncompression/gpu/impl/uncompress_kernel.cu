#include "uncompress_kernel.cuh"
#include "view_types.h"
#include <cstdint>

static constexpr float TWO_PI_F = 6.28318530717958647692f;
static constexpr int MAX_RADIX_LENGTH = 64;

__launch_bounds__(THREADS_PER_BLOCK, 3)
__global__ void uncompress_kernel_impl(
    const int* __restrict__ base_radices,
    const int* __restrict__ offset,
    FlatPermListData perm_data,
    float* __restrict__ output,
    int*   __restrict__ input_output,
    unsigned int* output_count,
    unsigned int num_ffts,
    int fft_size,
    int length,
    float threshold,
    unsigned int max_output_count
) {
    extern __shared__ int8_t smem_input[];
    const int stride  = smem_char_stride(fft_size);
    int8_t* my_input  = smem_input + threadIdx.x * stride;

    const unsigned int fft_id = blockIdx.x * blockDim.x + threadIdx.x;
    if (fft_id >= num_ffts) return;

    // Step 1: Mixed-radix index computation (my_radix in local memory — accessed once, not hot).
    int my_radix[MAX_RADIX_LENGTH];
    {
        int temp = (int)fft_id, carry = 0;
        for (int i = length - 1; i >= 0; i--) {
            int d  = temp % base_radices[i];
            temp  /= base_radices[i];
            int s  = offset[i] + d + carry;
            my_radix[i] = s % base_radices[i];
            carry        = s / base_radices[i];
        }
    }

    // Step 2: Load input sequence into shared memory as int8_t (values are +-1).
    FlatPermList::View permutations(perm_data);
    for (int i = 0; i < fft_size; i++)
        my_input[i] = (int8_t)permutations[i % length](my_radix[i % length], i / length);

    // Step 3: Naive DFT with incremental twiddle rotation, threshold check.
    {
        float w1r, w1i;
        __sincosf(-TWO_PI_F / (float)fft_size, &w1i, &w1r);
        float wkr = 1.f, wki = 0.f;

        for (int k = 0; k < fft_size; k++) {
            float pr = 1.f, pi = 0.f, re = 0.f, im = 0.f;
            for (int n = 0; n < fft_size; n++) {
                float x  = (float)my_input[n];
                re += x * pr;
                im += x * pi;
                float tmp = pr * wkr - pi * wki;
                pi = pr * wki + pi * wkr;
                pr = tmp;
            }
            if (re * re + im * im >= threshold) return;

            float nwkr = wkr * w1r - wki * w1i;
            wki = wkr * w1i + wki * w1r;
            wkr = nwkr;
        }
    }

    // Step 4: Claim an output slot.
    unsigned int out_idx = atomicAdd(output_count, 1);
    if (out_idx >= max_output_count) return;

    // Step 5: Recompute DFT and write magnitudes + input to output buffers.
    {
        float w1r, w1i;
        __sincosf(-TWO_PI_F / (float)fft_size, &w1i, &w1r);
        float wkr = 1.f, wki = 0.f;

        for (int k = 0; k < fft_size; k++) {
            float pr = 1.f, pi = 0.f, re = 0.f, im = 0.f;
            for (int n = 0; n < fft_size; n++) {
                float x  = (float)my_input[n];
                re += x * pr;
                im += x * pi;
                float tmp = pr * wkr - pi * wki;
                pi = pr * wki + pi * wkr;
                pr = tmp;
            }
            output[out_idx * fft_size + k] = re * re + im * im;

            float nwkr = wkr * w1r - wki * w1i;
            wki = wkr * w1i + wki * w1r;
            wkr = nwkr;
        }
        for (int i = 0; i < fft_size; i++)
            input_output[out_idx * fft_size + i] = (int)my_input[i];
    }
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
) {
    uncompress_kernel_impl<<<grid, block, smem_bytes>>>(
        base_radices, offset, perm_data,
        output, input_output, output_count,
        num_ffts, fft_size, length, threshold, max_output_count
    );
}
