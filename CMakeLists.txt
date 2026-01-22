cmake_minimum_required(VERSION 3.16)
project(GolayPair)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g -O3")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
endif()

# Find MPI
find_package(MPI REQUIRED)

# Find FFTW3 library
find_library(FFTW3_LIB fftw3 HINTS /usr/local/lib)
find_path(FFTW3_INCLUDE fftw3.h HINTS /usr/local/include)

# Find Boost (multiprecision headers)
find_package(Boost REQUIRED COMPONENTS)
find_path(BOOST_MULTIPRECISION_INCLUDE boost/multiprecision/cpp_int.hpp)
if(NOT BOOST_MULTIPRECISION_INCLUDE)
    message(FATAL_ERROR "Boost.Multiprecision headers not found")
endif()

if(NOT FFTW3_LIB)
    message(FATAL_ERROR "FFTW3 library not found")
endif()

include_directories(${FFTW3_INCLUDE} ${BOOST_MULTIPRECISION_INCLUDE} include)

# Library source files
set(LIB_SOURCES
    lib/binary.cpp
    lib/golay.cpp
    lib/fourier.cpp
    lib/orderly_equivalence.cpp
    lib/equivalence.cpp
    lib/array.cpp
    lib/coprimes.cpp
    lib/decomps.cpp
    lib/io.cpp
)

# Create a static library
add_library(golay_lib STATIC ${LIB_SOURCES})
target_link_libraries(golay_lib ${FFTW3_LIB} m)

# Main executable
add_executable(main src/main.cpp src/generate_hybrid.cpp src/match_pairs.cpp src/sort.cpp src/uncompression.cpp src/filter.cpp src/lyndon.cpp)
target_link_libraries(main golay_lib MPI::MPI_CXX)