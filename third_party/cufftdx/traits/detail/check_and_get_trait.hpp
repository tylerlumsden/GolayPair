// Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_TRAITS_DETAIL_CHECK_AND_GET_TRAIT_HPP
#define CUFFTDX_TRAITS_DETAIL_CHECK_AND_GET_TRAIT_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#    include <cuda/std/utility>
#else
#    include <type_traits>
#    include <utility>
#    include <tuple>
#endif

#include <cuda_fp16.h>

#include "cufftdx/operators.hpp"
#include "commondx/detail/expressions.hpp"
#include "cufftdx/database/database_definitions.hpp"
#include "cufftdx/database/fft_implementation_definitions.hpp"

#include "cufftdx/traits/fft_traits.hpp"
#include "cufftdx/traits/replace.hpp"

#include "cufftdx/traits/detail/description_traits.hpp"
#include "cufftdx/traits/detail/bluestein_helpers.hpp"
#include "cufftdx/traits/detail/frontend_backend_mappings.hpp"
#include "cufftdx/detail/support.hpp"


namespace cufftdx {
    namespace detail {
        template<fft_operator Operator, class Description>
        class check_and_get_trait;

        namespace get_block_config_impl {
            template<class Description, execution_type ExecType>
            class helper
            {
                // To suggest EPT and FPB (BPB) we need to know Size, Type, Direction, Precision + Architecture
                static constexpr bool is_complete = is_complete_description<Description>::value;
                static_assert(is_complete, "FFT description must be complete to calculate queried information");


                // Right now we go to Bluestein only if there's no CT implementation. User can't force Bluestein if
                // there is CT implementation.
#ifdef CUFFTDX_DETAIL_DISABLE_BLUESTEIN
                static constexpr bool is_bluestein_required_v  = false;
                static constexpr bool is_bluestein_supported_v = false;
#else
                static constexpr bool is_bluestein_required_v  = is_bluestein_required<size_of<Description>::value,
                                                                                       precision_of_t<Description>,
                                                                                       direction_of<Description>::value,
                                                                                       type_of<Description>::value,
                                                                                       sm_of<Description>::value,
                                                                                       real_fft_mode_of<Description>::value,
                                                                                       experimental::code_type_of<Description>::value>::value;
                static constexpr bool is_bluestein_supported_v = is_bluestein_supported<size_of<Description>::value>();
                // Check if we have implementation or bluestein which can do requested size
                static_assert(!is_bluestein_required_v || (is_bluestein_required_v && is_bluestein_supported_v),
                              "This FFT configuration is not supported");
#endif
                // Get if ept and block dim are defined
                static constexpr bool has_ept_defined       = has_operator<fft_operator::elements_per_thread, Description>::value;
                static constexpr bool has_block_dim_defined = has_operator<fft_operator::block_dim, Description>::value;

// ---- Bug Checks
#if CUFFTDX_BLOCK_DIM_UNSUPPORTED && !defined(CUFFTDX_IGNORE_BLOCK_DIM_UNSUPPORTED)
                static constexpr bool is_block_dim_unsuppported = has_block_dim_defined;

                static_assert(!is_block_dim_unsuppported,
                            "BlockDim operator is not officially supported with CUDA Toolkit 13.1.0 (NVCC 13.1.80) and earlier\n"
                            "For testing BlockDim on unsupported versions \n"
                            "you must define  CUFFTDX_IGNORE_BLOCK_DIM_UNSUPPORTED, \n"
                            "and add -Xptxas \"-O1\" to build your application. \n"
                            "When using unsupported CUDA Toolkit versions result correctness should be checked. \n"
                            "For more details please consult cuFFTDx documentation at https://docs.nvidia.com/cuda/cufftdx/release_notes.html");
                #endif

                //If no ept is defined and block dim is, we use block dim x to get the closest ept
                using this_fft_precision_t = precision_of_t<Description>;

