set(UNCOMPRESS_SOURCE
    uncompression.cpp
    cpu/uncompress_cpu.cpp
)

if(GPU_ARCH)
    list(APPEND UNCOMPRESS_SOURCE
        gpu/uncompress_kernel_interface.cpp
        gpu/uncompress_kernel.cu
    )
endif()

add_library(uncompress STATIC ${UNCOMPRESS_SOURCE})

target_include_directories(uncompress
    PUBLIC  
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/cpu
        ${CMAKE_CURRENT_SOURCE_DIR}/gpu
        ${GOLAYPAIR_BOOST_MULTIPRECISION_INCLUDE}
)

if(GPU_ARCH)
    target_link_libraries(uncompress PRIVATE utils match sort gpu_utils CUDA::cufft CUDA::cudart)
else()
    target_link_libraries(uncompress PRIVATE utils match sort)
endif()
