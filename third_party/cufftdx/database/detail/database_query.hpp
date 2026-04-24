// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DETAIL_DATABASE_QUERY_HPP
#define CUFFTDX_DATABASE_DETAIL_DATABASE_QUERY_HPP

#include "cufftdx/database/database_definitions.hpp"

// Always include compile-time query functionality
#include "constexpr_query.hpp"

// Only include runtime query functionality if runtime database is enabled
#if defined(CUFFTDX_ENABLE_RUNTIME_DATABASE)
#    include "runtime_query.hpp"
#endif

#endif // CUFFTDX_DATABASE_DETAIL_DATABASE_QUERY_HPP