                static constexpr auto ptx_backend = frontend_to_backend(is_bluestein_required_v ? algorithm::bluestein : algorithm::ct,
                                                                        execution_type::block,
                                                                        size_of<Description>::value,
                                                                        type_of<Description>::value,
                                                                        direction_of<Description>::value,
                                                                        sm_of<Description>::value,
                                                                        real_fft_mode_of<Description>::value,
                                                                        get_or_default_t<fft_operator::elements_per_thread, Description, ElementsPerThread<0>>::value,
                                                                        get_or_default_t<fft_operator::block_dim, Description, BlockDim<0, 0, 0>>::x,
                                                                        experimental::code_type::ptx);

                static constexpr auto lto_backend = frontend_to_backend(is_bluestein_required_v ? algorithm::bluestein : algorithm::ct,
                                                                        execution_type::block,
                                                                        size_of<Description>::value,
                                                                        type_of<Description>::value,
                                                                        direction_of<Description>::value,
                                                                        sm_of<Description>::value,
                                                                        real_fft_mode_of<Description>::value,
                                                                        get_or_default_t<fft_operator::elements_per_thread, Description, ElementsPerThread<0>>::value,
                                                                        get_or_default_t<fft_operator::block_dim, Description, BlockDim<0, 0, 0>>::x,
                                                                        experimental::code_type::ltoir);

                using optimal_block_config_t = typename database::detail::constexpr_db::constexpr_query_database<ptx_backend.size,
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
                                                                                                                 this_fft_precision_t,
                                                                                                                 experimental::code_type_of<Description>::value>::optimal_block_config_t;

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
                                                                                                                  this_fft_precision_t,
                                                                                                                  experimental::code_type_of<Description>::value>::selected_block_config_t;


                static constexpr auto backend = selected_block_config_t::code == experimental::code_type::ltoir ? lto_backend : ptx_backend;

                static_assert(!CUFFTDX_STD::is_void<selected_block_config_t>::value, "This FFT configuration is not supported");

                // If LTO is defined, we need to check if it's supported
                // LTO supports block dimension if version is >= the minimum supported version
                static constexpr bool lto_supports_block_dimension = cufftdx::detail::is_lto_config_supported<selected_block_config_t, detail::get_t<fft_operator::block_dim, Description>> ();


                static_assert(lto_supports_block_dimension, "BlockDim is not supported with experimental::code_type::ltoir. Use experimental::code_type::ptx instead.");


                static constexpr auto frontend = backend_to_frontend(execution_type::block,
                                                                     has_operator<fft_operator::elements_per_thread, Description>::value,
                                                                     type_of<Description>::value,
                                                                     real_fft_layout_of<Description>::value,
                                                                     real_fft_mode_of<Description>::value,
                                                                     map_precision<this_fft_precision_t>(),
                                                                     get_or_default_t<fft_operator::ffts_per_block, Description, FFTsPerBlock<0>>::value,
                                                                     backend.size,
                                                                     selected_block_config_t::elements_per_thread,
                                                                     selected_block_config_t::ffts_per_block,
                                                                     selected_block_config_t::shared_memory_size,
                                                                     selected_block_config_t::storage_size,
                                                                     optimal_block_config_t::elements_per_thread,
                                                                     optimal_block_config_t::ffts_per_block,
                                                                     has_operator<fft_operator::block_dim, Description>::value,
                                                                     get_or_default_t<fft_operator::block_dim, Description, BlockDim<0, 0, 0>>::x,
                                                                     get_or_default_t<fft_operator::block_dim, Description, BlockDim<0, 0, 0>>::y,
                                                                     get_or_default_t<fft_operator::block_dim, Description, BlockDim<0, 0, 0>>::z);

                // Note: optimal_fpb and suggested_fpb are not used as default fpb
                // For fp16 FPB must be even, each thread processes two half complex numbers
                static_assert(!CUFFTDX_STD::is_same<this_fft_precision_t, __half>::value || (frontend.ffts_per_block % 2 == 0), "FP16 block FFT can only process even number of FFTs per block");

            public:
                using elements_per_thread = ElementsPerThread<frontend.elements_per_thread>;
                using block_dim           = BlockDim<frontend.block_dim_x, frontend.block_dim_y, frontend.block_dim_z>;
                using ffts_per_block      = FFTsPerBlock<frontend.ffts_per_block>;
                using fft_implementation  = selected_block_config_t;

