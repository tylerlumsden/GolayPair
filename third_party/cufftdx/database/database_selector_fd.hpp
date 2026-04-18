// Copyright (c) 2026, NVIDIA CORPORATION.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DATABASE_SELECTOR_FD_HPP
#define CUFFTDX_DATABASE_DATABASE_SELECTOR_FD_HPP

// forward declaration
namespace cufftdx {
    namespace database {
        namespace detail {
            template<typename PrecisionType, unsigned int Architecture, fft_direction Direction>
            struct database_selector;
        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_DATABASE_SELECTOR_FD_HPP
