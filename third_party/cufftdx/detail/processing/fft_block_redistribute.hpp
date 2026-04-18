// Copyright (c) 2025, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DETAIL_PROCESSING_FFT_BLOCK_REDISTRIBUTE_HPP
#define CUFFTDX_DETAIL_PROCESSING_FFT_BLOCK_REDISTRIBUTE_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#else
#    include <type_traits>
#endif

#include <cuda_fp16.h>
#include "cufftdx/detail/utils.hpp"


namespace cufftdx {
    namespace detail {

        // Redistribution type enum (now used as a template parameter)
        enum class redistribution_type {
            shared_only, // Only perform redistribution into shared memory
            full        // Perform full redistribution (shared memory + back to registers)
        };
        // Use for registers API

        /* Struct used to move data from_ept registers into ept registers using shared memory */
        template<class FFT, unsigned from_ept>
        struct redistribution {
            static constexpr auto size = size_of<FFT>::value;
            static constexpr auto output_size = FFT::output_length;
            static constexpr unsigned int dfts_per_thread = (FFT::elements_per_thread + from_ept - 1) / from_ept;//= ceil(ndft / threads_per_fft) = ceil( (nx / from_ept) / (nx / ept))
            static constexpr auto t_stride = (size / from_ept); // Stride between elements inside original registers

            template <bool redistribute, class T>
            static __forceinline__ __device__ auto redistribute_to_shared(T* thread_data, T* smem) ->
                typename CUFFTDX_STD::enable_if_t< redistribute && (FFT::elements_per_thread % from_ept != 0)> {
                const auto is_thread_active = FFT::working_group::is_thread_active();
                const unsigned int batch_offset = threadIdx.y * size;
                unsigned int       index        = threadIdx.x;


                __syncthreads();
                if (is_thread_active) {
                    // Reorganize data in shared memory
                    for (unsigned int k = 0; k < dfts_per_thread; k++) {
                        index = threadIdx.x + (FFT::stride * k);
                        if (index < t_stride) {
                            #pragma unroll
                            for (unsigned int i = 0; i < from_ept; i++) {
                                smem[batch_offset + index] = thread_data[i * dfts_per_thread + k];
                                index += t_stride;
                            }
                        }
                    }
                }
            }

            //EPT % from_ept ==0
            template <bool redistribute, class T>
            static __forceinline__ __device__ auto redistribute_to_shared(T* thread_data, T* smem) ->
                typename CUFFTDX_STD::enable_if_t< !redistribute || (FFT::elements_per_thread % from_ept == 0)> {
                const auto is_thread_active = FFT::working_group::is_thread_active();
                const unsigned int batch_offset = threadIdx.y * output_size;
                unsigned int       index        = threadIdx.x;

                __syncthreads();
                if (is_thread_active) {
                    for (unsigned int i = 0; i < FFT::output_ept; i++) {
                        if (index < output_size) {
                            smem[batch_offset + index] = thread_data[i];
                        }
                        index += FFT::stride;
                    }
                }
            }


            template <class T>
            static __forceinline__ __device__ void redistribute_from_shared(T* thread_data, T* smem) {
                const auto is_thread_active = FFT::working_group::is_thread_active();
                const unsigned int batch_offset = threadIdx.y * output_size;
                unsigned int       index        = threadIdx.x;

                __syncthreads();
                if (is_thread_active) {
                    // Return the data back to registers in natural order
                    #pragma unroll
                    for (unsigned i = 0; i < FFT::output_ept; i++) {
                        if (index < size) {
                            thread_data[i] = smem[batch_offset + index];
                        }
                        index += FFT::stride;
                    }
                }
            }

            // Public function: Perform full redistribution, always redistribute
            template <class T>
            static __forceinline__ __device__ void full_redistribution(T* thread_data, T* smem) {
                redistribute_to_shared<true>(thread_data, smem);
                redistribute_from_shared(thread_data, smem);
            }
        };


        template<class FFT, unsigned from_ept, bool redistribute, redistribution_type Type, class T>
        __device__ inline void block_redistribute(T* thread_data, T* smem) {
            using output_t = typename FFT::output_type;
            if constexpr (Type == redistribution_type::shared_only) {
                // Perform shared memory redistribution only
                redistribution<FFT, from_ept>::redistribute_to_shared<redistribute>(reinterpret_cast<output_t*>(thread_data), reinterpret_cast<output_t*>(smem));
            } else if constexpr (Type == redistribution_type::full && redistribute) {
                // Perform full redistribution: shared memory + back to registers
                redistribution<FFT, from_ept>::full_redistribution(reinterpret_cast<output_t*>(thread_data), reinterpret_cast<output_t*>(smem));
            }
        }



    } // namespace detail
} // namespace cufftdx

#endif
