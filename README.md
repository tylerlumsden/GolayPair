The first section of texts is from @yc518suray. The second section of texts is from the original README.

This repository is forked from @tylerlumsden. The codes are used to search for periodic Golay pairs (PGPs or PCPs) with lengths up to 130, as an midterm project in the class **Sequence Design for Communications** in NCKU, 2025 fall.

## Modifications

No modifications yet.

---

This repository contains a set of procedures for the generation and post-processing of Periodic Golay Pairs.

## Prerequisites

To compile and run our code, you are required to have installed the following:

```A valid C++ compiler``` (our code is compiled using the ```g++``` command)

```FFTW``` (version 3.3.10)

The FFTW instructions for installing the FFTW library are located at https://fftw.org/.

Due to the FFTW library, our code can only be compiled in a unix environment.

## Usage

Compilation of our code is handled by a Makefile, so to compile our procedures you should enter the directory where the Makefile is located, and enter the bash command ```make```, ensuring no errors are produced.

To run our code, we have a driver script that handles the interactions between our different procedures.

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



