// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DETAIL_CONSTEXPR_QUERY_HPP
#define CUFFTDX_DATABASE_DETAIL_CONSTEXPR_QUERY_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#    include <cuda/std/array>
#    include <cuda/std/utility>
#else
#include <array>
#include <utility>
#include <type_traits>
#endif
#include "cufftdx/operators/transposition.hpp"
#include "constexpr_database.hpp"
#include "block_fft.hpp"

namespace cufftdx {
    namespace database {
        namespace detail {
            namespace constexpr_db {

                // Compile-time optimized query_database that uses direct record access
                // This version only instantiates the specific record needed, avoiding the full database_selector
                template<unsigned int PTXSize,
                         fft_type PTXType,
                         fft_direction PTXDirection,
                         unsigned int PTXArchitecture,
                         unsigned int PTXElementsPerThread,
                         unsigned int PTXMinElementsPerThread,
                         unsigned int LTOSize,
                         fft_type LTOType,
                         fft_direction LTODirection,
                         unsigned int LTOArchitecture,
                         unsigned int LTOElementsPerThread,
                         unsigned int LTOMinElementsPerThread,
                         typename PrecisionType,
                         experimental::code_type CodeType>
                struct constexpr_query_database {
                private:
                    // Compile-time optimized database access - creates single-record database directly
                    // This avoids instantiating the full database_selector for compile-time usage
                    template<experimental::code_type CT, unsigned int Size, fft_type Type, fft_direction Direction, unsigned int Architecture>
                    static constexpr auto get_compile_time_database() {
                        return make_single_record_database<Size, PrecisionType, Type, Direction, Architecture, CT, 0>();
                    }

                    static constexpr transposition trp_option =
                    #ifdef CUFFTDX_DETAIL_BLOCK_FFT_ENFORCE_X_TRANSPOSITION
                    transposition::x;
                    #elif defined(CUFFTDX_DETAIL_BLOCK_FFT_ENFORCE_XY_TRANSPOSITION)
                    transposition::xy;
                    #else
                    transposition::undefined;
                    #endif

                    static constexpr precision prec = cufftdx::detail::map_precision<PrecisionType>();


                    // For compile-time evaluation, use the optimized single-record database
                    static constexpr auto lto_database = get_compile_time_database<experimental::code_type::ltoir, LTOSize, LTOType, LTODirection, LTOArchitecture>();
                    static constexpr auto ptx_database = get_compile_time_database<experimental::code_type::ptx, PTXSize, PTXType, PTXDirection, PTXArchitecture>();

                    // LTO: query the database
                    static constexpr unsigned int max_impls_lto = lto_database.size() > 0 ?
                        CUFFTDX_STD::tuple_size<decltype(lto_database[0].implementations)>::value : 0;

                    static constexpr auto lto_result = lto_database.size() > 0 ?
                        query_constexpr_database<lto_database.size(), max_impls_lto>(
                            lto_database, LTOSize, LTOType, LTODirection, LTOArchitecture, experimental::code_type::ltoir, prec, LTOElementsPerThread, LTOMinElementsPerThread, static_cast<transposition>(trp_option)) :
                        query_result{};

                    // PTX: query the database
                    static constexpr unsigned int ptx_max_impls = ptx_database.size() > 0 ?
                        CUFFTDX_STD::tuple_size<decltype(ptx_database[0].implementations)>::value : 0;

                    static constexpr auto ptx_result = ptx_database.size() > 0 ?
                        query_constexpr_database<ptx_database.size(), ptx_max_impls>(
                            ptx_database, PTXSize, PTXType, PTXDirection, PTXArchitecture, experimental::code_type::ptx, prec, PTXElementsPerThread, PTXMinElementsPerThread, static_cast<transposition>(trp_option)) :
                        query_result{};

