#pragma once
#include <vector>
#include <span>
#include <functional>
#include <cstddef>

#include "jitify2.hpp"
#include "uncompress_kernel.h"
#include "flat_perm_list.h"
#include "mixed_radix_pool.h"
#include "sequence_pool.h"
#include "fourier_pool.h"
#include "gpu_fourier.h"

struct UncompressKernel::Impl {
    int order;
    int compress;
    int new_compress;
    int paf_constant;
    jitify2::Kernel kernel;
    
    void launch_kernel();
};