add_library(gpu_utils STATIC
    flat_perm_list.cu
)
target_include_directories(gpu_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gpu_utils PRIVATE CUDA::cufft CUDA::cudart)
