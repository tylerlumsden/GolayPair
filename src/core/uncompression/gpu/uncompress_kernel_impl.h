#pragma once
#include <vector>
#include <span>
#include <functional>
#include <cstddef>

#include "uncompress_kernel.h"
#include "flat_perm_list.h"
#include "mixed_radix_pool.h"
#include "sequence_pool.h"
#include "fourier_pool.h"
#include "gpu_fourier.h"

struct UncompressKernel::Impl {
    FlatPermList    flat_perm_list;
    MixedRadixPool  rad_pool;
    SequencePool    seq_pool;
    FourierPool     psd_pool;
    SequencePool    seq_filtered;
    FourierPool     psd_filtered;
    GPUFourier      fft;
    int             order;
    int             paf_constant;

    Impl(PermList& permutations, size_t new_length, size_t items_per_iter,
         const std::vector<int>& radices, int order, int paf_constant);
    ~Impl();

    const std::vector<int>& radices() const { return rad_pool.radices(); }
    size_t items_per_iter() const           { return seq_pool.batch_size(); }

    size_t execute_batch(const std::vector<int>& mixed_radix, size_t blocks, size_t threads,
                         const std::function<void(std::span<int>, std::span<double>)>& writer);
};
