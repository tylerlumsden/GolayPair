// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef COMMONDX_TYPES_HPP
#define COMMONDX_TYPES_HPP

#include "commondx/detail/stl/cstddef.hpp"

#include "commondx/detail/namespace_wrapper_open.hpp"

namespace commondx {

#if __cplusplus >= 201703L
    using byte = COMMONDX_STL_NAMESPACE::byte;
#else
    enum class byte : unsigned char {};
#endif

}  // namespace commondx

// Namespace wrapper
#include "commondx/detail/namespace_wrapper_close.hpp"

#endif  // COMMONDX_TYPES_HPP