                    // If code type is LTO and the result is not empty, use the LTO result, otherwise use the PTX result
                    static constexpr auto result = (CodeType == experimental::code_type::ltoir && lto_result.selected.has_value()) ? lto_result : ptx_result;

                    // Create implementations from optional results
                    static constexpr implementation_info dummy_impl{0, 0, 0, 0, 0, 0, 0, 0, experimental::code_type::ptx, 0};
                    static constexpr implementation_info optimal_impl = result.optimal.value_or(dummy_impl);
                    static constexpr implementation_info selected_impl = result.selected.value_or(dummy_impl);


                    static constexpr unsigned int size = selected_impl.code_type == experimental::code_type::ltoir ? LTOSize : PTXSize;
                    static constexpr fft_type type = selected_impl.code_type == experimental::code_type::ltoir ? LTOType : PTXType;
                    static constexpr fft_direction direction = selected_impl.code_type == experimental::code_type::ltoir ? LTODirection : PTXDirection;
                    static constexpr unsigned int architecture = selected_impl.code_type == experimental::code_type::ltoir ? LTOArchitecture : PTXArchitecture;

                public:

                    using optimal_block_config_t = CUFFTDX_STD::conditional_t<
                        result.optimal.has_value(),
                        implementation_info_as_type<optimal_impl>,
                        void
                    >;

                    using selected_block_config_t = CUFFTDX_STD::conditional_t<
                        result.selected.has_value(),
                        implementation_info_as_type<selected_impl>,
                        void
                    >;

                    using min_ept_greater_than_t = selected_block_config_t; // For compatibility

                    // Need to return the entry in the database if defined
                    using block_fft_record_t = block_fft_record<size, PrecisionType, type, direction, architecture, selected_impl.code_type>;

                };

                // Convenience alias that matches the original find_min_ept_implementation_t
                template<unsigned int PTXSize,
                         fft_type PTXType,
                         fft_direction PTXDirection,
                         unsigned int PTXArchitecture,
                         unsigned int PTXElementsPerThread,
                         unsigned int PTXMinElementsPerThread,
                         unsigned int LTOSize,
                         fft_type LTOType,
                         fft_direction LTODirection,
                         unsigned int LTOArchitecture,
                         unsigned int LTOElementsPerThread,
                         unsigned int LTOMinElementsPerThread,
                         typename PrecisionType,
                         experimental::code_type CodeType = experimental::code_type::ptx>
                using find_min_ept_implementation_t =
                    typename constexpr_query_database<PTXSize, PTXType, PTXDirection, PTXArchitecture,
                                                     PTXElementsPerThread, PTXMinElementsPerThread,
                                                     LTOSize, LTOType, LTODirection, LTOArchitecture,
                                                     LTOElementsPerThread, LTOMinElementsPerThread,
                                                     PrecisionType, CodeType>::min_ept_greater_than_t;

                // Convenience alias for the query_database template used in tests
                template<unsigned int PTXSize,
                         fft_type PTXType,
                         fft_direction PTXDirection,
                         unsigned int PTXArchitecture,
                         unsigned int PTXElementsPerThread,
                         unsigned int PTXMinElementsPerThread,
                         unsigned int LTOSize,
                         fft_type LTOType,
                         fft_direction LTODirection,
                         unsigned int LTOArchitecture,
                         unsigned int LTOElementsPerThread,
                         unsigned int LTOMinElementsPerThread,
                         typename PrecisionType,
                         experimental::code_type CodeType = experimental::code_type::ptx>
                using query_database = constexpr_query_database<PTXSize, PTXType, PTXDirection, PTXArchitecture,
                                                               PTXElementsPerThread, PTXMinElementsPerThread,
                                                               LTOSize, LTOType, LTODirection, LTOArchitecture,
                                                               LTOElementsPerThread, LTOMinElementsPerThread,
                                                               PrecisionType, CodeType>;

            } // namespace constexpr_db
        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_DETAIL_CONSTEXPR_QUERY_HPP

