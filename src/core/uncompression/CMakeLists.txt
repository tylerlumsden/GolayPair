add_library(uncompress STATIC
    uncompression.cpp
    cpu/uncompress_cpu.cpp
    gpu/uncompress_kernel_interface.cpp
    gpu/uncompress_kernel.cu
)

target_include_directories(uncompress
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/cpu
        ${CMAKE_CURRENT_SOURCE_DIR}/gpu
        ${GOLAYPAIR_BOOST_MULTIPRECISION_INCLUDE}
)

target_link_libraries(uncompress PRIVATE utils match sort CUDA::cufft CUDA::cudart)