                using suggested_elements_per_thread = ElementsPerThread<frontend.suggested_elements_per_thread>;
                using effective_elements_per_thread = ElementsPerThread<selected_block_config_t::elements_per_thread>;
                using suggested_ffts_per_block      = FFTsPerBlock<frontend.suggested_ffts_per_block>;
                using suggested_block_dim           = BlockDim<frontend.suggested_block_dim_x, frontend.suggested_block_dim_y, frontend.suggested_block_dim_z>;

                using complex_type                               = typename make_complex_type<precision_of_t<Description>>::cufftdx_type;
                static constexpr bool         use_bluestein      = is_bluestein_required_v;
                static constexpr bool         requires_workspace = is_bluestein_required_v;
                static constexpr unsigned int workspace_size     = is_bluestein_required_v ? 2 * backend.size * sizeof(complex_type) : 0;

                static constexpr experimental::code_type code = selected_block_config_t::code;

                static constexpr unsigned int shared_memory_size = frontend.shared_memory_size;
                static constexpr unsigned int storage_size       = frontend.storage_size;
                static constexpr unsigned int stride             = frontend.stride;
                static constexpr unsigned int input_ept          = frontend.input_elements_per_thread;
                static constexpr unsigned int output_ept         = frontend.output_elements_per_thread;

                // This is internal, no need to expose it in frontend
                static constexpr unsigned int num_syncs = selected_block_config_t::num_syncs;

            private:
                // Checks
                static_assert(!is_bluestein_required_v || (backend.size >= (2 * size_of<Description>::value - 1)),
                              "cuFFTDx internal error, selected Bluestein size is too small");
                static_assert(!is_bluestein_required_v || (backend.size <= (4 * size_of<Description>::value - 3)),
                              "cuFFTDx internal error, selected Bluestein size is too big");


                static constexpr unsigned int threads_per_fft = selected_block_config_t::threads_per_fft;

                // Checks
                static constexpr bool has_block_dim = has_operator<fft_operator::block_dim, Description>::value;

                // SIZE % EPT == 0
                static constexpr bool ept_is_factor_of_size = (backend.size % effective_elements_per_thread::value) == 0;
                static_assert(ept_is_factor_of_size, "Elements per thread must be a factor of FFT size");

                // SIZE * FFTS_PER_BLOCK <= EPT * FLAT_BLOCK_SIZE
                static constexpr auto max_elements_processed_per_block =
                    block_dim::flat_size * effective_elements_per_thread::value *
                    (CUFFTDX_STD::is_same<this_fft_precision_t, __half>::value ? 2 : 1);
                static constexpr auto elements_to_process_per_block = backend.size * ffts_per_block::value;
                static_assert(elements_to_process_per_block <= max_elements_processed_per_block,
                              "Not enough threads in block to calculate FFT, you need to increase BlockDim<> or "
                              "ElementsPerThread<>");

                // Can not generate a description that requires more than 1024 threads per block
                static_assert(block_dim::flat_size <= 1024, "Too many threads requested. This FFT configuration is not supported, "
                              "increase ElementsPerThread<>, BlockDim<>, or reduce FFTSPerBlock<>.");

                // Check each block dim dimension
                static_assert(block_dim::x >= threads_per_fft, "BlockDim::x must be greater than default block_dim.x");
                static_assert(block_dim::y >= ffts_per_block::value / get_implicit_type_batching(map_precision<this_fft_precision_t>()), "BlockDim::y must be greater than default block_dim.y");
                static_assert(block_dim::z >= 1, "BlockDim::z must be greater than default block_dim.z");


                //Either EPT is a factor of size or BlockDim is specified
                static_assert(ept_is_factor_of_size || has_block_dim,
                              "Elements per thread must be a factor of FFT size");
            };

            template<class Description>
            class helper<Description, execution_type::thread>
            {
                // To suggest EPT we need to know Size, Type, Direction, Precision + Architecture
                static constexpr bool is_complete = is_complete_description<Description>::value;
                static_assert(is_complete, "FFT description must be complete to calculate queried information");

