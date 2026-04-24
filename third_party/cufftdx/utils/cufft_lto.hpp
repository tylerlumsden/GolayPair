// Copyright (c) 2025, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#ifndef CUFFTDX_UTILS_CUFFT_LTO_HPP
#define CUFFTDX_UTILS_CUFFT_LTO_HPP

#include <vector>
#include <tuple>
#include <iostream>
#include <cufft_device.h>

// Check cuFFT Device API version
#define CUFFT_DEVICE_API_MIN_VERSION 200

#ifndef CUFFT_CHECK_AND_EXIT
#    define CUFFT_CHECK_AND_EXIT(error)                                                 \
        {                                                                               \
            auto status = static_cast<cufftResult>(error);                              \
            if (status != CUFFT_SUCCESS) {                                              \
                std::cout << status << " " << __FILE__ << ":" << __LINE__ << std::endl; \
                std::exit(status);                                                      \
            }                                                                           \
        }
#endif // CUFFT_CHECK_AND_EXIT

namespace cufftdx {
    namespace utils {

        inline bool check_cufft_device_api_version() {
            int device_api_version = 0;
            CUFFT_CHECK_AND_EXIT(cufftDeviceGetVersion(&device_api_version));

            int major = device_api_version / 1000;
            int minor = (device_api_version % 1000) / 100;

            int major_min = CUFFT_DEVICE_API_MIN_VERSION / 1000;
            int minor_min = (CUFFT_DEVICE_API_MIN_VERSION % 1000) / 100;

            if (major != major_min || (major == major_min && minor < minor_min)) {
                std::cerr << "Error: cuFFT Device API minimum required version is not met or major version is not the same. Found version "
                          << major << "." << minor << ".*, but major version is " << major_min << " and minimum required version is " << major_min << "." << minor_min << ".*.\n";
                return false;
            }
            return true;
        }

