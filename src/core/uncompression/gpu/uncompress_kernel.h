#pragma once
#include <vector>
#include <span>
#include <functional>
#include <memory>

using PermList = std::vector<std::vector<std::vector<int>>>;

class UncompressKernel {
public:
    UncompressKernel(PermList& permutations, int compress, int new_compress, int order, int paf_constant);
    ~UncompressKernel();
    UncompressKernel(const UncompressKernel&) = delete;
    UncompressKernel& operator=(const UncompressKernel&) = delete;

    void run(const std::vector<int>& seq,
             std::function<void(std::span<int>, std::span<double>)> writer);

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
