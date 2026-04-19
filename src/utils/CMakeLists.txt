add_library(utils STATIC
    array.cpp
    binary.cpp
    coprimes.cpp
    decomps.cpp
    equivalence.cpp
    fourier.cpp
    golay.cpp
    io.cpp
    lyndon.cpp
    orderly_equivalence.cpp
)
target_include_directories(utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${GOLAYPAIR_FFTW3_INCLUDE}
)
target_link_libraries(utils PUBLIC ${GOLAYPAIR_FFTW3_LIB} m)

if(GPU_ARCH)
    add_subdirectory(gpu)
endif()