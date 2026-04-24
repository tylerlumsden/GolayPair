// Copyright (c) 2025, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_TRAITS_DETAIL_WORKING_GROUP_HPP
#define CUFFTDX_TRAITS_DETAIL_WORKING_GROUP_HPP

#include "cufftdx/traits/detail/description_traits.hpp"

namespace cufftdx {
    namespace detail {
        template<unsigned int Stride, unsigned int FftsPerBlock>
        struct working_group_impl {
            static constexpr unsigned int stride = Stride;
            static constexpr unsigned int ffts_per_block = FftsPerBlock;

            __device__ __host__ static constexpr dim3 block_dim() noexcept {
                return dim3(stride, ffts_per_block, 1);
            }

            __device__ static inline bool is_thread_active() noexcept {
                return threadIdx.x < stride &&
                       threadIdx.y < ffts_per_block &&
                       threadIdx.z < 1;
            }


        };

        // Primary template - block execution (IsThreadExecution = false)
        template<class FFTType, bool IsDynamicBatching, bool IsThreadExecution>
        struct working_group_helper {
        private:
            // Helper to detect single-threaded execution at method level
            __device__ __host__ static constexpr bool does_it_need_predication() {
                constexpr auto s = FFTType::stride;
                constexpr auto fpb = FFTType::ffts_per_block / FFTType::implicit_type_batching;
                constexpr auto bd = FFTType::block_dim;
                //If dynamic batching is enabled, bigger y dimension is not considered as predication
                return  (bd.x > s || (bd.y > fpb && !IsDynamicBatching) || bd.z > 1);
            }

        public:
            // constexpr only when single-threaded, otherwise regular function
            template<bool DoesItNeedPredication = does_it_need_predication()>
            __device__ static constexpr inline typename CUFFTDX_STD::enable_if_t<!DoesItNeedPredication, bool>
            is_thread_active() noexcept {
                return true; // constexpr path for non predicated execution
            }

            template<bool DoesItNeedPredication = does_it_need_predication()>
            __device__ static inline typename CUFFTDX_STD::enable_if_t<DoesItNeedPredication, bool>
            is_thread_active() noexcept {
                // Block execution logic - not constexpr due to threadIdx
                constexpr auto s = FFTType::stride;
                constexpr auto fpb = FFTType::ffts_per_block / FFTType::implicit_type_batching;
                using impl = working_group_impl<s, fpb>;
                return impl::is_thread_active();
            }

            __device__ __host__ static constexpr inline dim3 block_dim() noexcept {
                constexpr auto s = FFTType::stride;
                constexpr auto fpb = FFTType::ffts_per_block / FFTType::implicit_type_batching;
                using impl = working_group_impl<s, fpb>;
                return impl::block_dim();
            }



            __device__ __host__ static constexpr inline bool is_predicated() noexcept {
                return does_it_need_predication();
            }

        };

        // Specialization for thread execution (IsThreadExecution = true)
        // Same interface, but with constexpr methods where possible
        template<class FFTType>
        struct working_group_helper<FFTType, false,true> {
            __device__ __host__ static constexpr inline bool is_thread_active() noexcept {
                return true; // Thread execution always valid
            }

            __device__ __host__ static constexpr inline dim3 block_dim() noexcept {
                return dim3(1, 1, 1); // Thread execution uses single thread
            }

            __device__ __host__ static constexpr inline bool is_predicated() noexcept {
                return false;
            }
        };
    }
}

#endif // CUFFTDX_TRAITS_DETAIL_WORKING_GROUP_HPP