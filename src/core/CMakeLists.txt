add_library(core SHARED
    filter.cpp
    generate_hybrid.cpp
    sort.cpp
    match_pairs.cpp
    uncompression.cpp
    uncompression_kernel.cu
)
target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${GOLAYPAIR_BOOST_MULTIPRECISION_INCLUDE}
)
target_link_libraries(core PUBLIC utils CUDA::cufft CUDA::cudart)