                using this_fft_precision_t = precision_of_t<Description>;

                static constexpr auto ptx_backend = frontend_to_backend(algorithm::ct,
                                                                        execution_type::thread,
                                                                        size_of<Description>::value,
                                                                        type_of<Description>::value,
                                                                        direction_of<Description>::value,
                                                                        0 /* sm */,
                                                                        real_fft_mode_of<Description>::value,
                                                                        0 /* elements_per_thread */,
                                                                        0 /* block_dim_x */,
                                                                        experimental::code_type::ptx);

                static constexpr auto lto_backend = frontend_to_backend(algorithm::ct,
                                                                        execution_type::thread,
                                                                        size_of<Description>::value,
                                                                        type_of<Description>::value,
                                                                        direction_of<Description>::value,
                                                                        0 /* sm */,
                                                                        real_fft_mode_of<Description>::value,
                                                                        0 /* elements_per_thread */,
                                                                        0, /* block_dim_x */
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
                                                                                                                  this_fft_precision_t,
                                                                                                                  experimental::code_type_of<Description>::value>::selected_block_config_t;

                static_assert(!CUFFTDX_STD::is_void<selected_block_config_t>::value, "This FFT configuration is not supported");

                static constexpr auto backend = selected_block_config_t::code == experimental::code_type::ltoir ? lto_backend : ptx_backend;

                static constexpr auto frontend = backend_to_frontend(execution_type::thread,
                                                                     has_operator<fft_operator::elements_per_thread, Description>::value,
                                                                     type_of<Description>::value,
                                                                     real_fft_layout_of<Description>::value,
                                                                     real_fft_mode_of<Description>::value,
                                                                     map_precision<this_fft_precision_t>(),
                                                                     0 /* ffts_per_block */,
                                                                     backend.size,
                                                                     selected_block_config_t::elements_per_thread,
                                                                     selected_block_config_t::ffts_per_block,
                                                                     selected_block_config_t::shared_memory_size,
                                                                     selected_block_config_t::storage_size,
                                                                     selected_block_config_t::elements_per_thread /* optimal_elements_per_thread */,
                                                                     selected_block_config_t::ffts_per_block /* optimal_ffts_per_block */,
                                                                     has_operator<fft_operator::block_dim, Description>::value,
                                                                     get_or_default_t<fft_operator::block_dim, Description, BlockDim<0, 0, 0>>::x,
                                                                     get_or_default_t<fft_operator::block_dim, Description, BlockDim<0, 0, 0>>::y,
                                                                     get_or_default_t<fft_operator::block_dim, Description, BlockDim<0, 0, 0>>::z);

            public:
                using elements_per_thread           = ElementsPerThread<frontend.elements_per_thread>;
                using suggested_elements_per_thread = ElementsPerThread<frontend.suggested_elements_per_thread>;
                using effective_elements_per_thread = ElementsPerThread<selected_block_config_t::elements_per_thread>;
                using fft_implementation            = selected_block_config_t;

                static constexpr bool                    use_bluestein      = false;
                static constexpr bool                    requires_workspace = false;
                static constexpr unsigned int            workspace_size     = 0;
                static constexpr experimental::code_type code               = selected_block_config_t::code;
                static constexpr unsigned int            shared_memory_size = frontend.shared_memory_size;
                static constexpr unsigned int            storage_size       = frontend.storage_size;
                static constexpr unsigned int            stride             = frontend.stride;
                static constexpr unsigned int            input_ept          = frontend.input_elements_per_thread;
                static constexpr unsigned int            output_ept         = frontend.output_elements_per_thread;
                static constexpr unsigned int            num_syncs          = 0;


            private:
                static_assert(shared_memory_size == 0, "Shared memory size must be 0 for thread execution");
                static_assert(stride == 1, "Stride must be 1 for thread execution");
            };
        } // namespace get_block_config_impl

