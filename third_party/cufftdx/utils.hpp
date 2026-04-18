// Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_UTILS_HPP
#define CUFFTDX_UTILS_HPP

#if !defined(__CUDACC_RTC__)
#    include <vector>
#endif

#include "cufftdx/traits/detail/frontend_backend_mappings.hpp"
#include "cufftdx/database/detail/database_query.hpp"
#if defined(__CUDACC__) || defined(__CUDACC_RTC__)
#    include "cufftdx/traits/fft_traits.hpp"
#endif
namespace cufftdx {
    namespace utils {
        using detail::algorithm;
        using detail::backend_impl_traits;
        using detail::execution_type;
        using detail::frontend_impl_traits;
        using detail::frontend_to_backend;
    } // namespace utils
    namespace experimental {
        namespace utils {
            constexpr unsigned int get_shared_memory_size_for_dynamic_batching(const unsigned int shared_memory_size_per_fft, const unsigned int ffts_per_block, const unsigned int implicit_type_batching) {
                return (implicit_type_batching != 0) ? (shared_memory_size_per_fft * (ffts_per_block + implicit_type_batching - 1) / implicit_type_batching) : 0;
            }

#if defined(__CUDACC__) || defined(__CUDACC_RTC__)
            template<class FFT>
            constexpr unsigned int get_shared_memory_size_for_dynamic_batching(const unsigned int ffts_per_block) {
                static_assert(cufftdx::experimental::is_dynamic_batching_enabled_v<FFT>, "Dynamic batching is not enabled for this FFT");
                return get_shared_memory_size_for_dynamic_batching(FFT::shared_memory_size, ffts_per_block, FFT::implicit_type_batching);
            }
#endif

#if defined CUFFTDX_ENABLE_RUNTIME_DATABASE
            inline std::optional<cufftdx::utils::frontend_impl_traits> query_database(unsigned                                             fft_size,
                                                                               fft_direction                                        dir,
                                                                               fft_type                                             type,
                                                                               unsigned                                             sm,
                                                                               cufftdx::utils::execution_type                       execution,
                                                                               precision                                            prec      = precision::f32,
                                                                               unsigned                                             fft_ept   = 0,
                                                                               unsigned                                             fpb       = 0,
                                                                               std::tuple<unsigned int, unsigned int, unsigned int> block_dim = {0, 0, 0},
                                                                               complex_layout                                       layout    = complex_layout::natural,
                                                                               real_mode                                            rmode     = real_mode::normal,
                                                                               experimental::code_type                              code_type = cufftdx::experimental::code_type::ptx) {

                bool has_block_dim = std::get<0>(block_dim) > 0 || std::get<1>(block_dim) > 0 || std::get<2>(block_dim) > 0;
                auto backend       = cufftdx::utils::frontend_to_backend(cufftdx::utils::algorithm::ct,
                                                                   execution,
                                                                   fft_size,
                                                                   type,
                                                                   dir,
                                                                   sm,
                                                                   rmode,
                                                                   fft_ept,
                                                                   std::get<0>(block_dim),
                                                                   code_type);

                auto query_result = database::detail::constexpr_db::runtime_query_database::query_runtime(backend.size,
                                                                                                          backend.type,
                                                                                                          backend.direction,
                                                                                                          backend.sm,
                                                                                                          prec,
                                                                                                          code_type,
                                                                                                          backend.elements_per_thread,
                                                                                                          backend.min_elements_per_thread);

                if (query_result.found) {
                    const auto& selected_impl    = *query_result.selected;
                    auto        returned_traits = cufftdx::detail::backend_to_frontend(execution,
                                                                                fft_ept > 0 ? true : false,
                                                                                backend.type,
                                                                                layout,
                                                                                rmode,
                                                                                prec,
                                                                                fpb,
                                                                                backend.size,
                                                                                selected_impl.elements_per_thread,
                                                                                selected_impl.ffts_per_block,
                                                                                selected_impl.shared_memory_size,
                                                                                selected_impl.storage_size,
                                                                                selected_impl.elements_per_thread,
                                                                                selected_impl.ffts_per_block,
                                                                                has_block_dim,
                                                                                has_block_dim ? std::get<0>(block_dim) : 0,
                                                                                has_block_dim ? std::get<1>(block_dim) : 0,
                                                                                has_block_dim ? std::get<2>(block_dim) : 0);
                    return returned_traits;
                }
                return std::nullopt;
            }

            inline std::vector<cufftdx::utils::frontend_impl_traits> get_all_implementations(unsigned                                             fft_size,
                                                                                      fft_direction                                        dir,
                                                                                      fft_type                                             type,
                                                                                      unsigned                                             sm,
                                                                                      cufftdx::utils::execution_type                       execution,
                                                                                      precision                                            prec      = precision::f32,
                                                                                      unsigned                                             fft_ept   = 0,
                                                                                      unsigned                                             fpb       = 0,
                                                                                      std::tuple<unsigned int, unsigned int, unsigned int> block_dim = {0, 0, 0},
                                                                                      complex_layout                                       layout    = complex_layout::natural,
                                                                                      real_mode                                            rmode     = real_mode::normal,
                                                                                      experimental::code_type                              code_type = cufftdx::experimental::code_type::ptx) {
                bool has_block_dim = std::get<0>(block_dim) > 0 || std::get<1>(block_dim) > 0 || std::get<2>(block_dim) > 0;
                auto backend       = cufftdx::utils::frontend_to_backend(cufftdx::utils::algorithm::ct,
                                                                   execution,
                                                                   fft_size,
                                                                   type,
                                                                   dir,
                                                                   sm,
                                                                   rmode,
                                                                   fft_ept,
                                                                   std::get<0>(block_dim),
                                                                   code_type);

                auto possible_implementations = database::detail::constexpr_db::runtime_query_database::query_all_entries_runtime(backend.size,
                                                                                                                                  backend.type,
                                                                                                                                  backend.direction,
                                                                                                                                  backend.sm,
                                                                                                                                  prec,
                                                                                                                                  code_type,
                                                                                                                                  backend.elements_per_thread,
                                                                                                                                  backend.min_elements_per_thread);
                std::vector<cufftdx::utils::frontend_impl_traits> returned_traits;
                for (const auto& implementation : possible_implementations) {
                    returned_traits.push_back(cufftdx::detail::backend_to_frontend(execution,
                                                                                   fft_ept > 0 ? true : false,
                                                                                   backend.type,
                                                                                   layout,
                                                                                   rmode,
                                                                                   prec,
                                                                                   fpb,
                                                                                   backend.size,
                                                                                   implementation.elements_per_thread,
                                                                                   implementation.ffts_per_block,
                                                                                   implementation.shared_memory_size,
                                                                                   implementation.storage_size,
                                                                                   implementation.elements_per_thread,
                                                                                   implementation.ffts_per_block,
                                                                                   has_block_dim,
                                                                                   has_block_dim ? std::get<0>(block_dim) : 0,
                                                                                   has_block_dim ? std::get<1>(block_dim) : 0,
                                                                                   has_block_dim ? std::get<2>(block_dim) : 0));
                }
                return returned_traits;
            }
#endif // CUFFTDX_ENABLE_RUNTIME_DATABASE
        } // namespace utils
    } // namespace experimental
} // namespace cufftdx
#ifdef CUFFTDX_ENABLE_CUFFT_DEPENDENCY
#    include "cufftdx/utils/cufft_lto.hpp"
#endif

#endif // CUFFTDX_UTILS_HPP
