// Copyright (c) 2025, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef COMMONDX_DETAIL_STL_UTILITY_HPP
#define COMMONDX_DETAIL_STL_UTILITY_HPP

#include "commondx/detail/config.hpp"

#ifdef COMMONDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/utility>
#else
#    include <utility>
#endif

#endif // COMMONDX_DETAIL_STL_UTILITY_HPP
