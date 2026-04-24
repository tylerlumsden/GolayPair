// Copyright (c) 2024-2025, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_DETAIL_PROCESSING_FFT_BLOCK_PREPROCESS_HPP
#define CUFFTDX_DETAIL_PROCESSING_FFT_BLOCK_PREPROCESS_HPP

#ifdef CUFFTDX_DETAIL_USE_CUDA_STL
#    include <cuda/std/type_traits>
#else
#    include <type_traits>
#endif

#include <cuda_fp16.h>

#include "cufftdx/detail/processing/fft_preprocess.hpp"

#include "cufftdx/detail/processing/postprocess_fold.hpp"
#include "cufftdx/detail/processing/preprocess_fold.hpp"
#include "cufftdx/detail/utils.hpp"

namespace cufftdx {
    namespace detail {
        // Registers API

        // C2C
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess(ComplexType* /* input */, ComplexType* /* smem */) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::c2c)> {
            // NOP, C2C and C2R with ept == 2 don't require any preprocess
        }

        // assymetric R2C
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess(ComplexType* input, ComplexType* /* smem */) -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::r2c && real_fft_mode_of<FFT>::value != real_mode::folded)> {
            // Same implementation as thread_preprocess
            preprocess<FFT>(input);
        }

        // fold-optimized R2C
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess(ComplexType* input, ComplexType* /* smem */) -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::r2c && real_fft_mode_of<FFT>::value == real_mode::folded)> {
            // NOP, fold-optimized R2C doesn't require any preprocess
        }

        // C2R, EPT == SIZE
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess(ComplexType* input, ComplexType* /* smem */) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::c2r) &&
                                        real_fft_mode_of<FFT>::value == real_mode::normal &&
                                        (FFT::elements_per_thread == size_of<FFT>::value)> {
            // Same implementation as thread_preprocess
            preprocess<FFT>(input);
        }

        // C2R, EPT < SIZE, CT assymetric
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess(ComplexType* input, ComplexType* smem) //
            -> CUFFTDX_STD::enable_if_t<!Bluestein && (type_of<FFT>::value == fft_type::c2r) &&
                                        (FFT::elements_per_thread < size_of<FFT>::value) &&
                                        real_fft_mode_of<FFT>::value != real_mode::folded> {
            using scalar_type                                       = typename ComplexType::value_type;
            [[maybe_unused]] static constexpr auto ept              = FFT::elements_per_thread;
            [[maybe_unused]] static constexpr auto fft_size         = size_of<FFT>::value;
            [[maybe_unused]] static constexpr auto real_lay         = real_fft_layout_of<FFT>::value;
            [[maybe_unused]] static constexpr bool fft_size_is_even = (fft_size % 2) == 0;
            [[maybe_unused]] static constexpr auto stride           = FFT::stride;
            [[maybe_unused]] static constexpr bool middle_row       = !fft_size_is_even || (fft_size_is_even && ept % 2 != 0);
            [[maybe_unused]] static constexpr auto mid_thread_idx   = ((fft_size / 2) % (fft_size / ept));
            [[maybe_unused]] static constexpr auto index_mod        = fft_size_is_even ? 0 : 1; //For getting 0 element or not
            const auto is_thread_active         = FFT::working_group::is_thread_active();

            if constexpr (real_lay == complex_layout::full) {
                // nop, since
                // shared_to_registers
                // loads all data
                // the synchronization happens
                // inside the FFT function
            } else {
                // Move to the part of shared memory for that FFT batch
                ComplexType* smem_fft_batch = smem + (threadIdx.y * (fft_size / 2));
                __syncthreads();
                if (is_thread_active) {

                    for (unsigned int i = 0; i < (ept / 2); i++) {
                        if (!(threadIdx.x == 0 && i == 0 && !fft_size_is_even)) {
                            smem_fft_batch[threadIdx.x + (i * (fft_size / ept))-index_mod] = input[i];
                        }
                    }

                    if constexpr (middle_row)  {
                        constexpr unsigned int i     = ept / 2;
                        unsigned int           index = threadIdx.x + (i * (fft_size / ept))-index_mod;
                        if (index < (fft_size/2)) {
                            smem_fft_batch[index] = input[i];
                        }
                    }
                }
                __syncthreads();

                if (is_thread_active) {
                    const unsigned int reversed_thread_id = (fft_size / ept) - threadIdx.x; //The first element is never copied
                    const unsigned int loop_upper         = ((threadIdx.x == mid_thread_idx) && fft_size_is_even && !middle_row) ? (ept / 2) - 1 : ept / 2;
                    for (unsigned int i = 0; i < ept / 2; i++) {
                        if (i < loop_upper) {
                            input[ept - 1 - i] = smem_fft_batch[reversed_thread_id + (i * (fft_size / ept))-index_mod];
                            // conjugate
                            input[ept - 1 - i].y = -input[ept - 1 - i].y;
                        }
                    }
                    // Middle row is processed apart. Since packed layouts only work with even fft sizes, for them, normally there is no middle row to process
                    // However for even cases in which ept % 2 !=0 there is a middle row to process
                    if constexpr (middle_row)  {
                        constexpr unsigned int i     = ept / 2;
                        unsigned int           index = reversed_thread_id + (i * (fft_size / ept))-index_mod;
                        if (index < (fft_size / 2)) {
                            input[i] = smem_fft_batch[index];
                            // conjugate
                            input[i].y = -input[i].y;
                        }
                    }

                    // Ensure Hermitian symmetry
                    // Thread 0 contains element 0 of the input

                    // Thread (fft_size/2) % number of threads  contains element fft_size/2 of the input
                    // Thread managing the middle element starting with 0.
                    // For powers of 2 this will be also 0
                    if(threadIdx.x == mid_thread_idx) {
                        if constexpr (real_lay == complex_layout::packed) {
                            if constexpr (mid_thread_idx == 0) {
                                // Get element from register 0
                                input[ept / 2].x = input[0].y;
                            } else {
                                // Get element from shared memory
                                input[ept / 2].x = smem_fft_batch[0].y;
                            }
                        }
                    }
                }
            }

            if (is_thread_active) {
                // Ensure Hermitian symmetry
                // For even sizes this will be also 0
                if(threadIdx.x == mid_thread_idx) {
                    if constexpr(fft_size_is_even) {
                        input[ept / 2].y = get_zero<typename ComplexType::value_type>();
                    }
                }
                // Element 0 is always at thread 0
                if(threadIdx.x == 0) {
                    input[0].y       = get_zero<typename ComplexType::value_type>();
                }
            }

        }

        // C2R, EPT < SIZE, CT fold-optimized
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess(ComplexType* input, ComplexType* smem) //
            -> CUFFTDX_STD::enable_if_t<!Bluestein && (type_of<FFT>::value == fft_type::c2r) &&
                                        (FFT::elements_per_thread <= size_of<FFT>::value) &&
                                        real_fft_mode_of<FFT>::value == real_mode::folded> {
            preprocess_fold_c2r<FFT>(input, smem);
        }

        // C2R, EPT < SIZE, Bluestein
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess(ComplexType* input, ComplexType* smem) //
            -> CUFFTDX_STD::enable_if_t<Bluestein && (type_of<FFT>::value == fft_type::c2r) &&
                                        (FFT::elements_per_thread < get_bluestein_size(size_of<FFT>::value))> {
            using scalar_type                                            = typename ComplexType::value_type;
            [[maybe_unused]] static constexpr auto         ept           = FFT::elements_per_thread;
            [[maybe_unused]] static constexpr auto         fft_size      = size_of<FFT>::value;
            [[maybe_unused]] static constexpr auto         fft_blue_size = get_bluestein_size(fft_size);
            [[maybe_unused]] static constexpr unsigned int stride        = fft_blue_size / ept;
            [[maybe_unused]] static constexpr bool is_packed = real_fft_layout_of<FFT>::value == complex_layout::packed;

            // max_meaningful_ept limits number of loops
            [[maybe_unused]] static constexpr unsigned int max_meaningful_ept = (fft_size / 2 + 1 + (stride - 1)) / stride;

            // Move to the part of shared memory for that FFT batch
            [[maybe_unused]] ComplexType* smem_fft_batch = smem + (threadIdx.y * (fft_blue_size / 2));
            const auto is_thread_active = FFT::working_group::is_thread_active();

            if constexpr (real_fft_layout_of<FFT>::value == complex_layout::full) {
                // nop, since
                // shared_to_registers
                // loads all data
                // synchronization happens
                // inside the FFT function
            } else {
                __syncthreads();

                if (is_thread_active) {
                    for (unsigned i = 0; i < max_meaningful_ept /*ept/2*/; i++) {
                        unsigned index = (i * stride) + threadIdx.x;
                        if (index < (fft_size / 2 + !is_packed)) {
                            if (!(threadIdx.x == 0 && i == 0)) {
                                smem_fft_batch[index - 1] = input[i];
                            }
                        }
                    }

                    if constexpr (is_packed) {
                        if (threadIdx.x == 0) {
                            smem_fft_batch[fft_size / 2 - 1].x = input[0].y;
                        }
                    }
                }

                __syncthreads();

                if (is_thread_active) {
                    // max_meaningful_ept_2 limits number of loops
                    static constexpr unsigned int max_meaningful_ept_2 =
                        ept > (2 * max_meaningful_ept) ? ept : (2 * max_meaningful_ept);
                    for (unsigned i = (max_meaningful_ept - 1); i < max_meaningful_ept_2; i++) {
                        unsigned int index = (i * stride) + threadIdx.x;
                        if ((index >= (fft_size / 2 + 1)) && (index < fft_size)) {
                            input[i] = smem_fft_batch[(fft_size - index) - 1];
                            // conjugate
                            input[i].y = -input[i].y;
                        }
                    }
                }
            }

            if (is_thread_active) {
                // Zero out elements required to be 0
                // to ensure hermitian input
                if (threadIdx.x == 0) {
                    input[0].y = get_zero<scalar_type>();
                }

                if ((fft_size % 2 == 0) && threadIdx.x == (fft_size / 2 % stride)) {
                    if constexpr (is_packed) {
                        input[max_meaningful_ept - 1] = smem_fft_batch[fft_size / 2 - 1];
                    }
                    input[max_meaningful_ept - 1].y = get_zero<scalar_type>();
                }
            }
        }

        // Shared memory API

        // C2C
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess_shared_api(ComplexType* /* input */, ComplexType* /* smem */) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::c2c)> {
            // NOP, C2C and C2R with ept == 2 don't require any preprocess
        }

        // non-optimized R2C
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess_shared_api(ComplexType* input, ComplexType* /* smem */) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::r2c) &&
                                        real_fft_mode_of<FFT>::value != real_mode::folded> {
            // Same implementation as thread_preprocess
            preprocess<FFT>(input);
        }

        // fold-optimized R2C
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess_shared_api(ComplexType* input, ComplexType* /* smem */) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::r2c) &&
                                        real_fft_mode_of<FFT>::value == real_mode::folded> {
            // NOP, fold-optimized R2C doesn't require any preprocess
        }

        // C2R, EPT == SIZE
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess_shared_api(ComplexType* input, ComplexType* /* smem */) //
            -> CUFFTDX_STD::enable_if_t<(type_of<FFT>::value == fft_type::c2r) &&
                                        real_fft_mode_of<FFT>::value == real_mode::normal &&
                                        (FFT::elements_per_thread == size_of<FFT>::value)> {
            // Same implementation as thread_preprocess
            preprocess<FFT>(input);
        }

        // C2R, EPT < SIZE, CT assymetric
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess_shared_api(ComplexType* input, ComplexType* smem) //
            -> CUFFTDX_STD::enable_if_t<!Bluestein && (type_of<FFT>::value == fft_type::c2r) &&
                                        (FFT::elements_per_thread < size_of<FFT>::value) &&
                                        real_fft_mode_of<FFT>::value != real_mode::folded> {
            using scalar_type                               = typename ComplexType::value_type;
            [[maybe_unused]] static constexpr auto ept      = FFT::elements_per_thread;
            [[maybe_unused]] static constexpr auto fft_size = size_of<FFT>::value;

            [[maybe_unused]] static constexpr auto real_lay = real_fft_layout_of<FFT>::value;
            [[maybe_unused]] static constexpr bool fft_size_is_even = (fft_size % 2) == 0;
            // Thread managing the middle element starting with 0
            [[maybe_unused]] static constexpr auto mid_thread_idx = ((fft_size / 2) % (fft_size / ept));
            auto is_thread_active = FFT::working_group::is_thread_active();

            if constexpr (real_lay == complex_layout::full) {
                // nop, since
                // shared_to_registers
                // loads all data
            } else {
                if (is_thread_active) {
                    // Move to the part of shared memory for that FFT batch
                    ComplexType* smem_fft_batch = smem + (threadIdx.y * FFT::input_length);
                    for (unsigned int i = ept / 2; i < ept; i++) {
                        if ((real_lay == complex_layout::packed) &&
                            (threadIdx.x == mid_thread_idx) && (i == ept / 2)) {
                            if constexpr (mid_thread_idx == 0) {
                                // Get element from register 0
                                input[ept / 2].x = input[0].y;
                            } else {
                                // Get element from shared memory
                                input[ept / 2].x = smem_fft_batch[0].y;
                            }
                        } else {
                            auto index = threadIdx.x + i * (fft_size / ept);
                            if (index > fft_size / 2) {
                                input[i]   = smem_fft_batch[fft_size - index];
                                input[i].y = -input[i].y;
                            }
                        }
                    }
                }
            }
            if (is_thread_active) {
                // Ensure Hermitian symmetry
                // Thread 0 contains element 0 of the input
                if(threadIdx.x == 0) {
                    input[0].y       = get_zero<typename ComplexType::value_type>();
                }
                // Thread fft_size % number of threads  contains element fft_size/2 of the input
                if constexpr(fft_size_is_even)
                {
                    if(threadIdx.x == mid_thread_idx) {
                        input[ept / 2].y = get_zero<typename ComplexType::value_type>();
                    }
                }
            }

        }

        // C2R, EPT < SIZE, CT fold-optimized
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess_shared_api(ComplexType* input, ComplexType* smem) //
            -> CUFFTDX_STD::enable_if_t<!Bluestein && (type_of<FFT>::value == fft_type::c2r) &&
                                        (FFT::elements_per_thread <= size_of<FFT>::value) &&
                                        real_fft_mode_of<FFT>::value == real_mode::folded> {
            preprocess_fold_c2r<FFT, true>(input, smem);
        }

        // C2R, EPT < SIZE, Bluestein
        template<class FFT, bool Bluestein, class ComplexType>
        inline __device__ auto block_preprocess_shared_api(ComplexType* input, ComplexType* smem) //
            -> CUFFTDX_STD::enable_if_t<Bluestein && (type_of<FFT>::value == fft_type::c2r) &&
                                        (FFT::elements_per_thread < get_bluestein_size(size_of<FFT>::value))> {
            using scalar_type                            = typename ComplexType::value_type;
            static constexpr auto         ept            = FFT::elements_per_thread;
            static constexpr auto         fft_size       = size_of<FFT>::value;
            static constexpr auto         fft_blue_size  = get_bluestein_size(fft_size);
            static constexpr unsigned int stride         = fft_blue_size / ept;

            [[maybe_unused]] ComplexType* smem_fft_batch = smem + (threadIdx.y * FFT::input_length);
            const auto is_thread_active = FFT::working_group::is_thread_active();

            if constexpr (real_fft_layout_of<FFT>::value == complex_layout::full) {
                // nop, since
                // shared_to_registers
                // loads all data
            } else {
                if (is_thread_active) {
                    // Move to the part of shared memory for that FFT batch
                    static constexpr unsigned int first_missing_index = ((fft_size / 2 + 1) + (stride - 1)) / stride;
                    static constexpr unsigned int last_missing_index =
                        ept > (2 * first_missing_index) ? ept : (2 * first_missing_index);
                    for (unsigned i = (first_missing_index - 1); i < last_missing_index; i++) {
                        unsigned int index = (i * stride) + threadIdx.x;
                        if ((index >= (fft_size / 2 + 1)) && (index < fft_size)) {
                            input[i]   = smem_fft_batch[(fft_size - index)];
                            input[i].y = -input[i].y;
                        }
                    }
                }
            }

            if (is_thread_active) {
                // Zero out elements required to be 0
                // to ensure hermitian input
                if (threadIdx.x == 0) {
                    input[0].y = get_zero<typename ComplexType::value_type>();
                }

                if ((fft_size % 2 == 0) && threadIdx.x == (fft_size / 2 % stride)) {
                    if constexpr (real_fft_layout_of<FFT>::value == complex_layout::packed) {
                            input[fft_size / (2 * stride)]   = smem_fft_batch[fft_size / 2 - 1];
                    }
                    input[fft_size / (2 * stride)].y = get_zero<typename ComplexType::value_type>();
                }
            }
        }
    } // namespace detail
} // namespace cufftdx

#endif
