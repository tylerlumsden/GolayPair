// Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_TRAITS_DETAIL_BLUESTEIN_HELPERS_HPP
#define CUFFTDX_TRAITS_DETAIL_BLUESTEIN_HELPERS_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#else
#    include <type_traits>
#endif

#include "cufftdx/database/database_definitions.hpp"
#include "cufftdx/database/fft_implementation_definitions.hpp"
#include "cufftdx/database/detail/database_query.hpp"
#include "cufftdx/traits/detail/frontend_backend_mappings.hpp"

namespace cufftdx {
    namespace detail {
        template<class Description>
        __CUFFTDX_HOST_DEVICE_FORCEINLINE__ constexpr unsigned int get_bluestein_size() {
            return get_bluestein_size(size_of<Description>::value);
        }

        template<unsigned int FFTSize>
        __CUFFTDX_HOST_DEVICE_FORCEINLINE__ constexpr bool is_bluestein_supported() {
            return get_bluestein_size(FFTSize) > 0;
        }

        template<unsigned int FFTSize,
                 class FFTPrecisionType,
                 fft_direction           FFTDirection,
                 fft_type                FFTType,
                 unsigned int            FFTSM,
                 real_mode               RealMode,
                 experimental::code_type FFTCode>
        struct is_bluestein_required {
        private:
            // Attempt to use CT algorithm. If no record found, is_bluestein_required is set to true
            static constexpr auto ptx_backend = frontend_to_backend(algorithm::ct,
                                                                    execution_type::block,
                                                                    FFTSize,
                                                                    FFTType,
                                                                    FFTDirection,
                                                                    FFTSM,
                                                                    RealMode,
                                                                    0 /* elements per thread */,
                                                                    0 /* block_dim_x */,
                                                                    experimental::code_type::ptx);

            static constexpr auto lto_backend = frontend_to_backend(algorithm::ct,
                                                                    execution_type::block,
                                                                    FFTSize,
                                                                    FFTType,
                                                                    FFTDirection,
                                                                    FFTSM,
                                                                    RealMode,
                                                                    0 /* elements per thread */,
                                                                    0 /* block_dim_x */,
                                                                    experimental::code_type::ltoir);

            // Search for record in database
            using block_fft_record_t = typename database::detail::constexpr_db::constexpr_query_database<ptx_backend.size,
                                                                                                         ptx_backend.type,
                                                                                                         ptx_backend.direction,
                                                                                                         ptx_backend.sm,
                                                                                                         ptx_backend.elements_per_thread,
                                                                                                         ptx_backend.min_elements_per_thread,
                                                                                                         lto_backend.size,
                                                                                                         lto_backend.type,
                                                                                                         lto_backend.direction,
                                                                                                         lto_backend.sm,
                                                                                                         lto_backend.elements_per_thread,
                                                                                                         lto_backend.min_elements_per_thread,
                                                                                                         FFTPrecisionType,
                                                                                                         FFTCode>::block_fft_record_t;

        public:
            static constexpr bool value = !block_fft_record_t::defined;
        };

        template<unsigned int FFTSize,
                 typename FFTPrecisionType,
                 fft_direction           FFTDirection,
                 fft_type                FFTType,
                 unsigned int            FFTSM,
                 real_mode               FFTRealMode,
                 experimental::code_type FFTCode>
        constexpr inline bool is_bluestein_required<FFTSize, FFTPrecisionType, FFTDirection, FFTType, FFTSM, FFTRealMode, FFTCode>::value;
    } // namespace detail
} // namespace cufftdx

#endif // CUFFTDX_TRAITS_DETAIL_BLUESTEIN_HELPERS_HPP
