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
    unsigned int max_output_count,
    unsigned long long* step_cycles  // nullable; [0]=radix [1]=input_load [2]=dft
) {
    extern __shared__ int8_t smem_input[];
    const int stride  = smem_char_stride(fft_size);
    int8_t* my_input  = smem_input + threadIdx.x * stride;

    const unsigned int fft_id = blockIdx.x * blockDim.x + threadIdx.x;
    if (fft_id >= num_ffts) return;

    // Only time full blocks so __shfl_down_sync(0xffffffff) is safe.
    const bool do_timing = step_cycles &&
        ((blockIdx.x + 1) * (unsigned)blockDim.x <= num_ffts);

    clock_t t0 = do_timing ? clock() : 0;

    // Step 1: Mixed-radix index computation.
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

    clock_t t1 = do_timing ? clock() : 0;

    // Step 2: Load input sequence into shared memory as int8_t.
    FlatPermList::View permutations(perm_data);
    for (int i = 0; i < fft_size; i++)
        my_input[i] = (int8_t)permutations[i % length](my_radix[i % length], i / length);

    clock_t t2 = do_timing ? clock() : 0;

    // Step 3: Naive DFT with threshold check.
    // Use flag+break (not early return) so all threads reach the timing point below.
    bool passed = true;
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
            if (re * re + im * im >= threshold) { passed = false; break; }

            float nwkr = wkr * w1r - wki * w1i;
            wki = wkr * w1i + wki * w1r;
            wkr = nwkr;
        }
    }

    clock_t t3 = do_timing ? clock() : 0;

    // Warp-reduce cycle deltas and accumulate to global counters.
    if (do_timing) {
        unsigned long long r = (unsigned long long)(t1 - t0);
        unsigned long long l = (unsigned long long)(t2 - t1);
        unsigned long long d = (unsigned long long)(t3 - t2);
        for (int off = 16; off > 0; off >>= 1) {
            r += __shfl_down_sync(0xffffffff, r, off);
            l += __shfl_down_sync(0xffffffff, l, off);
            d += __shfl_down_sync(0xffffffff, d, off);
        }
        if ((threadIdx.x & 31) == 0) {
            atomicAdd(&step_cycles[0], r);
            atomicAdd(&step_cycles[1], l);
            atomicAdd(&step_cycles[2], d);
        }
    }

    if (!passed) return;

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
    unsigned int max_output_count,
    unsigned long long* step_cycles
) {
    uncompress_kernel_impl<<<grid, block, smem_bytes>>>(
        base_radices, offset, perm_data,
        output, input_output, output_count,
        num_ffts, fft_size, length, threshold, max_output_count,
        step_cycles
    );
}
