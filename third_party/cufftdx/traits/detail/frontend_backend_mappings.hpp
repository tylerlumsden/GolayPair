// Copyright (c) 2025, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_TRAITS_DETAIL_FRONTEND_BACKEND_MAPPINGS_HPP
#define CUFFTDX_TRAITS_DETAIL_FRONTEND_BACKEND_MAPPINGS_HPP

#include <vector_types.h>
#include "cufftdx/detail/config.hpp"
#include "cufftdx/operators.hpp"

namespace cufftdx {
    namespace detail {
        enum class algorithm
        {
            ct,
            bluestein,
        };

        enum class execution_type
        {
            thread,
            block
        };

        struct frontend_impl_traits {
            unsigned int elements_per_thread;
            unsigned int ffts_per_block;
            unsigned int suggested_elements_per_thread;
            unsigned int suggested_ffts_per_block;
            unsigned int block_dim_x;
            unsigned int block_dim_y;
            unsigned int block_dim_z;
            unsigned int shared_memory_size;
            unsigned int storage_size;
            unsigned int stride;
            unsigned int input_elements_per_thread;
            unsigned int output_elements_per_thread;
            unsigned int suggested_block_dim_x;
            unsigned int suggested_block_dim_y;
            unsigned int suggested_block_dim_z;

            constexpr frontend_impl_traits(unsigned int elements_per_thread,
                                           unsigned int ffts_per_block,
                                           unsigned int suggested_elements_per_thread,
                                           unsigned int suggested_ffts_per_block,
                                           unsigned int block_dim_x,
                                           unsigned int block_dim_y,
                                           unsigned int block_dim_z,
                                           unsigned int shared_memory_size,
                                           unsigned int storage_size,
                                           unsigned int stride,
                                           unsigned int input_elements_per_thread,
                                           unsigned int output_elements_per_thread,
                                           unsigned int suggested_block_dim_x,
                                           unsigned int suggested_block_dim_y,
                                           unsigned int suggested_block_dim_z):
                elements_per_thread(elements_per_thread),
                ffts_per_block(ffts_per_block),
                suggested_elements_per_thread(suggested_elements_per_thread),
                suggested_ffts_per_block(suggested_ffts_per_block),
                block_dim_x(block_dim_x),
                block_dim_y(block_dim_y),
                block_dim_z(block_dim_z),
                shared_memory_size(shared_memory_size),
                storage_size(storage_size),
                stride(stride),
                input_elements_per_thread(input_elements_per_thread),
                output_elements_per_thread(output_elements_per_thread),
                suggested_block_dim_x(suggested_block_dim_x),
                suggested_block_dim_y(suggested_block_dim_y),
                suggested_block_dim_z(suggested_block_dim_z) {}
        };

        struct backend_impl_traits {
            unsigned int  size;
            fft_type      type;
            fft_direction direction;
            unsigned int  sm;
            unsigned int  elements_per_thread;
            unsigned int  min_elements_per_thread;

            constexpr backend_impl_traits(unsigned int  size,
                                          fft_type      type,
                                          fft_direction direction,
                                          unsigned int  sm,
                                          unsigned int  elements_per_thread,
                                          unsigned int  min_elements_per_thread):
                size(size),
                type(type),
                direction(direction),
                sm(sm),
                elements_per_thread(elements_per_thread),
                min_elements_per_thread(min_elements_per_thread) {}
        };

        __CUFFTDX_HOST_DEVICE_FORCEINLINE__
        constexpr unsigned int get_bluestein_size(const unsigned int fft_size) {
            if (fft_size <= 16) {
                return 32;
            } else if (fft_size <= 32) {
                return 64;
            } else if (fft_size <= 64) {
                return 128;
            } else if (fft_size <= 128) {
                return 256;
            } else if (fft_size <= 256) {
                return 512;
            } else if (fft_size <= 512) {
                return 1024;
            } else if (fft_size <= 1024) {
                return 2048;
            } else if (fft_size <= 2048) {
                return 4096;
            } else if (fft_size <= 4096) {
                return 8192;
            } else if (fft_size <= 8192) {
                return 16384;
            } else if (fft_size <= 16384) {
                return 32768;
            } else if (fft_size <= 32768) {
                return 65536;
            } else if (fft_size == 65536) {
                return 65536;
            }
            return 0;
        }

        // This is necessary since when performing R2C or C2R FFT, the actual C2C implementation FFT happening inside
        // can be of a different size than the real FFT. To verify existence in database we need to be able to check
        // the effective execution size
        constexpr unsigned int get_fft_execution_size(real_mode mode, unsigned int size) {
            const bool is_folded = mode == real_mode::folded;
            return is_folded ? size / 2 : size;
        }

        constexpr unsigned int get_storage_size(complex_layout layout, real_mode mode, unsigned int storage_size) {
            bool is_folded = (mode == real_mode::folded);
            if (is_folded) {
                if (layout == complex_layout::natural) {
                    return storage_size + 1;
                } else if (layout == complex_layout::packed) {
                    return storage_size;
                } else if (layout == complex_layout::full) {
                    return 2 * storage_size;
                }
            } else {
                return storage_size;
            }
            return 0;
        }

        __CUFFTDX_HOST_DEVICE_FORCEINLINE__
        constexpr unsigned int divide_based_on_layout(complex_layout this_fft_complex_layout, unsigned int value) {
            switch (this_fft_complex_layout) {
                case complex_layout::natural: return value / 2 + 1;
                case complex_layout::packed: return value / 2;
                case complex_layout::full: return value;
            }
            return value;
        }

        constexpr fft_type flip_fft_type(fft_type this_fft_type) {
            switch (this_fft_type) {
                case fft_type::c2r: return fft_type::r2c;
                case fft_type::r2c: return fft_type::c2r;
                case fft_type::c2c: return fft_type::c2c;
            }
            return fft_type::c2c;
        }

        constexpr unsigned int get_input_ept(fft_type this_fft_type, complex_layout this_fft_complex_layout, unsigned int ept, unsigned int effective_ept) {
            switch (this_fft_type) {
                case fft_type::c2r:
                    // For non divisible epts need to get one row more even with packed
                    return (this_fft_complex_layout == complex_layout::packed) ?
                        divide_based_on_layout(this_fft_complex_layout, ept) + (ept % 2) :
                        divide_based_on_layout(this_fft_complex_layout, ept);
                case fft_type::r2c:
                case fft_type::c2c:
                    return effective_ept;
            }
            return 0;
        }

        constexpr unsigned int get_output_ept(fft_type this_fft_type, complex_layout this_fft_complex_layout, unsigned int ept, unsigned int effective_ept) {
            return get_input_ept(flip_fft_type(this_fft_type), this_fft_complex_layout, ept, effective_ept);
        }

        // See make_complex_type.hpp.
        constexpr auto get_complex_type(precision precision) {
            switch (precision) {
                case precision::f16: return value_type::c_16f2;
                case precision::f32: return value_type::c_32f;
                case precision::f64: return value_type::c_64f;
            }
            return value_type::c_32f;
        }

        constexpr auto get_real_type(precision precision) {
            switch (precision) {
                case precision::f16: return value_type::r_16f2;
                case precision::f32: return value_type::r_32f;
                case precision::f64: return value_type::r_64f;
            }
            return value_type::r_32f;
        }

        constexpr bool is_input_real(fft_type this_fft_type, real_mode real_mode) {
            return (real_mode != real_mode::folded && this_fft_type == fft_type::r2c);
        }

        constexpr bool is_output_real(fft_type this_fft_type, real_mode real_mode) {
            return is_input_real(flip_fft_type(this_fft_type), real_mode);
        }

        constexpr auto get_value_type(precision precision) {
            return get_complex_type(precision);
        }

        constexpr auto get_input_type(fft_type this_fft_type, real_mode real_mode, precision precision) {
            return is_input_real(this_fft_type, real_mode) ? get_real_type(precision) : get_complex_type(precision);
        }

        constexpr auto get_output_type(fft_type this_fft_type, real_mode real_mode, precision precision) {
            return is_output_real(this_fft_type, real_mode) ? get_real_type(precision) : get_complex_type(precision);
        }

        constexpr unsigned int get_input_length(fft_type this_fft_type, complex_layout this_fft_complex_layout, real_mode real_mode, unsigned int size) {
            const auto complex_len = divide_based_on_layout(this_fft_complex_layout, size);
            return this_fft_type == fft_type::c2r ? complex_len : get_fft_execution_size(real_mode, size);
        }

        constexpr unsigned int get_output_length(fft_type this_fft_type, complex_layout this_fft_complex_layout, real_mode real_mode, unsigned int size) {
            return get_input_length(flip_fft_type(this_fft_type), this_fft_complex_layout, real_mode, size);
        }

        constexpr unsigned int get_implicit_type_batching(precision precision) {
            return (precision == precision::f16) ? 2 : 1;
        }

        constexpr backend_impl_traits
        frontend_to_backend(const algorithm               algorithm,
                            const execution_type          execution,
                            unsigned int            size,
                            const fft_type                type,
                            const fft_direction           direction,
                            const unsigned int            sm,
                            const real_mode               real_mode,
                            const unsigned int            elements_per_thread,
                            const unsigned int            block_dim_x,
                            const experimental::code_type code) {

            const bool is_folded = (real_mode == real_mode::folded);
            const bool is_blue   = (algorithm == algorithm::bluestein);

            // Size, Elements per thread
            const unsigned int blue_size                     = get_bluestein_size(size);
            const unsigned int effective_size                = get_fft_execution_size(real_mode, is_blue ? blue_size : size);
            const unsigned int effective_elements_per_thread = (execution == execution_type::thread) ? effective_size : (is_folded ? elements_per_thread / 2 : elements_per_thread);

            const unsigned int effective_min_elements_per_thread = (execution == execution_type::thread) ? effective_size : (block_dim_x == 0 ? 0 : (effective_size + block_dim_x - 1) / block_dim_x);
            // SM
            unsigned int effective_sm = (execution == execution_type::thread ? 900 : sm);
            // Forward SMs (PTX only)
            if (code == experimental::code_type::ptx) {
                switch (effective_sm) {
                    case 870:
                        effective_sm = 800;
                        break;
                    case 1030:
                    case 1100:
                        effective_sm = 1000;
                        break;
                    case 1210:
                        effective_sm = 1200;
                        break;
                    default: break;
                }
            }

            // Direction
            const fft_direction blue_direction      = fft_direction::forward;
            fft_direction effective_direction = is_blue ? blue_direction : direction;
            // Forward inverse records to forward records (PTX only)
            if (code == experimental::code_type::ptx) {
                effective_direction = fft_direction::forward;
            }

            // Type
            const fft_type blue_type      = fft_type::c2c;
            fft_type effective_type = is_folded ? fft_type::c2c : (is_blue ? blue_type : type);
            // Forward R2C / C2R records to C2C records (PTX only)
            if (code == experimental::code_type::ptx) {
                if (effective_type == fft_type::r2c) {
                    effective_type = fft_type::c2c;
                }
                if (effective_type == fft_type::c2r) {
                    effective_type = fft_type::c2c;
                }
            }

            return backend_impl_traits(effective_size,
                                       effective_type,
                                       effective_direction,
                                       effective_sm,
                                       effective_elements_per_thread,
                                       effective_min_elements_per_thread);
        }

