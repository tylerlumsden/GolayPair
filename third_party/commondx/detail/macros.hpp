// Copyright (c) 2025, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef COMMONDX_MACROS_HPP
#define COMMONDX_MACROS_HPP

#ifndef COMMONDX_HOST_DEVICE
#define COMMONDX_HOST_DEVICE __host__ __device__ __forceinline__
#endif

#ifndef COMMONDX_DEVICE
#define COMMONDX_DEVICE __device__ __forceinline__
#endif

#endif // COMMONDX_MACROS_HPP
