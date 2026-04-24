set(UNCOMPRESS_SOURCE
    uncompression.cpp
    cpu/uncompress_cpu.cpp
)

if(GPU_ARCH)
    list(APPEND UNCOMPRESS_SOURCE
        gpu/uncompress_gpu.cpp
        gpu/impl/uncompress_kernel.cpp
    )
endif()

add_library(uncompress STATIC ${UNCOMPRESS_SOURCE})

target_include_directories(uncompress
    PUBLIC  
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/cpu
        ${CMAKE_CURRENT_SOURCE_DIR}/gpu
        ${CMAKE_CURRENT_SOURCE_DIR}/gpu/impl
        ${GOLAYPAIR_BOOST_MULTIPRECISION_INCLUDE}
        ${GOLAYPAIR_THIRD_PARTY_DIR}
)

if(GPU_ARCH)
    target_link_libraries(uncompress PRIVATE utils match sort gpu_utils CUDA::cufft CUDA::cudart CUDA::cuda_driver CUDA::nvrtc)
    target_compile_definitions(uncompress PRIVATE JITIFY_LINK_CUDA_STATIC=1 JITIFY_LINK_NVRTC_STATIC=1)
else()
    target_link_libraries(uncompress PRIVATE utils match sort)
endif()
