#pragma once

#include <span>
#include <limits>
#include <vector>
#include <fstream>
#include <string>
#include <functional>

#include "io.h"
using PermList = std::vector<std::vector<std::vector<int>>>;
int uncompress_recursive(std::vector<int>& orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, const int PROC_ID, const int PROC_NUM, std::ofstream& outfile, int seqflag);

enum DeviceType {
  CPU,
  GPU
};

int uncompress_pipeline(
    int order, 
    int compress,
    int new_compress,
    int paf_constant,
    IO::PairReader&,
    IO::PairWriter&,
    const std::string& work_dir,
    const std::string& prefix = "",
    DeviceType dev = DeviceType::CPU
);
