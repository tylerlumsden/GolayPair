// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DETAIL_CONSTEXPR_DATABASE_HPP
#define CUFFTDX_DATABASE_DETAIL_CONSTEXPR_DATABASE_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#    include <cuda/std/array>
#    include <cuda/std/utility>
#else
#    include <array>
#    include <utility>
#    include <type_traits>
#endif

#include <cuda_fp16.h>


#include "cufftdx/database/detail/block_fft.hpp"
#include "cufftdx/database/detail/optional.hpp"
#include "cufftdx/operators/type.hpp"
#include "cufftdx/operators/direction.hpp"
#include "cufftdx/operators/precision.hpp"
#include "cufftdx/operators/experimental/code_type.hpp"

namespace cufftdx {
    namespace database {
        namespace detail {
            namespace constexpr_db {

                // Helper functions for querying the database
                template<size_t N, unsigned int MaxImpls>
                constexpr detail::optional<unsigned int> find_record_index(const CUFFTDX_STD::array<database_record<MaxImpls>, N>& database,
                                               const database_key& key) {
                    if constexpr (N == 0) {
                        return detail::optional<unsigned int>();  // Empty database, no records to find
                    } else {
                        for (size_t i = 0; i < N; ++i) {
                            if (database[i].key == key) {
                                return detail::optional<unsigned int>(static_cast<unsigned int>(i));
                            }
                        }
                        return detail::optional<unsigned int>();
                    }
                }

                template<size_t N, unsigned int MaxImpls>
                constexpr const database_record<MaxImpls>* find_record(const CUFFTDX_STD::array<database_record<MaxImpls>, N>& database,
                                                                      const database_key& key) {
                    auto index = find_record_index<N, MaxImpls>(database, key);
                    return index.has_value() ? &database[index.value()] : nullptr;
                }

                // Helper function to get precision size
                constexpr size_t get_precision_size(precision prec) {
                    switch (prec) {
                        case precision::f16: return sizeof(__half);
                        case precision::f32: return sizeof(float);
                        case precision::f64: return sizeof(double);
                        default: return sizeof(float); // fallback
                    }
                }

                // Implementation selection logic
                constexpr bool check_trp_constraint(const implementation_info& impl, transposition trp_option, precision prec) {
                    if (impl.threads_per_fft == 1) {
                        return true; // Single-thread FFTs don't need TRP constraints
                    }

                    const size_t precision_size = get_precision_size(prec);
                    switch (trp_option) {
                        case transposition::undefined:
                            return true;
                        case transposition::none:
                            return impl.shared_memory_size == 0;
                        case transposition::x:
                            return (precision_size * impl.elements_per_thread * impl.threads_per_fft) ==
                                   impl.shared_memory_size;
                        case transposition::xy:
                            return (precision_size * 2 * impl.elements_per_thread * impl.threads_per_fft) ==
                                   impl.shared_memory_size;
                    }
                    return false;
                }

                template<unsigned int MaxImpls>
                constexpr detail::optional<implementation_info> find_implementation_by_ept(
                    const database_record<MaxImpls>& record,
                    unsigned int                     elements_per_thread,
                    transposition                    trp_option,
                    precision                        prec) {

                    for (unsigned int i = 0; i < record.num_implementations; ++i) {
                        const auto& impl = record.implementations[i];
                        if (impl.elements_per_thread == elements_per_thread &&
                            check_trp_constraint(impl, trp_option, prec)) {
                            return detail::optional<implementation_info>(impl);
                        }
                    }
                    return detail::optional<implementation_info>();
                }

                template<unsigned int MaxImpls>
                constexpr detail::optional<implementation_info> find_implementation_by_min_ept(
                    const database_record<MaxImpls>& record,
                    unsigned int                     min_elements_per_thread,
                    transposition                    trp_option,
                    precision                        prec) {

                    for (unsigned int i = 0; i < record.num_implementations; ++i) {
                        const auto& impl = record.implementations[i];
                        if (impl.elements_per_thread >= min_elements_per_thread &&
                            check_trp_constraint(impl, trp_option, prec)) {
                            return detail::optional<implementation_info>(impl);
                        }
                    }
                    return detail::optional<implementation_info>();
                }

                template<unsigned int MaxImpls>
                constexpr const implementation_info* get_optimal_implementation(
                    const database_record<MaxImpls>& record) {

                    if (record.num_implementations > 0) {
                        return &record.implementations[0]; // First implementation is considered optimal
                    }
                    return nullptr;
                }

                // Query result structure
                struct query_result {
                    detail::optional<implementation_info> optimal;
                    detail::optional<implementation_info> selected;
                    bool found;

                    constexpr query_result():
                        optimal(), selected(), found(false) {}
                    constexpr query_result(const detail::optional<implementation_info>& opt, const detail::optional<implementation_info>& sel):
                        optimal(opt), selected(sel), found(sel.has_value()) {}
                };

                // Main constexpr query function
                template<unsigned int N, unsigned int MaxImpls>
                constexpr query_result query_constexpr_database(
                    const CUFFTDX_STD::array<database_record<MaxImpls>, N>& database,
                    unsigned int                                            size,
                    fft_type                                                type,
                    fft_direction                                           direction,
                    unsigned int                                            architecture,
                    experimental::code_type                                 code_type,
                    precision                                               prec,
                    unsigned int                                            elements_per_thread     = 0,
                    unsigned int                                            min_elements_per_thread = 0,
                    transposition                                           trp_option              = transposition::undefined) {

                    // Create database key
                    database_key key {
                        size,
                        prec,
                        type,
                        direction,
                        architecture,
                        code_type};

                    auto record_index = find_record_index<N, MaxImpls>(database, key);
                    if (!record_index.has_value()) {
                        return query_result {};
                    }

                    const auto& record = database[record_index.value()];

                    // No implementations found, return empty result
                    if (record.num_implementations == 0) {
                        return query_result {};
                    }

                    // Find first implementation with EPT >= min_elements_per_thread. If min_elements_per_thread is 0, return the first implementation.
                    auto optimal = find_implementation_by_min_ept<MaxImpls>(record, min_elements_per_thread, trp_option, prec);

                    // Select implementation based on criteria
                    if (elements_per_thread != 0) {
                        // Exact EPT match requested
                        if (min_elements_per_thread > elements_per_thread) {
                            // Contradiction: can't satisfy both constraints
                            return query_result {optimal, detail::optional<implementation_info>()};
                        } else {
                            return query_result {optimal, find_implementation_by_ept<MaxImpls>(record, elements_per_thread, trp_option, prec)};
                        }
                    } else {
                        // Minimum EPT constraint
                        return query_result {optimal, optimal};
                    }
                }

            } // namespace constexpr_db
        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_DETAIL_CONSTEXPR_DATABASE_HPP
