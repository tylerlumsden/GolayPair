#pragma once
#include <memory>
#include <vector>
#include <cstdint>

class MixedRadixPool {
public:
    MixedRadixPool(const std::vector<int>& radices, uint64_t items_per_iter);
    ~MixedRadixPool();
    MixedRadixPool(const MixedRadixPool&) = delete;
    MixedRadixPool& operator=(const MixedRadixPool&) = delete;

    void set_base(const std::vector<int>& mixed_base);
    const std::vector<int>& radices() const;

    struct View;
    View get_view();

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
