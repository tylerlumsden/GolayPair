file(READ "${CMAKE_CURRENT_SOURCE_DIR}/view_types.h" VIEW_TYPES_CONTENT)
configure_file(jit_headers.h.in ${CMAKE_CURRENT_BINARY_DIR}/jit_headers.h)

add_library(gpu_utils STATIC
    flat_perm_list.cu
)
target_include_directories(gpu_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(gpu_utils PRIVATE CUDA::cufft CUDA::cudart)
