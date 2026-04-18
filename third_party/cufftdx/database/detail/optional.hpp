// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DETAIL_OPTIONAL_HPP
#define CUFFTDX_DATABASE_DETAIL_OPTIONAL_HPP

#if defined(CUFFTDX_DETAIL_USE_CUDA_STL) 
#    include <cuda/std/optional>
namespace cufftdx {
    namespace database {
        namespace detail {
            template<typename T> using optional = cuda::std::optional<T>;
        }
    }
}
#else
#    include <optional>
namespace cufftdx {
    namespace database {
        namespace detail {
            template<typename T> using optional = std::optional<T>;
        }
    }
}
#endif
#endif // CUFFTDX_DATABASE_DETAIL_OPTIONAL_HPP
