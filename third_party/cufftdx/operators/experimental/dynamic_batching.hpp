// Copyright (c) 2019-2025, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_OPERATORS_EXPERIMENTAL_DYNAMIC_BATCHING_HPP
#define CUFFTDX_OPERATORS_EXPERIMENTAL_DYNAMIC_BATCHING_HPP

#include "cufftdx/operators/fft_operator.hpp"
#include "commondx/detail/expressions.hpp"
#include "commondx/traits/detail/is_operator_fd.hpp"
#include "commondx/traits/detail/get_operator_fd.hpp"

namespace cufftdx {
    namespace experimental {

        struct DynamicBatching: public commondx::detail::operator_expression {
        };
    }
} // namespace cufftdx

namespace commondx::detail {

    template<>
    struct is_operator<cufftdx::fft_operator, cufftdx::fft_operator::experimental_dynamic_batching, cufftdx::experimental::DynamicBatching>:
        COMMONDX_STL_NAMESPACE::true_type {
    };

    template<>
    struct get_operator_type<cufftdx::fft_operator,cufftdx::experimental::DynamicBatching> {
        static constexpr cufftdx::fft_operator value = cufftdx::fft_operator::experimental_dynamic_batching;
    };
} // namespace commondx::detail

#endif // CUFFTDX_OPERATORS_EXPERIMENTAL_DYNAMIC_BATCHING_HPP
