#include <span>
#include <limits>
#include <vector>
#include <fstream>
#include <string>
#include <functional>
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
    std::ifstream& input,
    std::ofstream& out_pairs,
    const std::string& work_dir,
    const std::string& prefix = "",
    size_t range_begin = 0,
    size_t range_end = std::numeric_limits<size_t>::max(),
    size_t step = 1,
    DeviceType dev = DeviceType::CPU
);

void uncompress_kernel(
  std::vector<int> seq, 
  PermList permutations, 
  size_t new_length, 
  int order, 
  int paf_constant,
  std::function<void(std::span<int>, std::span<double>)> writer
);