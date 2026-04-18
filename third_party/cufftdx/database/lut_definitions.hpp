// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_LUT_DEFINITIONS_HPP
#define CUFFTDX_DATABASE_LUT_DEFINITIONS_HPP

#include "commondx/complex_types.hpp"

namespace cufftdx {
    namespace database {
        namespace detail {
            using lut_fp32_type = commondx::complex<float>;
            using lut_fp64_type = commondx::complex<double>;

#if defined(CUFFTDX_DETAIL_USE_EXTERN_LUT) || defined(CUFFTDX_USE_SEPARATE_TWIDDLES)
#    include "cufftdx/database/lut_fp32.h"
#    include "cufftdx/database/lut_fp64.h"
#else // CUFFTDX_DETAIL_USE_EXTERN_LUT
#    ifndef CUFFTDX_DETAIL_LUT_LINKAGE
#        define CUFFTDX_DETAIL_LUT_LINKAGE static
#    endif
#    if !defined(CUFFTDX_DETAIL_MANUAL_IMPL_FILTER) || (defined(CUFFTDX_DETAIL_INCLUDE_PRECISION_FP32))
#        include "cufftdx/database/lut_fp32.hpp.inc"
#    endif
#    if !defined(CUFFTDX_DETAIL_MANUAL_IMPL_FILTER) || (defined(CUFFTDX_DETAIL_INCLUDE_PRECISION_FP64))
#        include "cufftdx/database/lut_fp64.hpp.inc"
#    endif
#    ifdef CUFFTDX_DETAIL_LUT_LINKAGE
#        undef CUFFTDX_DETAIL_LUT_LINKAGE
#    endif
#endif // CUFFTDX_DETAIL_USE_EXTERN_LUT

        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_LUT_DEFINITIONS_HPP
