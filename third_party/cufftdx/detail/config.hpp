// Copyright (c) 2020-2023, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DETAIL_CONFIG_HPP
#define CUFFTDX_DETAIL_CONFIG_HPP

#include "cufftdx/detail/commondx_config.hpp"

#ifdef __CUDACC_RTC__
#    define CUFFTDX_DETAIL_USE_CUDA_STL
#endif

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#   define CUFFTDX_STD ::cuda::std
#else
#   define CUFFTDX_STD ::std
#endif

#ifdef __CUDACC__
#   define __CUFFTDX_HOST_DEVICE_FORCEINLINE__ __host__ __device__ __forceinline__
#else
#   define __CUFFTDX_HOST_DEVICE_FORCEINLINE__
#endif

#endif // CUFFTDX_DETAIL_CONFIG_HPP
