This repository contains a set of procedures for the generation and post-processing of Periodic Golay Pairs.

## Prerequisites

To compile and run our code, you are required to have installed the following:

```A valid C++ compiler``` (our code is compiled using the ```g++``` command)

```FFTW``` (version 3.3.10)

The FFTW instructions for installing the FFTW library are located at https://fftw.org/.

Due to the FFTW library, our code can only be compiled in a unix environment.

## Usage

Compilation of our code is handled by a CMake, so to compile our procedures you should enter the root directory and run the command ```cmake --preset=release ``` or ```cmake --preset=debug ``` for development. Then, to build the project run the ``` cmake --build build/release ``` or ```cmake --build build/debug ``` commands respectively. 

## Driver Script

Our driver script is usable with the following commands:

```bash
./driver.sh [Length] [Compression Factor]
```

Valid length values for searching with our code include: 2, 4, 8, 10, 16, 18, 20, 26, 32, 34, 36, 40, 50, 52, 58, 64, 68, 72, 74, 80, 82, and 90.

Valid compression factor values include any number which divides the length value. To search without compression, use a compression factor of 1.

The output of our procedures will be located in the ```results``` directory, stored in the file [Length]-pairs-found

## Procedures

The ```src``` directory contains all source files containing runnable procedures which compile to a ```main``` function.

The ```lib``` directory contains all source files containing helper functions for our main procedures.



