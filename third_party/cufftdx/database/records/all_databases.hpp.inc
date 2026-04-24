

#ifndef CUFFTDX_DATABASE_DETAIL_ALL_DATABASES_TEMPLATE_HPP
#define CUFFTDX_DATABASE_DETAIL_ALL_DATABASES_TEMPLATE_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#    include <cuda/std/array>
#    include <cuda/std/tuple>
#    include <cuda/std/utility>
#else
#    include <array>
#    include <utility>
#    include <type_traits>
#    include <tuple>
#endif

namespace cufftdx {
    namespace database {
        namespace detail {
            // Maximum number of implementations per database record
            constexpr unsigned int max_implementations = 14;

            // Helper template to determine if a precision is enabled
            template<typename PrecisionType>
            struct precision_enabled {
                static constexpr bool value = true; // Default: all precisions enabled
            };

            // Specializations for each precision type
            template<>
            struct precision_enabled<half> {
#if !defined(CUFFTDX_DETAIL_MANUAL_IMPL_FILTER) || defined(CUFFTDX_DETAIL_INCLUDE_PRECISION_FP16)
                static constexpr bool value = true;
#else
                static constexpr bool value = false;
#endif
            };

            template<>
            struct precision_enabled<float> {
#if !defined(CUFFTDX_DETAIL_MANUAL_IMPL_FILTER) || defined(CUFFTDX_DETAIL_INCLUDE_PRECISION_FP32)
                static constexpr bool value = true;
#else
                static constexpr bool value = false;
#endif
            };

            template<>
            struct precision_enabled<double> {
#if !defined(CUFFTDX_DETAIL_MANUAL_IMPL_FILTER) || defined(CUFFTDX_DETAIL_INCLUDE_PRECISION_FP64)
                static constexpr bool value = true;
#else
                static constexpr bool value = false;
#endif
            };

            // Main database selector with filtering (uses max_implementations from database_definition.hpp)
            template<typename PrecisionType, unsigned int Architecture, fft_direction Direction>
            struct database_selector {
                static constexpr auto get_database() {
                    if constexpr (precision_enabled<PrecisionType>::value) {
                        return database_function<PrecisionType, Architecture, Direction>::get();
                    } else {
                        return CUFFTDX_STD::array<database_record<max_implementations>, 0> {};
                    }
                }
            };

            // Primary template definition for database_function (provides fallback with error message)
            // Note: Forward declared in database.hpp, specialized in individual database files
            template<typename PrecisionType, unsigned int Architecture, fft_direction Direction>
            struct database_function {
                static constexpr auto get() {
                    static_assert(sizeof(PrecisionType) == 0,
                                  "database_function: No specialization found for this precision/architecture/direction combination. "
                                  "Either the database file is missing or this combination is not supported.");
                    return CUFFTDX_STD::array<database_record<max_implementations>, 0> {};
                }
            };

#if defined CUFFTDX_ENABLE_RUNTIME_DATABASE
            inline constexpr auto database_entries = CUFFTDX_STD::make_tuple(
                database_selector<float, 750, fft_direction::forward>::get_database(),
                database_selector<double, 750, fft_direction::forward>::get_database(),
                database_selector<half, 750, fft_direction::forward>::get_database(),
                database_selector<float, 800, fft_direction::forward>::get_database(),
                database_selector<double, 800, fft_direction::forward>::get_database(),
                database_selector<half, 800, fft_direction::forward>::get_database(),
                database_selector<float, 860, fft_direction::forward>::get_database(),
                database_selector<double, 860, fft_direction::forward>::get_database(),
                database_selector<half, 860, fft_direction::forward>::get_database(),
                database_selector<float, 890, fft_direction::forward>::get_database(),
                database_selector<double, 890, fft_direction::forward>::get_database(),
                database_selector<half, 890, fft_direction::forward>::get_database(),
                database_selector<float, 900, fft_direction::forward>::get_database(),
                database_selector<double, 900, fft_direction::forward>::get_database(),
                database_selector<half, 900, fft_direction::forward>::get_database(),
                database_selector<float, 1000, fft_direction::forward>::get_database(),
                database_selector<double, 1000, fft_direction::forward>::get_database(),
                database_selector<half, 1000, fft_direction::forward>::get_database(),
                database_selector<float, 1200, fft_direction::forward>::get_database(),
                database_selector<double, 1200, fft_direction::forward>::get_database(),
                database_selector<half, 1200, fft_direction::forward>::get_database()
            );
#endif // CUFFTDX_ENABLE_RUNTIME_DATABASE

            // Centralized function to get all databases as a tuple using database_selector
            // This automatically filters out databases that are not defined (return empty arrays)
            constexpr const auto& get_all_databases() {
#if defined CUFFTDX_ENABLE_RUNTIME_DATABASE
                return database_entries;
#else
                return CUFFTDX_STD::make_tuple();
#endif // CUFFTDX_ENABLE_RUNTIME_DATABASE
            }

        } // namespace detail
    } // namespace database
} // namespace cufftdx

#endif // CUFFTDX_DATABASE_DETAIL_ALL_DATABASES_TEMPLATE_HPP