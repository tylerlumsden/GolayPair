// Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DATABASE_DETAIL_BLOCK_FFT_HPP
#define CUFFTDX_DATABASE_DETAIL_BLOCK_FFT_HPP

#include <cuda_fp16.h>
#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/array>
#else
#    include <array>
#endif

#include "cufftdx/operators/type.hpp"
#include "cufftdx/operators/direction.hpp"
#include "cufftdx/operators/precision.hpp"
#include "cufftdx/operators/experimental/code_type.hpp"
#include "cufftdx/database/detail/type_list.hpp"

namespace cufftdx {
    namespace database {
        namespace detail {
            template<unsigned int Size /* FFT size */,
                     class Precision,
                     fft_type                Type,
                     fft_direction           Direction,
                     unsigned int            Architecture,
                     experimental::code_type CodeType = experimental::code_type::ptx>
            struct block_fft_record {
                static constexpr bool defined = false;
            };

            template<unsigned int            ElementsPerThread /* Number of elements processed per thread */,
                     unsigned int            StoreElementsPerThread,
                     unsigned int            StorageSize, /* Storage size, number of elements in input/output array */
                     unsigned int            ThreadsPerFFT,
                     unsigned int            FFTsPerBlock,
                     unsigned int            SharedMemorySize /* Size of shared mem. required by one FFT */,
                     unsigned int            NumSyncs,
                     unsigned long long      FunctionId,
                     experimental::code_type CodeType>
            struct fft_implementation {
                static constexpr unsigned int            elements_per_thread       = ElementsPerThread;
                static constexpr unsigned int            store_elements_per_thread = StoreElementsPerThread;
                static constexpr unsigned int            storage_size              = StorageSize;
                static constexpr unsigned int            threads_per_fft           = ThreadsPerFFT;
                static constexpr unsigned int            ffts_per_block            = FFTsPerBlock;
                static constexpr unsigned int            shared_memory_size        = SharedMemorySize;
                static constexpr unsigned int            num_syncs                 = NumSyncs;
                static constexpr unsigned long long      function_id               = FunctionId;
                static constexpr experimental::code_type code                      = CodeType;
            };

            template<unsigned int       ElementsPerThread,
                     unsigned int       StoreElementsPerThread,
                     unsigned int       StorageSize,
                     unsigned int       ThreadsPerFFT,
                     unsigned int       FFTsPerBlock,
                     unsigned int       SharedMemorySize,
                     unsigned int       NumSyncs,
                     unsigned long long FunctionId>
            struct block_fft_implementation:
                fft_implementation<ElementsPerThread,
                                   StoreElementsPerThread,
                                   StorageSize,
                                   ThreadsPerFFT,
                                   FFTsPerBlock,
                                   SharedMemorySize,
                                   NumSyncs,
                                   FunctionId,
                                   experimental::code_type::ptx> {
                static constexpr unsigned version = 0; // PTX implementations have version 0
            };

            template<unsigned int       ElementsPerThread,
                     unsigned int       StoreElementsPerThread,
                     unsigned int       StorageSize,
                     unsigned int       ThreadsPerFFT,
                     unsigned int       FFTsPerBlock,
                     unsigned int       SharedMemorySize,
                     unsigned long long FunctionId,
                     unsigned int       Version,
                     unsigned int       NumSyncs = 0>
            struct block_fft_lto_implementation:
                fft_implementation<ElementsPerThread,
                                   StoreElementsPerThread,
                                   StorageSize,
                                   ThreadsPerFFT,
                                   FFTsPerBlock,
                                   SharedMemorySize,
                                   NumSyncs,
                                   FunctionId,
                                   experimental::code_type::ltoir> {
                static constexpr unsigned version = Version;
            };

