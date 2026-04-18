// Copyright (c) 2025, NVIDIA CORPORATION.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DETAIL_SUPPORT_HPP
#define CUFFTDX_DETAIL_SUPPORT_HPP

#include "cufftdx/detail/system_checks.hpp"
#include "cufftdx/operators/experimental/code_type.hpp"

namespace cufftdx {
    namespace detail {

        template<typename BlockConfig, bool IsVoid = CUFFTDX_STD::is_void<BlockConfig>::value>
        struct get_block_config_version {
            static constexpr unsigned value = BlockConfig::version;
        };

        template<typename BlockConfig>
        struct get_block_config_version<BlockConfig, true> {
            static constexpr unsigned value = 0;
        };

        template<typename BlockConfig, bool IsVoid = CUFFTDX_STD::is_void<BlockConfig>::value>
        struct get_block_config_code {
            static constexpr experimental::code_type value = BlockConfig::code;
        };

        template<typename BlockConfig>
        struct get_block_config_code<BlockConfig, true> {
            static constexpr experimental::code_type value = experimental::code_type::ltoir;
        };
        // Helper to check if LTO supports BlockDim for a given configuration
        template<typename Config, typename BlockDimension>
        static constexpr bool is_lto_config_supported() {
            return (get_block_config_code<Config>::value != experimental::code_type::ltoir) ||           // Non-LTO always supported
                    CUFFTDX_STD::is_void<BlockDimension>::value;
        }
    } // namespace detail
} // namespace cufftdx

#endif // CUFFTDX_DETAIL_SUPPORT_HPP