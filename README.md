This repository contains a set of procedures for the generation and post-processing of binary periodic complementary sequences.

# Overview

This generation pipeline was used to construct the first example of periodic Golay pairs of length 90, which resolved the question of their existence entirely.

Published in AMS Mathematics of Computation at: https://doi.org/10.1090/mcom/4096

Arxiv preprint available at: https://doi.org/10.48550/arXiv.2408.15611

# Prerequisites

To compile and run our code, you are required to have installed the following:

```CMake``` (Minimum version 3.16)

```A valid C++ compiler``` (Minimum standard C++20)

```FFTW``` (version 3.3.10)

In Linux, these can all be installed easily with the default package manager using apt-get. The FFTW documentation is located at https://fftw.org/.

It may be possible to compile on Windows, but we have not tried. For ease of use, I recommend using WSL2 (Windows Subsystem for Linux) for building and running on Windows.

# Build

Compilation of our code is handled by CMake, so to compile our procedures you should enter the root directory and run the command ```cmake --preset=release``` or ```cmake --preset=debug``` for development. Then, to build the project run the ```cmake --build build/release``` or ```cmake --build build/debug``` commands respectively. 

# Running the pipeline

The generation pipeline is launched from the executable compiled from main.cpp, which handles the configuration of each run.

The CMake standard directory structure places each executable in the build/${preset} directory, so to run the pipeline from the root directory you can locate the executables through ```build/debug/main``` or ```build/debug/release``` respectively.

### Run the generation pipeline as follows:

```bash
# To see the valid list of OPTIONS, run ./build/debug/main --help
./build/debug/main [OPTIONS] [order]
```

### Example configuration:

```bash
# Generates all periodic Golay pairs of order 16 by generating all 2-compressions
# Uncompresses to a compression value of 1
# By default runs the full pipeline (Candidate Generation, Sorting, Matching, Uncompression, Filtering)
./build/debug/main 16 --compress 2 1
```

By default the pipeline only generates periodic complementary sequences from the family of periodic Golay pairs. To adjust this, you can add the flag ```--paf [PAF Constant]``` to generate complementary sequences with other PAF constant requirements (e.g. The PAF Constant for Legendre pairs is -2). 

Valid compression factor values include any number which divides the order value. To uncompress in the same run, or use incremental uncompression, provide a list of compression values via ```--compress [Uncompression List]```.

The temp directory of our procedures by default will be located in the ```results``` directory. This can be changed with the ```--dir [Path]``` flag.

# Procedures

The ```src``` directory contains all source files containing runnable procedures which compile to a ```main``` function.

The ```lib``` directory contains all source files containing helper functions for our main procedures.