        template<class Description>
        class check_and_get_trait<fft_operator::block_dim, Description>
        {
            // FAIL if it's not a block execution
            static constexpr bool is_block_execution = has_operator<fft_operator::block, Description>::value;
            static_assert(is_block_execution, "Must be block execution to get ::block_dim trait");

        public:
            using type                      = typename get_block_config_impl::helper<Description, execution_type::block>::block_dim;
            using suggested_type            = typename get_block_config_impl::helper<Description, execution_type::block>::suggested_block_dim;
            static constexpr dim3 value     = type::value;
            static constexpr dim3 suggested = suggested_type::value;
        };

        template<class Description>
        class check_and_get_trait<fft_operator::elements_per_thread, Description>
        {
            // FAIL if it's not a block execution
            static constexpr bool is_block_execution  = has_operator<fft_operator::block, Description>::value;
            static constexpr bool is_thread_execution = has_operator<fft_operator::thread, Description>::value;
            static_assert(is_block_execution || is_thread_execution,
                          "FFT must be define as either thread of block execution to get ::elements_per_thread trait");
            static constexpr execution_type exec = is_thread_execution ? execution_type::thread : execution_type::block;

        public:
            using type                          = typename get_block_config_impl::helper<Description, exec>::elements_per_thread;
            static constexpr unsigned int value = type::value;

            using effective_ept_type                = typename get_block_config_impl::helper<Description, exec>::effective_elements_per_thread;
            static constexpr unsigned int effective = effective_ept_type::value;

            using suggested_ept_type                = typename get_block_config_impl::helper<Description, exec>::suggested_elements_per_thread;
            static constexpr unsigned int suggested = suggested_ept_type::value;

            static constexpr unsigned int input  = get_block_config_impl::helper<Description, exec>::input_ept;
            static constexpr unsigned int output = get_block_config_impl::helper<Description, exec>::output_ept;
        };

        template<class Description>
        class check_and_get_trait<fft_operator::ffts_per_block, Description>
        {
            // FAIL if it's not a block execution
            static constexpr bool is_block_execution = has_operator<fft_operator::block, Description>::value;
            static_assert(is_block_execution, "Must be block execution to get ::ffts_per_block trait");

        public:
            using type                          = typename get_block_config_impl::helper<Description, execution_type::block>::ffts_per_block;
            static constexpr unsigned int value = type::value;

            using suggested_type                    = typename get_block_config_impl::helper<Description, execution_type::block>::suggested_ffts_per_block;
            static constexpr unsigned int suggested = suggested_type::value;
        };

        template<class Description>
        class check_and_get_fft_implementation
        {
            // FAIL if it's not a block execution
            static constexpr bool is_block_execution  = has_operator<fft_operator::block, Description>::value;
            static constexpr bool is_thread_execution = has_operator<fft_operator::thread, Description>::value;
            static_assert(is_block_execution || is_thread_execution,
                          "FFT must be define as either thread of block execution to get ::elements_per_thread trait");
            static constexpr execution_type exec = is_thread_execution ? execution_type::thread : execution_type::block;

            using block_config_t = get_block_config_impl::helper<Description, exec>;

        public:
            using type = typename block_config_t::fft_implementation;

            static constexpr bool                    use_bluestein      = block_config_t::use_bluestein;
            static constexpr bool                    requires_workspace = block_config_t::requires_workspace;
            static constexpr unsigned int            workspace_size     = block_config_t::workspace_size;
            static constexpr experimental::code_type code               = block_config_t::code;
            static constexpr unsigned int            shared_memory_size = block_config_t::shared_memory_size;
            ;
            static constexpr unsigned int storage_size = block_config_t::storage_size;
            static constexpr unsigned int stride       = block_config_t::stride;
            static constexpr unsigned int num_syncs    = block_config_t::num_syncs;
        };

        /// Alias template for check_and_get_fft_implementation_t<Description>::type
        template<class Description>
        using check_and_get_fft_implementation_t = typename check_and_get_fft_implementation<Description>::type;
    } // namespace detail
} // namespace cufftdx

#endif // CUFFTDX_TRAITS_DETAIL_CHECK_AND_GET_TRAIT_HPP
