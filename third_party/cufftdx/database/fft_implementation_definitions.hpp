// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_FFT_IMPLEMENTATION_DEFINITIONS_HPP
#define CUFFTDX_DATABASE_FFT_IMPLEMENTATION_DEFINITIONS_HPP

#include "cufftdx/database/lut_definitions.hpp"
#include "cufftdx/database/detail/cufftdx_private_function.hpp"

namespace cufftdx {
    namespace database {
        namespace detail {

#ifndef CUFFTDX_PTX_REG
#    if (__CUDACC_VER_MAJOR__ == 12) && (__CUDACC_VER_MINOR__ < 1)
#        define CUFFTDX_PTX_REG(x) "=" #x
#    else
#        define CUFFTDX_PTX_REG(x) "=&" #x
#    endif
#endif

#if (!defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 530)
#    ifndef __HALF2_TO_UI
#        define __HALF2_TO_UI(var) *(reinterpret_cast<unsigned int*>(&(var)))
#    endif

#    if !defined(CUFFTDX_DETAIL_MANUAL_IMPL_FILTER) || (defined(CUFFTDX_DETAIL_INCLUDE_PRECISION_FP16))
#        include "cufftdx/database/records/definitions_fp16_fwd.hpp.inc"
#    endif

#endif
#if !defined(CUFFTDX_DETAIL_MANUAL_IMPL_FILTER) || (defined(CUFFTDX_DETAIL_INCLUDE_PRECISION_FP32))
#    include "cufftdx/database/records/definitions_fp32_fwd.hpp.inc"
#endif
#if !defined(CUFFTDX_DETAIL_MANUAL_IMPL_FILTER) || (defined(CUFFTDX_DETAIL_INCLUDE_PRECISION_FP64))
#    include "cufftdx/database/records/definitions_fp64_fwd.hpp.inc"
#endif

#ifdef __HALF2_TO_UI
#    undef __HALF2_TO_UI
#endif

        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_FFT_IMPLEMENTATION_DEFINITIONS_HPP
