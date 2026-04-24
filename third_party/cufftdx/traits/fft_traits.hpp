// Copyright (c) 2019-2024, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_TRAITS_FFT_TRAITS_HPP
#define CUFFTDX_TRAITS_FFT_TRAITS_HPP

#include "cufftdx/detail/fft_description_fd.hpp"

#include "cufftdx/operators.hpp"

#include "cufftdx/traits/detail/description_traits.hpp"
#include "cufftdx/traits/detail/make_complex_type.hpp"
#include "cufftdx/traits/detail/working_group.hpp"

#include "commondx/traits/dx_traits.hpp"

namespace cufftdx {
    template<class Description>
    struct size_of {
    private:
        static constexpr bool has_size = detail::has_operator<fft_operator::size, Description>::value;
        static_assert(has_size, "Description does not have size defined");

    public:
        using value_type                  = unsigned int;
        static constexpr value_type value = detail::get_t<fft_operator::size, Description>::value;
        constexpr                   operator value_type() const noexcept { return value; }
    };

    // size_of
    template<class Description>
    constexpr unsigned int size_of<Description>::value;

    template<class Description>
    inline constexpr unsigned int size_of_v = size_of<Description>::value;

    // sm_of
    template<class Description>
    using sm_of = commondx::sm_of<fft_operator, Description>;

    template<class Description>
    inline constexpr unsigned int sm_of_v = sm_of<Description>::value;

    // type_of
    template<class Description>
    struct type_of {
        using value_type = fft_type;
        static constexpr value_type value =
            detail::get_or_default_t<fft_operator::type, Description, Type<fft_type::c2c>>::value;
        constexpr operator value_type() const noexcept { return value; }
    };

    template<class Description>
    constexpr fft_type type_of<Description>::value;

    template<class Description>
    inline constexpr fft_type type_of_v = type_of<Description>::value;

    // real_fft_layout_of
    template<class Description>
    struct real_fft_layout_of {
        using value_type = complex_layout;
        static constexpr value_type value =
            detail::get_or_default_t<fft_operator::real_fft_options, Description, RealFFTOptions<complex_layout::natural, real_mode::normal>>::layout;
        constexpr operator value_type() const noexcept { return value; }
    };

    template<class Description>
    constexpr complex_layout real_fft_layout_of<Description>::value;

    template<class Description>
    inline constexpr complex_layout real_fft_layout_of_v = real_fft_layout_of<Description>::value;

    // real_fft_mode_of
    template<class Description>
    struct real_fft_mode_of {
        using value_type = real_mode;
        static constexpr value_type value =
            detail::get_or_default_t<fft_operator::real_fft_options, Description, RealFFTOptions<complex_layout::natural, real_mode::normal>>::mode;
        constexpr operator value_type() const noexcept { return value; }
    };

    template<class Description>
    constexpr real_mode real_fft_mode_of<Description>::value;

    template<class Description>
    inline constexpr real_mode real_fft_mode_of_v = real_fft_mode_of<Description>::value;

    // direction_of
    template<class Description>
    struct direction_of {
    private:
        using deduced_fft_direction = detail::deduce_direction_type_t<Type<type_of<Description>::value>>;
        using this_fft_direction =
            detail::get_or_default_t<fft_operator::direction, Description, deduced_fft_direction>;

        static_assert(!CUFFTDX_STD::is_void<this_fft_direction>::value,
                      "Description has neither direction defined, nor it can be deduced from its type");

    public:
        using value_type                  = fft_direction;
        static constexpr value_type value = this_fft_direction::value;
        constexpr                   operator value_type() const noexcept { return value; }
    };

    template<class Description>
    constexpr fft_direction direction_of<Description>::value;

    template<class Description>
    inline constexpr fft_direction direction_of_v = direction_of<Description>::value;

    // precision_of
    template<class Description>
    using precision_of = commondx::precision_of<fft_operator, Description, detail::default_fft_precision_operator>;

    template<class Description>
    using precision_of_t = typename precision_of<Description>::type;

    // is_fft
    template<class Description>
    using is_fft = commondx::is_dx_expression<Description>;

    template<class Description>
    inline constexpr bool is_fft_v = commondx::is_dx_expression<Description>::value;

    // is_fft_execution
    template<class Description>
    using is_fft_execution = commondx::is_dx_execution_expression<fft_operator, Description>;

    template<class Description>
    inline constexpr bool is_fft_execution_v = commondx::is_dx_execution_expression<fft_operator, Description>::value;

    // is_complete_fft
    template<class Description>
    using is_complete_fft = commondx::is_complete_dx_expression<Description, detail::is_complete_description>;

    template<class Description>
    inline constexpr bool is_complete_fft_v = commondx::is_complete_dx_expression<Description, detail::is_complete_description>::value;

    // is_complete_fft_execution
    template<class Description>
    using is_complete_fft_execution =
        commondx::is_complete_dx_execution_expression<fft_operator, Description, detail::is_complete_description>;

    template<class Description>
    inline constexpr bool is_complete_fft_execution_v =
        commondx::is_complete_dx_execution_expression<fft_operator, Description, detail::is_complete_description>::value;

    // extract_fft_description
    template<class Description>
    using extract_fft_description = commondx::extract_dx_description<detail::fft_description, Description, fft_operator>;

    template<class Description>
    using extract_fft_description_t = typename extract_fft_description<Description>::type;

    // working_group_of
    template<class Description>
    struct working_group_of {
    private:
        static_assert(is_complete_fft_execution_v<Description>,
                    "Description must be a complete FFT execution description");

    public:
        // Forward to the FFT's working_group type alias
        using value_type = typename Description::working_group;
        static constexpr value_type value{};
        constexpr operator value_type() const noexcept { return value; }
    };

    template<class Description>
    constexpr typename working_group_of<Description>::value_type working_group_of<Description>::value;

    template<class Description>
    inline constexpr auto working_group_of_v = working_group_of<Description>::value;

    namespace experimental {
        // code_type_of
        template<class Description>
        struct code_type_of {
            using value_type = code_type;
            static constexpr value_type value =
                detail::get_or_default_t<fft_operator::experimental_code_type, Description, CodeType<code_type::ptx>>::value;
            constexpr operator value_type() const noexcept { return value; }
        };

        template<class Description>
        constexpr code_type code_type_of<Description>::value;

        template<class Description>
        inline constexpr code_type code_type_of_v = code_type_of<Description>::value;

        template<class Description>
        struct is_dynamic_batching_enabled {
            static constexpr bool value = detail::has_operator<fft_operator::experimental_dynamic_batching, Description>::value;
            constexpr operator bool() const noexcept { return value; }
        };

        template<class Description>
        inline constexpr bool is_dynamic_batching_enabled_v = is_dynamic_batching_enabled<Description>::value;

    } // namespace experimental

    namespace detail {
        template<class Description>
        struct convert_to_fft_description {
            using type = void;
        };

        template<template<class...> class Description, class... Types>
        struct convert_to_fft_description<Description<Types...>> {
            using type = typename detail::fft_description<Types...>;
        };
    } // namespace detail
} // namespace cufftdx

#endif // CUFFTDX_TRAITS_FFT_TRAITS_HPP
