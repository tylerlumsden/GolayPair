// Copyright (c) 2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DETAIL_RUNTIME_QUERY_HPP
#define CUFFTDX_DATABASE_DETAIL_RUNTIME_QUERY_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#    include <cuda/std/array>
#    include <cuda/std/utility>
#else
#    include <array>
#    include <utility>
#    include <type_traits>
#endif

#include <vector>
#include <unordered_set>

#include "cufftdx/operators/transposition.hpp"
#include "constexpr_database.hpp"
#include "block_fft.hpp"
#include "cufftdx/database/records/all_databases.hpp.inc"

namespace cufftdx {
    namespace database {
        namespace detail {
            namespace constexpr_db {

                // Helper to create the flattened array
                constexpr auto make_all_records() {
                    constexpr const auto& databases = get_all_databases();

                    // Calculate total size
                    constexpr size_t total_size = CUFFTDX_STD::apply(
                        [](auto&&... db) { return (db.size() + ... + 0); },
                        databases);

                    // Create result array
                    CUFFTDX_STD::array<database_record<max_implementations>, total_size> result {};
                    size_t                                                               index = 0;

                    // Flatten all databases into single array using constexpr-compatible approach
                    CUFFTDX_STD::apply([&result, &index](auto&&... db) {
                        auto copy_db = [&result, &index](const auto& database) {
                            for (size_t i = 0; i < database.size(); ++i) {
                                result[index + i] = database[i];
                            }
                            index += database.size();
                        };
                        (copy_db(db), ...);
                    },
                                       databases);

                    return result;
                }

                // Store all records as a single flat array
                // WARNING: This instantiates ALL database templates
                inline constexpr auto all_records = make_all_records();

                // Function to get all records - returns reference to pre-computed array (no instantiation overhead)
                constexpr const auto& get_all_records() {
                    return all_records;
                }

                // Function to search for a specific record at runtime
                template<typename PrecisionType, unsigned int Architecture, fft_direction Direction>
                constexpr auto find_record_runtime(unsigned int size) {
                    constexpr const auto& all_records = get_all_records();

                    // Convert PrecisionType to precision enum
                    constexpr precision prec = cufftdx::detail::map_precision<PrecisionType>();

                    for (const auto& record : all_records) {
                        if (record.key.match(size, record.key.type, Direction, Architecture, prec,
                                             record.key.code_type)) {
                            return record;
                        }
                    }

                    // Return empty record if not found
                    return database_record<max_implementations> {};
                }

                // Convenience function to get database count
                constexpr size_t get_database_count() {
                    using db_type = typename std::remove_reference<decltype(get_all_databases())>::type;
                    return CUFFTDX_STD::tuple_size<db_type>::value;
                }

                // Function to get total record count across all databases
                constexpr size_t get_total_record_count() {
                    return get_all_records().size();
                }

                // This is only needed when runtime FFT parameter queries are required
                struct runtime_query_database {
                public:
                    // Runtime query function - uses get_all_records() for flexible querying
                    static auto query_runtime(
                        unsigned int            runtime_size,
                        fft_type                runtime_type,
                        fft_direction           runtime_direction,
                        unsigned int            runtime_architecture,
                        precision               runtime_precision,
                        experimental::code_type runtime_code_type,
                        unsigned int            runtime_ept                         = 0,
                        unsigned int            runtime_min_ept                     = 0,
                        unsigned int            runtime_trp_option [[maybe_unused]] = 0) {

                        static const auto    runtime_db = get_all_records();
                        constexpr transposition trp_option =
#ifdef CUFFTDX_DETAIL_BLOCK_FFT_ENFORCE_X_TRANSPOSITION
                            transposition::x;
#elif defined(CUFFTDX_DETAIL_BLOCK_FFT_ENFORCE_XY_TRANSPOSITION)
                            transposition::xy;
#else
                            transposition::undefined;
#endif
                        // Extract MaxImplementations from the runtime database type
                        constexpr unsigned int runtime_max_impls = runtime_db.size() > 0 
                            ? CUFFTDX_STD::tuple_size<decltype(runtime_db[0].implementations)>::value
                            : 0;
                        return query_constexpr_database<runtime_db.size(), runtime_max_impls>(
                            runtime_db, runtime_size, runtime_type, runtime_direction, runtime_architecture, runtime_code_type, runtime_precision, runtime_ept, runtime_min_ept, static_cast<transposition>(trp_option));
                    }
                    // this function should only be used on the host as it returns a std::vector of implementation_info
                    static auto query_all_entries_runtime(
                        unsigned int            runtime_size,
                        fft_type                runtime_type,
                        fft_direction           runtime_direction,
                        unsigned int            runtime_architecture,
                        precision               runtime_precision,
                        experimental::code_type runtime_code_type,
                        unsigned int            runtime_ept     = 0,
                        unsigned int            runtime_min_ept = 0) {
                        static const auto                runtime_db = get_all_records();
                        std::vector<implementation_info> possible_implementations;
                        // this is the filtered ept value so we don't add the same implementation twice
                        // avoids having multiple transpositions of the same implementation which we don't support
                        std::unordered_set<unsigned int> ept_map;
                        for (const auto& record : runtime_db) {
                            if (record.key.match(runtime_size, runtime_type, runtime_direction,
                                                 runtime_architecture, runtime_precision,
                                                 runtime_code_type)) {
                                for (unsigned int i = 0; i < record.num_implementations; ++i) {
                                    const auto& implementation = record.implementations[i];
                                    // Skip if we've already seen this EPT value
                                    if (ept_map.find(implementation.elements_per_thread) != ept_map.end()) {
                                        continue;
                                    }

                                    // If runtime_ept specified (> 0): must match exactly
                                    // If runtime_ept not specified (== 0): returned ept values must be >= runtime_min_ept
                                    bool ept_matches = (runtime_ept > 0)
                                                           ? (implementation.elements_per_thread == runtime_ept)
                                                           : (implementation.elements_per_thread >= runtime_min_ept);

                                    if (ept_matches) {
                                        possible_implementations.push_back(implementation);
                                        ept_map.insert(implementation.elements_per_thread);
                                    }
                                }
                            }
                        }
                        return possible_implementations;
                    }
                };

            } // namespace constexpr_db
        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_DETAIL_RUNTIME_QUERY_HPP
