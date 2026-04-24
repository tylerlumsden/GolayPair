#pragma once

#include <vector>
#include <fstream>
#include <stdexcept>

#ifdef USE_GPU
    int uncompress_gpu(std::vector<int>& orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, const int PROC_ID, const int PROC_NUM, std::ofstream& outfile, int seqflag);
#else

    template<typename... Args>
    int uncompress_gpu(Args&&...) {
        throw std::runtime_error("Built without GPU support (See README.md for compiling with CUDA)");
    }

#endif