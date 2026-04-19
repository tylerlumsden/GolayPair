#include <vector>
#include "uncompress_kernel.h"
#include "uncompress_kernel_impl.h"

void UncompressKernel::run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer) {
    this->impl->launch_kernel();
}