            // Implementation info structure - contains implementation details as values (not types)
            // This allows us to store implementation data in constexpr arrays for runtime queries
            struct implementation_info {
                unsigned int            elements_per_thread;
                unsigned int            store_elements_per_thread;
                unsigned int            storage_size;
                unsigned int            threads_per_fft;
                unsigned int            ffts_per_block;
                unsigned int            shared_memory_size;
                unsigned int            num_syncs;
                unsigned long long      function_id;
                experimental::code_type code_type;
                unsigned int            version;

                constexpr bool is_valid() const {
                    return elements_per_thread > 0;
                }

                constexpr bool operator==(const implementation_info& other) const {
                    return elements_per_thread == other.elements_per_thread &&
                           store_elements_per_thread == other.store_elements_per_thread &&
                           storage_size == other.storage_size &&
                           threads_per_fft == other.threads_per_fft &&
                           ffts_per_block == other.ffts_per_block &&
                           shared_memory_size == other.shared_memory_size &&
                           num_syncs == other.num_syncs &&
                           function_id == other.function_id &&
                           code_type == other.code_type &&
                           version == other.version;
                }

                constexpr bool operator!=(const implementation_info& other) const {
                    return !(*this == other);
                }

                // Helper to create from existing fft_implementation type
                template<typename FFTImplementation>
                static constexpr implementation_info from_type() {
                    return implementation_info {
                        FFTImplementation::elements_per_thread,
                        FFTImplementation::store_elements_per_thread,
                        FFTImplementation::storage_size,
                        FFTImplementation::threads_per_fft,
                        FFTImplementation::ffts_per_block,
                        FFTImplementation::shared_memory_size,
                        FFTImplementation::num_syncs,
                        FFTImplementation::function_id,
                        FFTImplementation::code,
                        FFTImplementation::version
                    };
                }
            };

            // Helper to convert implementation_info back to the appropriate fft_implementation type
            // This is the inverse of implementation_info::from_type
            // Returns block_fft_lto_implementation for LTOIR (includes version),
            // or block_fft_implementation for PTX
            template<const implementation_info& Data>
            using implementation_info_as_type = CUFFTDX_STD::conditional_t<
                Data.code_type == experimental::code_type::ltoir,
                block_fft_lto_implementation<
                    Data.elements_per_thread,
                    Data.store_elements_per_thread,
                    Data.storage_size,
                    Data.threads_per_fft,
                    Data.ffts_per_block,
                    Data.shared_memory_size,
                    Data.function_id,
                    Data.version,
                    Data.num_syncs>,
                block_fft_implementation<
                    Data.elements_per_thread,
                    Data.store_elements_per_thread,
                    Data.storage_size,
                    Data.threads_per_fft,
                    Data.ffts_per_block,
                    Data.shared_memory_size,
                    Data.num_syncs,
                    Data.function_id>>;

            // Database key structure - uniquely identifies a database query
            struct database_key {
                unsigned int            size;
                precision               precision_type;
                fft_type                type;
                fft_direction           direction;
                unsigned int            architecture;
                experimental::code_type code_type;

                constexpr bool operator==(const database_key& other) const {
                    return size == other.size &&
                           precision_type == other.precision_type &&
                           type == other.type &&
                           direction == other.direction &&
                           architecture == other.architecture &&
                           code_type == other.code_type;
                }

                constexpr bool match(unsigned int            size_param,
                                    fft_type                type_param,
                                    fft_direction           direction_param,
                                    unsigned int            architecture_param,
                                    precision               precision_type_param,
                                    experimental::code_type code_type_param) const {
                    return size == size_param && type == type_param &&
                           direction == direction_param && architecture == architecture_param &&
                           precision_type == precision_type_param && code_type == code_type_param;
                }
            };


            // Database record - contains key and array of implementations
            template<unsigned int MaxImplementations>
            struct database_record {
                database_key                                                key;
                CUFFTDX_STD::array<implementation_info, MaxImplementations> implementations;
                unsigned int                                                num_implementations;

                constexpr database_record():
                    key {}, implementations {}, num_implementations(0) {}

