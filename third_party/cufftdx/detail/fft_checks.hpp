// Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DETAIL_FFT_CHECKS_HPP
#define CUFFTDX_DETAIL_FFT_CHECKS_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#else
#    include <type_traits>
#endif

#include <cuda_fp16.h>

#include "cufftdx/detail/fft_sizes.hpp"
#include "cufftdx/operators.hpp"
#include "cufftdx/traits/detail/bluestein_helpers.hpp"
#include "cufftdx/traits/fft_traits.hpp"
#include "cufftdx/traits/detail/frontend_backend_mappings.hpp"
#include "cufftdx/detail/support.hpp"

namespace cufftdx {
    namespace detail {

        template<typename BlockDimension, bool IsVoid = CUFFTDX_STD::is_void<BlockDimension>::value>
        struct get_block_dim_x {
            static constexpr unsigned value = BlockDimension::x;
        };

        template<typename BlockDimension>
        struct get_block_dim_x<BlockDimension, true> {
            static constexpr unsigned value = 0;
        };

        // LoosenRestriction is a bool flag signaling that we suspect that the description may not be
        // complete yet in a way which influences the maximal sizes. It is passed as 'true' whenever
        // there is no Type<> operator, or if the type is R2C/C2R and there is no RealFFTOptions
        // operator, since if RealFFTOptions is passed with real_mode::folded set as the
        // second argument, the size posssible to be executed is doubled in effect.
        //
        // Provision of LoosenRestriction flag allows such construction
        // using FFT_base = decltype(Block() + Size<MAX_R2C_SIZE>()) ---> MAX_R2C_SIZE is C2C unsupported
        // using FFT_r2c = decltype(FFT_base() + Type<fft_type::r2c>() + RealFFTOptions<normal, folded>())
        // using FFT_c2r = decltype(FFT_base() + Type<fft_type::c2r>() + RealFFTOptions<normal, folded>())
        template<class Precision, unsigned int Size, unsigned int Arch, bool LoosenRestriction = false>
        class is_supported
        {
            // architecture with biggest allowed sizes
            static constexpr unsigned int max_arch = 1000;
            // Max supported sizes, if -1 passed then SM is ignored and global max size is checked
            static constexpr auto effective_arch            = (Arch == unsigned(-1)) ? max_arch : Arch;
            static constexpr auto effective_max_blue_size   = (LoosenRestriction ? 2 : 1) * max_block_size<double>(effective_arch);
            static constexpr auto effective_max_thread_size = (LoosenRestriction ? 2 : 1) * max_thread_size<Precision>();
            static constexpr auto blue_size                 = detail::get_bluestein_size(Size);

        public:
            static constexpr auto effective_max_block_size = (LoosenRestriction ? 2 : 1) * max_block_size<Precision>(effective_arch);
            static constexpr bool is_sm_supported          = effective_max_block_size > 0;

            static constexpr bool thread_value     = (is_sm_supported && (Size <= effective_max_thread_size) && (Size >= 2));
            static constexpr bool block_value      = ((Size <= effective_max_block_size) && (Size >= 2));
            static constexpr bool blue_block_value = ((Size == effective_max_block_size) || (blue_size <= effective_max_blue_size) && (blue_size >= 2));

            static constexpr bool value = block_value || blue_block_value;
        };

        template<class Precision,
                 fft_type      Type,
                 fft_direction Direction,
                 unsigned      Size,
                 bool          Block,
                 bool          Thread,
                 class EPT, // void if not set
                 complex_layout  RealLayout,
                 real_mode    RealMode,
                 experimental::code_type Code,
                 class BlockDimension,
                 unsigned int Arch>
        class is_supported_helper
        {
            // Checks
            static_assert(Block || Thread,
                          "To check if an FFT description is supported on a given architecture it has to have Block or "
                          "Thead execution operator");

            static constexpr auto effective_memory_size = (RealMode == real_mode::folded && RealLayout != complex_layout::full)
                                                              ? Size / 2
                                                              : Size;
            static constexpr bool is_supported_thread     = is_supported<Precision, effective_memory_size, Arch>::thread_value;
            static constexpr bool is_supported_block      = is_supported<Precision, effective_memory_size, Arch>::block_value;
            static constexpr bool is_supported_block_blue = is_supported<Precision, effective_memory_size, Arch>::blue_block_value;

            static constexpr bool requires_block_blue =
                Block && is_bluestein_required<Size, Precision, Direction, Type, Arch, RealMode, Code>::value;

            static constexpr auto ptx_backend = frontend_to_backend(algorithm::ct,
                                                                    execution_type::block,
                                                                    Size,
                                                                    Type,
                                                                    Direction,
                                                                    Arch,
                                                                    RealMode,
                                                                    CUFFTDX_STD::conditional_t<!CUFFTDX_STD::is_void<EPT>::value, EPT, ElementsPerThread<0>>::value,
                                                                    get_block_dim_x<BlockDimension>::value,
                                                                    experimental::code_type::ptx);

