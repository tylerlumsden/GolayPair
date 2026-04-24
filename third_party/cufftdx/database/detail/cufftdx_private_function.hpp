// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DETAIL_PRIVATE_FUNCTION_HPP
#define CUFFTDX_DATABASE_DETAIL_PRIVATE_FUNCTION_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/array>
#else
#    include <array>
#endif

#include "cufftdx/operators.hpp"
#include "cufftdx/traits/detail/make_complex_type.hpp"

namespace cufftdx {
    namespace database {
        namespace detail {
            template<unsigned Version, unsigned long long FunctionID, typename T, unsigned int FFTsPerBlock>
            __device__ void cufftdx_private_lto_function(T* rmem, void* smem, int sign);

            template<unsigned int FunctionID, typename T>
            __device__ void cufftdx_private_function(typename cufftdx::detail::make_complex_type<T>::cufftdx_type* rmem,
                                                     unsigned                                                      smem);

            template<unsigned int FunctionID, typename T>
            __device__ void cufftdx_private_function_wrapper(typename cufftdx::detail::make_complex_type<T>::cufftdx_type* rmem,
                                                             void*                                                         smem) {
                unsigned smem32 = static_cast<unsigned>(__cvta_generic_to_shared(smem));
                cufftdx_private_function<FunctionID, T>(rmem, smem32);
            }
        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif
