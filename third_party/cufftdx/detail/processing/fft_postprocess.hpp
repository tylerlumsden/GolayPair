// Copyright (c) 2024-2025, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DETAIL_PROCESSING_FFT_POSTPROCESS_HPP
#define CUFFTDX_DETAIL_PROCESSING_FFT_POSTPROCESS_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#else
#    include <type_traits>
#endif

#include <cuda_fp16.h>
#include "cufftdx/detail/utils.hpp"
#include "cufftdx/detail/processing/postprocess_fold.hpp"

namespace cufftdx {
    namespace detail {
        // C2C
        template<class FFT, class ComplexType>
        inline __device__ auto postprocess(ComplexType* input) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::c2c)> {
            // NOP, C2C doesn't require postprocess
        }

        // R2C
        template<class FFT, class ComplexType>
        inline __device__ auto postprocess(ComplexType* input) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::r2c &&
                                         real_fft_mode_of<FFT>::value != real_mode::folded)> {
            // Need to get the middle element of all valid values. For the first thread
            // this is equal to the number of registers, that is storage_size. Normally,
            // this is the same as effective_elements_per_thread
            [[maybe_unused]] static constexpr auto max_elements_per_thread = FFT::storage_size;
            const auto is_thread_active = FFT::working_group::is_thread_active();

            if (is_thread_active) {
                if constexpr (real_fft_layout_of<FFT>::value == complex_layout::full) {
                    // already is in full layout
                } else if constexpr (real_fft_layout_of<FFT>::value == complex_layout::natural) {
                    // implicitly already in natural layout (if the rest is ignored)
                } else if constexpr (real_fft_layout_of<FFT>::value == complex_layout::packed) {
                    // we need to pack real part of element N/2 into imaginary part of element 0
                    if constexpr (size_of<FFT>::value > FFT::elements_per_thread) {
                        if (threadIdx.x == 0) {
                            input[0].y = input[max_elements_per_thread / 2].x;
                        }
                    } else {
                        input[0].y = input[max_elements_per_thread / 2].x;
                    }
                }
            }
        }

        template<class FFT, class ComplexType>
        inline __device__ auto postprocess(ComplexType* input) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::r2c &&
                                         real_fft_mode_of<FFT>::value == real_mode::folded)> {
            postprocess_fold_r2c<FFT>(input, static_cast<ComplexType*>(nullptr));
        }

        // C2R
        template<class FFT, class ComplexType>
        inline __device__ auto postprocess(ComplexType* input) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::c2r &&
                                         real_fft_mode_of<FFT>::value != real_mode::folded)> {
            using scalar_type         = typename ComplexType::value_type;
            // Need to post process all valid elements in thread. For some threads, this is
            // equal to the number of registers, that is storage_size. Normally,
            // this is the same as elements_per_thread
            static constexpr auto max_elements_per_thread = FFT::storage_size;
            // Pack real values
            for (unsigned int i = 1; i < max_elements_per_thread; i++) {
                (reinterpret_cast<scalar_type*>(input))[i] = (reinterpret_cast<scalar_type*>(input))[2 * i];
            }

        }

        // C2R
        template<class FFT, class ComplexType>
        inline __device__ auto postprocess(ComplexType* input) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::c2r &&
                                         real_fft_mode_of<FFT>::value == real_mode::folded)> {
            // NOP
        }
    } // namespace detail
} // namespace cufftdx

#endif