            static constexpr auto lto_backend = frontend_to_backend(algorithm::ct,
                                                                    execution_type::block,
                                                                    Size,
                                                                    Type,
                                                                    Direction,
                                                                    Arch,
                                                                    RealMode,
                                                                    CUFFTDX_STD::conditional_t<!CUFFTDX_STD::is_void<EPT>::value, EPT, ElementsPerThread<0>>::value,
                                                                    get_block_dim_x<BlockDimension>::value,
                                                                    experimental::code_type::ltoir);

            static constexpr auto ptx_blue_backend = frontend_to_backend(algorithm::bluestein,
                                                                         execution_type::block,
                                                                         Size,
                                                                         Type,
                                                                         Direction,
                                                                         Arch,
                                                                         RealMode,
                                                                         CUFFTDX_STD::conditional_t<!CUFFTDX_STD::is_void<EPT>::value, EPT, ElementsPerThread<0>>::value,
                                                                         get_block_dim_x<BlockDimension>::value,
                                                                         experimental::code_type::ptx);

            static constexpr auto lto_blue_backend = frontend_to_backend(algorithm::bluestein,
                                                                         execution_type::block,
                                                                         Size,
                                                                         Type,
                                                                         Direction,
                                                                         Arch,
                                                                         RealMode,
                                                                         CUFFTDX_STD::conditional_t<!CUFFTDX_STD::is_void<EPT>::value, EPT, ElementsPerThread<0>>::value,
                                                                         get_block_dim_x<BlockDimension>::value,
                                                                         experimental::code_type::ltoir);

            using selected_block_config_t = typename database::detail::constexpr_db::constexpr_query_database<ptx_backend.size,
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
                                                                                      Precision,
                                                                                      Code>::selected_block_config_t;

            using selected_blue_block_config_t = typename database::detail::constexpr_db::constexpr_query_database<ptx_blue_backend.size,
                                                                                           ptx_blue_backend.type,
                                                                                           ptx_blue_backend.direction,
                                                                                           ptx_blue_backend.sm,
                                                                                           ptx_blue_backend.elements_per_thread,
                                                                                           ptx_blue_backend.min_elements_per_thread,
                                                                                           lto_blue_backend.size,
                                                                                           lto_blue_backend.type,
                                                                                           lto_blue_backend.direction,
                                                                                           lto_blue_backend.sm,
                                                                                           lto_blue_backend.elements_per_thread,
                                                                                           lto_blue_backend.min_elements_per_thread,
                                                                                           Precision,
                                                                                           Code>::selected_block_config_t;

            // Check if EPT is supported
            static constexpr bool is_ept_supported_v = !CUFFTDX_STD::is_void<selected_block_config_t>::value;
            static constexpr bool is_ept_supported_blue_v = !CUFFTDX_STD::is_void<selected_blue_block_config_t>::value;

            static constexpr bool is_lto_supported = cufftdx::detail::is_lto_config_supported<selected_block_config_t, BlockDimension> ();
            static constexpr bool is_lto_blue_supported = cufftdx::detail::is_lto_config_supported<selected_blue_block_config_t, BlockDimension> ();
        public:
            static constexpr bool value =
                ((Thread && is_supported_thread) ||                                                           // Thread
                (Block && is_supported_block && is_ept_supported_v && is_lto_supported) ||             // Block (with LTO check)
                (Block && is_supported_block_blue && requires_block_blue && is_ept_supported_blue_v && is_lto_blue_supported)); // Blue (with LTO check)
        };
    } // namespace detail

    // Check if description is supported on given Architecture
    template<class Description, unsigned int Architecture>
    struct is_supported:
        public CUFFTDX_STD::bool_constant<
            detail::is_supported_helper<precision_of_t<Description>,
                                        type_of<Description>::value,
                                        direction_of<Description>::value,
                                        size_of<Description>::value,
                                        detail::has_operator<fft_operator::block, Description>::value,
                                        detail::has_operator<fft_operator::thread, Description>::value,
                                        detail::get_t<fft_operator::elements_per_thread, Description>,
                                        real_fft_layout_of<Description>::value,
                                        real_fft_mode_of<Description>::value,
                                        experimental::code_type_of<Description>::value,
                                        detail::get_t<fft_operator::block_dim, Description>,
                                        Architecture>::value> {
    };

    template<class Description, unsigned int Architecture>
    inline constexpr bool is_supported_v = is_supported<Description, Architecture>::value;
} // namespace cufftdx

#endif // CUFFTDX_DETAIL_FFT_CHECKS_HPP