        constexpr frontend_impl_traits
        backend_to_frontend(const execution_type execution,
                            const bool           has_ept,
                            const fft_type       fe_type,
                            const complex_layout fe_complex_layout,
                            const real_mode      fe_real_mode,
                            const precision      fe_precision,
                            const unsigned int   fe_ffts_per_block,
                            const unsigned int   be_size,
                            const unsigned int   selected_elements_per_thread,
                            const unsigned int   selected_ffts_per_block,
                            const unsigned int   selected_shared_mem_per_fft,
                            const unsigned int   selected_storage_size,
                            const unsigned int   optimal_elements_per_thread,
                            const unsigned int   optimal_ffts_per_block,
                            const bool           has_block_dim,
                            const unsigned int   block_dim_x,
                            const unsigned int   block_dim_y,
                            const unsigned int   block_dim_z) {

            bool is_folded = (fe_real_mode == real_mode::folded);

            // Elements per thread
            const unsigned int fe_selected_ept  = is_folded ? 2 * selected_elements_per_thread : selected_elements_per_thread;
            const unsigned int fe_suggested_ept = is_folded ? 2 * optimal_elements_per_thread : optimal_elements_per_thread;

            // Storage size
            const unsigned int fe_storage_size = get_storage_size(fe_complex_layout, fe_real_mode, selected_storage_size);

            // FFTs per block
            const unsigned int implicit_type_batching      = get_implicit_type_batching(fe_precision);
            const unsigned int default_ffts_per_block      = implicit_type_batching;
            const unsigned int computed_fe_ffts_per_block                        = (fe_ffts_per_block == 0) ? (has_block_dim ? block_dim_y * implicit_type_batching : default_ffts_per_block) : fe_ffts_per_block;
            const bool computed_has_ept = has_ept || has_block_dim; // In both cases we have defined an EPT

            const unsigned int fe_suggested_ffts_per_block = has_block_dim ?
                ((selected_ffts_per_block < block_dim_y * implicit_type_batching) ? selected_ffts_per_block : block_dim_y * implicit_type_batching) :
                (computed_has_ept ? selected_ffts_per_block : optimal_ffts_per_block);

            // Default block dimension (X = SIZE/EPT, Y = FFTs Per Block, Z = 1)
            const unsigned int fe_block_dim_x = has_block_dim ? block_dim_x : be_size / selected_elements_per_thread;
            const unsigned int fe_block_dim_y = has_block_dim ? block_dim_y : computed_fe_ffts_per_block / implicit_type_batching;
            const unsigned int fe_block_dim_z = has_block_dim ? block_dim_z : 1;

            // Shared memory size
            const unsigned int fe_shared_memory_size = selected_shared_mem_per_fft * computed_fe_ffts_per_block;

            // Stride
            const unsigned int fe_stride = be_size / selected_elements_per_thread;

            // Input / Output EPT
            const unsigned int fe_input_ept  = get_input_ept(fe_type, fe_complex_layout, fe_selected_ept, selected_elements_per_thread);
            const unsigned int fe_output_ept = get_output_ept(fe_type, fe_complex_layout, fe_selected_ept, selected_elements_per_thread);


            // Suggested block dim
            const unsigned int fe_suggested_block_dim_x = fe_stride;
            const unsigned int fe_suggested_block_dim_y = computed_fe_ffts_per_block / implicit_type_batching;
            const unsigned int fe_suggested_block_dim_z = 1;

            return frontend_impl_traits(fe_selected_ept,
                                        (execution == execution_type::thread) ? 0 : computed_fe_ffts_per_block,
                                        fe_suggested_ept,
                                        (execution == execution_type::thread) ? 0 : fe_suggested_ffts_per_block,
                                        (execution == execution_type::thread) ? 0 : fe_block_dim_x,
                                        (execution == execution_type::thread) ? 0 : fe_block_dim_y,
                                        (execution == execution_type::thread) ? 0 : fe_block_dim_z,
                                        fe_shared_memory_size,
                                        fe_storage_size,
                                        fe_stride,
                                        fe_input_ept,
                                        fe_output_ept,
                                        (execution == execution_type::thread) ? 0 : fe_suggested_block_dim_x,
                                        (execution == execution_type::thread) ? 0 : fe_suggested_block_dim_y,
                                        (execution == execution_type::thread) ? 0 : fe_suggested_block_dim_z);
        }
    } // namespace detail
} // namespace cufftdx

#endif // CUFFTDX_TRAITS_DETAIL_FRONTEND_BACKEND_MAPPINGS_HPP