        inline auto get_database_and_ltoir(unsigned       fft_size,
                                    fft_direction  dir,
                                    fft_type       type,
                                    unsigned       sm,
                                    execution_type execution,
                                    precision      prec           = precision::f32,
                                    complex_layout layout         = complex_layout::natural,
                                    real_mode      rmode          = real_mode::normal,
                                    unsigned       fft_ept        = 0 /* use heuristic */,
                                    unsigned       ffts_per_block = 1 /* 0: use suggested ffts_per_block */) {

            std::vector<char> database_str;
            std::vector<std::vector<char>> codes;

            dim3 block_dim = {1,1,1};
            unsigned shared_memory_size = 0;

            auto backend = frontend_to_backend(algorithm::ct, execution, fft_size, type, dir, sm, rmode, fft_ept, 0, experimental::code_type::ltoir);

            cufftDescriptionHandle desc_handle;
            CUFFT_CHECK_AND_EXIT(cufftDescriptionCreate(&desc_handle));
            CUFFT_CHECK_AND_EXIT(cufftDescriptionSetTraitInt64(desc_handle, CUFFT_DESC_TRAIT_SIZE, static_cast<long long int>(backend.size)));
            CUFFT_CHECK_AND_EXIT(cufftDescriptionSetTraitInt64(desc_handle, CUFFT_DESC_TRAIT_SM, static_cast<long long int>(backend.sm)));
            CUFFT_CHECK_AND_EXIT(cufftDescriptionSetTraitInt64(desc_handle, CUFFT_DESC_TRAIT_ELEMENTS_PER_THREAD, static_cast<long long int>(backend.elements_per_thread)));

            auto cufft_dir = CUFFT_DESC_FORWARD;
            switch (backend.direction) {
                case fft_direction::forward: cufft_dir = CUFFT_DESC_FORWARD; break;
                case fft_direction::inverse: cufft_dir = CUFFT_DESC_INVERSE; break;
            }
            CUFFT_CHECK_AND_EXIT(cufftDescriptionSetTraitInt64(desc_handle, CUFFT_DESC_TRAIT_DIRECTION, static_cast<long long int>(cufft_dir)));

            auto cufft_type = CUFFT_DESC_C2C;
            switch (backend.type) {
                case fft_type::c2c: cufft_type = CUFFT_DESC_C2C; break;
                case fft_type::c2r: cufft_type = CUFFT_DESC_C2R; break;
                case fft_type::r2c: cufft_type = CUFFT_DESC_R2C; break;
            }
            CUFFT_CHECK_AND_EXIT(cufftDescriptionSetTraitInt64(desc_handle, CUFFT_DESC_TRAIT_TYPE, static_cast<long long int>(cufft_type)));

            auto cufft_precision = CUFFT_DESC_SINGLE;
            switch (prec) {
                case precision::f16: cufft_precision = CUFFT_DESC_HALF; break;
                case precision::f32: cufft_precision = CUFFT_DESC_SINGLE; break;
                case precision::f64: cufft_precision = CUFFT_DESC_DOUBLE; break;
            }
            CUFFT_CHECK_AND_EXIT(cufftDescriptionSetTraitInt64(desc_handle, CUFFT_DESC_TRAIT_PRECISION, static_cast<long long int>(cufft_precision)));

            cufftDeviceHandle device_handle;
            CUFFT_CHECK_AND_EXIT(cufftDeviceCreate(&device_handle, 1, &desc_handle));

            size_t func_count;
            CUFFT_CHECK_AND_EXIT(cufftDeviceGetNumDeviceFunctions(device_handle, desc_handle, &func_count));
            if (func_count > 0) {
                std::vector<cufftDeviceFunctionHandle> funcs(func_count);
                CUFFT_CHECK_AND_EXIT(cufftDeviceGetDeviceFunctions(device_handle, desc_handle, funcs.size(), funcs.data()));

                long long int func_elements_per_thread;
                long long int func_suggested_ffts_per_block;
                long long int func_smem_per_fft;
                long long int func_storage_size;

                CUFFT_CHECK_AND_EXIT(cufftDeviceGetDeviceFunctionTraitInt64(device_handle, funcs[0], CUFFT_DEVICE_FUNC_TRAIT_SUGGESTED_FFTS_PER_BLOCK, &func_suggested_ffts_per_block));
                CUFFT_CHECK_AND_EXIT(cufftDeviceGetDeviceFunctionTraitInt64(device_handle, funcs[0], CUFFT_DEVICE_FUNC_TRAIT_SHARED_MEMORY_PER_FFT, &func_smem_per_fft));
                CUFFT_CHECK_AND_EXIT(cufftDeviceGetDeviceFunctionTraitInt64(device_handle, funcs[0], CUFFT_DEVICE_FUNC_TRAIT_ELEMENTS_PER_THREAD, &func_elements_per_thread));
                CUFFT_CHECK_AND_EXIT(cufftDeviceGetDeviceFunctionTraitInt64(device_handle, funcs[0], CUFFT_DEVICE_FUNC_TRAIT_STORAGE_SIZE, &func_storage_size));

                auto frontend = detail::backend_to_frontend(execution,
                                                            (fft_ept != 0),
                                                            type,
                                                            layout,
                                                            rmode,
                                                            prec,
                                                            ffts_per_block,
                                                            backend.size,
                                                            func_elements_per_thread,
                                                            func_suggested_ffts_per_block,
                                                            func_smem_per_fft,
                                                            func_storage_size,
                                                            func_elements_per_thread,
                                                            func_suggested_ffts_per_block,
                                                            false,
                                                            0,
                                                            0,
                                                            0);

                block_dim = {frontend.block_dim_x, frontend.block_dim_y, frontend.block_dim_z};
                shared_memory_size = frontend.shared_memory_size;

                size_t database_str_size = 0;
                CUFFT_CHECK_AND_EXIT(cufftDeviceGetDatabaseStrSize(device_handle, &database_str_size, funcs[0]));
                if(database_str_size > 0) {
                    database_str.resize(database_str_size);
                    CUFFT_CHECK_AND_EXIT(cufftDeviceGetDatabaseStr(device_handle, database_str.size(), database_str.data(), funcs[0]));
                }

                size_t count = 0;
                CUFFT_CHECK_AND_EXIT(cufftDeviceGetNumLTOIRs(device_handle, &count, funcs[0]));
                if (count > 0) {
                    std::vector<size_t> code_sizes(count);
                    CUFFT_CHECK_AND_EXIT(cufftDeviceGetLTOIRSizes(device_handle, code_sizes.size(), code_sizes.data(), funcs[0]));
                    for (auto size : code_sizes) {
                        codes.push_back(std::vector<char>(size));
                    }
                    std::vector<char*> code_ptrs;
                    for (auto& code : codes) {
                        code_ptrs.push_back(code.data());
                    }
                    std::vector<cufftDeviceCodeContainer> code_containers(count);
                    CUFFT_CHECK_AND_EXIT(cufftDeviceGetLTOIRs(device_handle, code_ptrs.size(), code_ptrs.data(), code_containers.data(), funcs[0]));

                }
            }
            CUFFT_CHECK_AND_EXIT(cufftDeviceDestroy(device_handle));
            return std::make_tuple(database_str.size() > 0 ? std::string(database_str.data()) : std::string(),
                                   codes,
                                   block_dim,
                                   shared_memory_size);
        }
    }
}

#endif // CUFFTDX_UTILS_CUFFT_LTO_HPP
