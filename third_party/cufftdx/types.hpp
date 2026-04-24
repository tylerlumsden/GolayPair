// Copyright (c) 2019-2023, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_TYPES_HPP
#define CUFFTDX_TYPES_HPP

#include "commondx/complex_types.hpp"
#include "commondx/types.hpp"

namespace cufftdx {
    namespace detail {
        template<class T>
        using complex = typename commondx::complex<T>;
    }

    template<class T>
    using complex = typename commondx::complex<T>;

    using byte = commondx::byte;
} // namespace cufftdx

#endif // CUFFTDX_TYPES_HPP
