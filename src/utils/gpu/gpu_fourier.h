#pragma once
#include <memory>

class SequencePool;
class FourierPool;

class GPUFourier {
public:
    GPUFourier(SequencePool& input, FourierPool& output);
    ~GPUFourier();
    GPUFourier(const GPUFourier&) = delete;
    GPUFourier& operator=(const GPUFourier&) = delete;

    void launch_batch();

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