                constexpr database_record(const database_key&                                                k,
                                          const CUFFTDX_STD::array<implementation_info, MaxImplementations>& impls,
                                          unsigned int                                                       count):
                    key(k), implementations(impls), num_implementations(count) {}
            };

            // Helper to convert template-based implementation to constexpr info
            // This reuses the existing fft_implementation structure
            template<typename Implementation>
            constexpr implementation_info make_implementation_info() {
                return implementation_info::from_type<Implementation>();
            }

            // Helper to extract implementations from type_list
            template<typename TypeList>
            struct extract_implementations;

            template<typename... Types>
            struct extract_implementations<type_list<Types...>> {
                static constexpr unsigned int count = sizeof...(Types);
                template<unsigned int MaxImpls>
                static constexpr CUFFTDX_STD::array<implementation_info, MaxImpls> get() {
                    return get_impl<MaxImpls>(CUFFTDX_STD::index_sequence_for<Types...>{});
                }

            private:
                template<unsigned int MaxImpls, CUFFTDX_STD::size_t... Indices>
                static constexpr CUFFTDX_STD::array<implementation_info, MaxImpls> get_impl(
                    CUFFTDX_STD::index_sequence<Indices...>) {
                    CUFFTDX_STD::array<implementation_info, MaxImpls> result {};
                    ((result[Indices] = make_implementation_info<Types>()), ...);
                    return result;
                }
            };


            // Helper to create database record from block_fft_record
            // If MaxImpls is 0, automatically deduce the exact size from the record type
            template<unsigned int Size,
                     typename PrecisionType,
                     fft_type                Type,
                     fft_direction           Direction,
                     unsigned int            Architecture,
                     experimental::code_type CodeType,
                     unsigned int            MaxImpls>
            constexpr auto make_database_record() {
                using record_type = block_fft_record<Size, PrecisionType, Type, Direction, Architecture, CodeType>;

                if constexpr (record_type::defined) {
                    using extractor = extract_implementations<typename record_type::blobs>;

                    // Auto-deduce the actual implementation count when MaxImpls is 0
                    constexpr size_t actual_max_impls = (MaxImpls == 0) ? extractor::count : MaxImpls;

                    // Convert PrecisionType to precision enum
                    constexpr precision prec = cufftdx::detail::map_precision<PrecisionType>();

                    database_key key {
                        Size,
                        prec,
                        Type,
                        Direction,
                        Architecture,
                        CodeType};

                    auto implementations = extractor::template get<actual_max_impls>();

                    return database_record<actual_max_impls> {key, implementations, extractor::count};
                } else {
                    return database_record<MaxImpls> {};
                }
            }

            // Compile-time specific database record accessor - creates single-record array directly from block_fft_record
            // This avoids instantiating the full database_selector for compile-time usage
            // If MaxImpls is 0, automatically deduce the exact size from the record type
            template<unsigned int Size,
                     typename PrecisionType,
                     fft_type                Type,
                     fft_direction           Direction,
                     unsigned int            Architecture,
                     experimental::code_type CodeType,
                     unsigned int            MaxImpls>
            constexpr auto make_single_record_database() {
                using record_type = block_fft_record<Size, PrecisionType, Type, Direction, Architecture, CodeType>;

                if constexpr (record_type::defined) {
                    using extractor = extract_implementations<typename record_type::blobs>;

                    // Auto-deduce the actual implementation count when MaxImpls is 0
                    constexpr size_t actual_max_impls = (MaxImpls == 0) ? extractor::count : MaxImpls;

                    // Create a single-record database array
                    auto single_record = make_database_record<Size, PrecisionType, Type, Direction, Architecture, CodeType, actual_max_impls>();
                    CUFFTDX_STD::array<database_record<actual_max_impls>, 1> database {};
                    database[0] = single_record;
                    return database;
                } else {
                    // Return empty database if record is not defined
                    return CUFFTDX_STD::array<database_record<MaxImpls>, 0> {};
                }
            }
        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_DETAIL_BLOCK_FFT_HPP
