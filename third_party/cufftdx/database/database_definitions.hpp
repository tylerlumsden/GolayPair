// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DEFINITIONS_HPP
#define CUFFTDX_DATABASE_DEFINITIONS_HPP

#include "cufftdx/database/detail/block_fft.hpp"
#include "cufftdx/database/database_selector_fd.hpp"
#include "cufftdx/database/detail/optional.hpp"

namespace cufftdx {
    namespace database {
        namespace detail {
            // Forward declaration of database_function (specialized in individual database files below)
            template<typename PrecisionType, unsigned int Architecture, fft_direction Direction>
            struct database_function;

#if (!defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 530)
#    include "cufftdx/database/records/750/database_fp16_fwd.hpp.inc"
#endif
#include "cufftdx/database/records/750/database_fp32_fwd.hpp.inc"
#include "cufftdx/database/records/750/database_fp64_fwd.hpp.inc"

#if (!defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 530)
#    include "cufftdx/database/records/800/database_fp16_fwd.hpp.inc"
#endif
#include "cufftdx/database/records/800/database_fp32_fwd.hpp.inc"
#include "cufftdx/database/records/800/database_fp64_fwd.hpp.inc"

#if (!defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 530)
#    include "cufftdx/database/records/860/database_fp16_fwd.hpp.inc"
#endif
#include "cufftdx/database/records/860/database_fp32_fwd.hpp.inc"
#include "cufftdx/database/records/860/database_fp64_fwd.hpp.inc"

#if (!defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 530)
#    include "cufftdx/database/records/890/database_fp16_fwd.hpp.inc"
#endif
#include "cufftdx/database/records/890/database_fp32_fwd.hpp.inc"
#include "cufftdx/database/records/890/database_fp64_fwd.hpp.inc"

#if (!defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 530)
#    include "cufftdx/database/records/900/database_fp16_fwd.hpp.inc"
#endif
#include "cufftdx/database/records/900/database_fp32_fwd.hpp.inc"
#include "cufftdx/database/records/900/database_fp64_fwd.hpp.inc"

#if (!defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 530)
#    include "cufftdx/database/records/1000/database_fp16_fwd.hpp.inc"
#endif
#include "cufftdx/database/records/1000/database_fp32_fwd.hpp.inc"
#include "cufftdx/database/records/1000/database_fp64_fwd.hpp.inc"


#if (!defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 530)
#    include "cufftdx/database/records/1200/database_fp16_fwd.hpp.inc"
#endif
#include "cufftdx/database/records/1200/database_fp32_fwd.hpp.inc"
#include "cufftdx/database/records/1200/database_fp64_fwd.hpp.inc"

        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_DEFINITIONS_HPP
