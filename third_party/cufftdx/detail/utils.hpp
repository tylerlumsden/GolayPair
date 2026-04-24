// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DETAIL_UTILS_HPP
#define CUFFTDX_DETAIL_UTILS_HPP

#ifndef __CUDACC_RTC__
#   include <cstring>
#endif

#include <cuda_fp16.h>

namespace cufftdx {
    namespace detail {

        template<class T>
        inline __device__ T get_val(double val) {
            return static_cast<T>(val);
        }

        template<>
        inline __device__ __half2 get_val<__half2>(double val) {
            return __float2half2_rn(static_cast<float>(val));
        }

        template<class T>
        inline __device__ __host__ T get_nan() {
            return NAN;
        }

        template<>
        inline __device__ __host__ __half2 get_nan<__half2>() {
            #ifdef __CUDA_ARCH__
            const unsigned h2_nan = unsigned(0x07FF07FF);
            return *reinterpret_cast<__half2 const*>(&h2_nan);
            #else
            unsigned h2_nan = unsigned(0x07FF07FF);
            __half2 ret;
            std::memcpy(static_cast<void*>(&ret), static_cast<void*>(&h2_nan),
                        sizeof(__half2));
            return ret;
            #endif
        }

        template<class T>
        inline __device__ __host__ constexpr T get_zero() {
            return 0.;
        }

        template<>
        inline __device__ __host__ constexpr __half2 get_zero<__half2>() {
            // This return __half2 with zeros everywhere
            return __half2 {};
        }

    } // namespace detail
} // namespace cufftdx

#endif
