#include "uncompress_kernel.cuh"
#include "view_types.h"
#include <cstdint>

static constexpr float TWO_PI_F = 6.28318530717958647692f;
static constexpr int MAX_RADIX_LENGTH = 64;

// Barrett reduction: q = a/d, r = a%d  (magic = (1ULL<<32)/d, precomputed on host)
__device__ __forceinline__ void fast_divmod(uint32_t a, uint32_t magic, uint32_t d,
                                             uint32_t& q, uint32_t& r) {
    q = __umulhi(a, magic);
    r = a - q * d;
    if (r >= d) { r -= d; ++q; }
}

__launch_bounds__(THREADS_PER_BLOCK, 3)
__global__ void uncompress_kernel_impl(
    const int* __restrict__ base_radices,
    const int* __restrict__ offset,
    const uint32_t* __restrict__ magic,
    FlatPermListData perm_data,
    float* __restrict__ output,
    int*   __restrict__ input_output,
    unsigned int* output_count,
    unsigned int num_ffts,
    int fft_size,
    int length,
    float threshold,
    unsigned int max_output_count,
    unsigned long long* step_cycles  // nullable; [0]=coop_load [1]=radix [2]=input_load [3]=dft
) {
    extern __shared__ int8_t smem_raw[];
    const int stride = smem_char_stride(fft_size);
    int8_t* my_input = smem_raw + threadIdx.x * stride;

    // Perm table section sits after the per-thread input buffers (always 4-byte aligned).
    int* smem_indexes = (int*)(smem_raw + THREADS_PER_BLOCK * stride);
    int* smem_pdata   = smem_indexes + perm_data.indexes_size;

    // Only time full blocks so __shfl_down_sync(0xffffffff) is safe.
    // Computed here (before early exit) so the coop load is included in timing.
    const bool do_timing = step_cycles &&
        ((blockIdx.x + 1) * (unsigned)blockDim.x <= num_ffts);

    clock_t t0 = do_timing ? clock() : 0;

    // Cooperatively load the permutation table into shared memory (all threads participate).
    for (int i = (int)threadIdx.x; i < perm_data.indexes_size; i += (int)blockDim.x)
        smem_indexes[i] = __ldg(&perm_data.indexes[i]);
    for (int i = (int)threadIdx.x; i < perm_data.data_size; i += (int)blockDim.x)
        smem_pdata[i] = __ldg(&perm_data.data[i]);
    __syncthreads();

    clock_t t1 = do_timing ? clock() : 0;

    const unsigned int fft_id = blockIdx.x * blockDim.x + threadIdx.x;
    if (fft_id >= num_ffts) return;

    // Step 1: Mixed-radix index computation (Barrett reduction — no hardware divide).
    int my_radix[MAX_RADIX_LENGTH];
    {
        uint32_t temp = fft_id, carry = 0;
        for (int i = length - 1; i >= 0; i--) {
            uint32_t d = (uint32_t)base_radices[i];
            uint32_t m = magic[i];
            uint32_t q, r;
            fast_divmod(temp, m, d, q, r);
            temp = q;
            uint32_t s = (uint32_t)offset[i] + r + carry;
            uint32_t sq, sr;
            fast_divmod(s, m, d, sq, sr);
            my_radix[i] = (int)sr;
            carry        = sq;
        }
    }

    clock_t t2 = do_timing ? clock() : 0;

    // Step 2: Load input sequence into shared memory via smem perm table.
    const int perm_sz = perm_data.permutation_size;
    int base_off[MAX_RADIX_LENGTH];
    for (int j = 0; j < length; j++)
        base_off[j] = smem_indexes[j] + my_radix[j] * perm_sz;
    int out = 0;
    for (int rep = 0; rep < perm_sz; rep++)
        for (int j = 0; j < length; j++)
            my_input[out++] = (int8_t)smem_pdata[base_off[j] + rep];

    clock_t t3 = do_timing ? clock() : 0;

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

    clock_t t4 = do_timing ? clock() : 0;

    // Warp-reduce all 4 cycle deltas and accumulate to global counters.
    if (do_timing) {
        unsigned long long c = (unsigned long long)(t1 - t0);
        unsigned long long r = (unsigned long long)(t2 - t1);
        unsigned long long l = (unsigned long long)(t3 - t2);
        unsigned long long d = (unsigned long long)(t4 - t3);
        for (int off = 16; off > 0; off >>= 1) {
            c += __shfl_down_sync(0xffffffff, c, off);
            r += __shfl_down_sync(0xffffffff, r, off);
            l += __shfl_down_sync(0xffffffff, l, off);
            d += __shfl_down_sync(0xffffffff, d, off);
        }
        if ((threadIdx.x & 31) == 0) {
            atomicAdd(&step_cycles[0], c);
            atomicAdd(&step_cycles[1], r);
            atomicAdd(&step_cycles[2], l);
            atomicAdd(&step_cycles[3], d);
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
    const uint32_t* magic,
    FlatPermListData perm_data,
    float* output, int* input_output,
    unsigned int* output_count,
    unsigned int num_ffts,
    int fft_size, int length, float threshold,
    unsigned int max_output_count,
    unsigned long long* step_cycles
) {
    uncompress_kernel_impl<<<grid, block, smem_bytes>>>(
        base_radices, offset, magic, perm_data,
        output, input_output, output_count,
        num_ffts, fft_size, length, threshold, max_output_count,
        step_cycles
    );
}
