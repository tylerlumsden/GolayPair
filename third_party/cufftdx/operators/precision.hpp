// Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_OPERATORS_PRECISION_HPP
#define CUFFTDX_OPERATORS_PRECISION_HPP

#include "cufftdx/detail/config.hpp"
#include "cufftdx/operators/fft_operator.hpp"
#include "commondx/operators/precision.hpp"

namespace cufftdx {
    enum class precision
    {
        f16,
        f32,
        f64
    };

    template<class T>
    struct Precision: public commondx::PrecisionBase<T, __half, float, double> {
    };

    namespace detail {
        // TODO: Move to types.hpp once commondx/complex_types.hpp works with host compiler
        enum class value_type
        {
            r_16f,  // equivalent to __half
            r_16f2, // equivalent to __half2
            r_32f,  // equivalent to float
            r_64f,  // equivalent to double
            c_16f,  // equivalent to cufftdx::complex<__half>
            c_16f2, // equivalent to cufftdx::complex<__half2>
            c_32f,  // equivalent to cufftdx::complex<float>
            c_64f   // equivalent to cufftdx::complex<double>
        };

        template<typename T>
        constexpr precision map_precision() {
            if constexpr (CUFFTDX_STD::is_same_v<T, __half>) {
                return precision::f16;
            } else if constexpr (CUFFTDX_STD::is_same_v<T, float>) {
                return precision::f32;
            } else if constexpr (CUFFTDX_STD::is_same_v<T, double>) {
                return precision::f64;
            } else {
                static_assert(CUFFTDX_STD::is_same_v<T, void>,
                              "map_precision: Only __half, float, and double types are supported");
            }
            return precision::f32;
        }

        using default_fft_precision_operator = Precision<float>;
    } // namespace detail
} // namespace cufftdx

namespace commondx::detail {
    template<class T>
    struct is_operator<cufftdx::fft_operator, cufftdx::fft_operator::precision, cufftdx::Precision<T>>:
        COMMONDX_STL_NAMESPACE::true_type {
    };

    template<class T>
    struct get_operator_type<cufftdx::fft_operator,cufftdx::Precision<T>> {
        static constexpr cufftdx::fft_operator value = cufftdx::fft_operator::precision;
    };
} // namespace commondx::detail

#endif // CUFFTDX_OPERATORS_TYPE_HPP
