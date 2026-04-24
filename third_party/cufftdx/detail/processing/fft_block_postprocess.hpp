// Copyright (c) 2024-2025, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DETAIL_PROCESSING_FFT_BLOCK_POSTPROCESS_HPP
#define CUFFTDX_DETAIL_PROCESSING_FFT_BLOCK_POSTPROCESS_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#else
#    include <type_traits>
#endif

#include <cuda_fp16.h>

#include "cufftdx/detail/processing/fft_postprocess.hpp"

#include "cufftdx/detail/processing/postprocess_fold.hpp"
#include "cufftdx/detail/processing/preprocess_fold.hpp"

namespace cufftdx {
    namespace detail {

        // R2C for Bluestein packed
        template<class FFT, class ComplexType>
        inline __device__ auto postprocess_bluestein_r2c_packed(ComplexType* input, ComplexType* smem)
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::r2c)> {

            static constexpr auto ept = FFT::elements_per_thread;
            const auto is_thread_active = FFT::working_group::is_thread_active();



            if constexpr (size_of<FFT>::value > ept) {
                ComplexType* smem_fft_batch = smem + threadIdx.y;
                __syncthreads();

                if (is_thread_active && ((size_of<FFT>::value / 2) % FFT::stride) == threadIdx.x) {
                    smem_fft_batch[0].x = input[((size_of<FFT>::value / 2) - threadIdx.x) / FFT::stride].x;
                }


                __syncthreads();

                if (is_thread_active && threadIdx.x == 0) {
                    input[0].y = smem_fft_batch[0].x;
                }
            } else {
                if (is_thread_active) {
                    input[0].y = input[ept / 2].x;
                }
            }
        }

        // Block R2C
        template<class FFT, unsigned store_ept, class ComplexType>
        inline __device__ auto postprocess_r2c_packed(ComplexType* input, ComplexType* smem) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::r2c &&
                                         real_fft_mode_of<FFT>::value != real_mode::folded &&
                                         real_fft_layout_of<FFT>::value == complex_layout::packed)> {
            // Need to get the middle element of all valid values. For the first thread
            // this is equal to the number of registers, that is storage_size. Normally,
            // this is the same as effective_elements_per_thread
            [[maybe_unused]] static constexpr auto max_elements_per_thread = FFT::storage_size;
            [[maybe_unused]] static constexpr auto size = size_of<FFT>::value;
            [[maybe_unused]] static constexpr auto thread_mid_idx = ((size/2) % (size/store_ept))% FFT::stride;
            [[maybe_unused]] static constexpr auto register_size = (((size/store_ept)+ FFT::stride-1)/FFT::stride);
            // Compute the mid position inside the registers
            [[maybe_unused]] static constexpr auto element_mid_idx = (((store_ept/2)*register_size) + ((((size/2) % (size/store_ept))) / FFT::stride));
            const auto is_thread_active = FFT::working_group::is_thread_active();

            if (thread_mid_idx != 0) {
                __syncthreads();
                if (is_thread_active && threadIdx.x == thread_mid_idx) {
                    //Save middle element for each batch
                    smem[threadIdx.y] = input[element_mid_idx];
                }
                __syncthreads();
                if (is_thread_active && threadIdx.x == 0) {
                    input[0].y = smem[threadIdx.y].x;
                }
            } else {
                postprocess<FFT>(input);
            }


        }

        // All non-optimized
        template<class FFT, bool Bluestein, unsigned store_ept, class ComplexType>
        inline __device__ auto block_postprocess(ComplexType* input, ComplexType* smem) -> CUFFTDX_STD::enable_if_t<real_fft_mode_of<FFT>::value != real_mode::folded || Bluestein> {
            [[maybe_unused]] static constexpr auto size = size_of<FFT>::value;

            // Same implementation as thread_postprocess
            if constexpr (Bluestein &&
                          real_fft_layout_of<FFT>::value == complex_layout::packed &&
                          type_of<FFT>::value == fft_type::r2c) {
                postprocess_bluestein_r2c_packed<FFT>(input, smem);
            } else if constexpr ( real_fft_layout_of<FFT>::value == complex_layout::packed &&
                type_of<FFT>::value == fft_type::r2c) {
                postprocess_r2c_packed<FFT, store_ept>(input, smem);
            } else {
                postprocess<FFT>(input);
            }
        }


        // fold-optimized R2C
        template<class FFT, bool Bluestein, unsigned store_ept, class ComplexType>
        inline __device__ auto block_postprocess(ComplexType* input, ComplexType* smem) -> CUFFTDX_STD::enable_if_t<!Bluestein && real_fft_mode_of<FFT>::value == real_mode::folded &&
                                                                                                                    (type_of<FFT>::value == fft_type::r2c)> {
            postprocess_fold_r2c<FFT>(input, smem);
        }

        // fold-optimized C2R
        template<class FFT, bool Bluestein, unsigned store_ept, class ComplexType>
        inline __device__ auto block_postprocess(ComplexType* input, ComplexType* /* smem */) -> CUFFTDX_STD::enable_if_t<!Bluestein && real_fft_mode_of<FFT>::value == real_mode::folded &&
                                                                                                                          (type_of<FFT>::value == fft_type::c2r)> {
            // NOP, fold-optimized C2R doesn't require any postprocess
        }
    } // namespace detail
} // namespace cufftdx

#endif
