#pragma once
#include <vector>
#include <span>
#include <functional>
#include <memory>
#include <cstddef>

using PermList = std::vector<std::vector<std::vector<int>>>;

class UncompressKernel {
public:
    UncompressKernel(PermList& permutations, const std::vector<int>& seq,
                     size_t new_length, size_t items_per_iter);
    ~UncompressKernel();
    UncompressKernel(const UncompressKernel&) = delete;
    UncompressKernel& operator=(const UncompressKernel&) = delete;

    const std::vector<int>& radices() const;
    size_t items_per_iter() const;

    void   set_offset(const std::vector<int>& mixed_radix);
    void   launch_cartesian_product(size_t blocks, size_t threads);
    void   launch_fft();
    size_t launch_sequence_filter(size_t blocks, size_t threads, int order, int paf_constant);
    void   write_filtered(size_t count,
                          std::function<void(std::span<int>, std::span<double>)> writer);

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
