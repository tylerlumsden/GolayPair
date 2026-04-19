#pragma once
#include <memory>
#include <cstddef>

class SequencePool {
public:
    SequencePool(size_t length, size_t batch);
    ~SequencePool();
    SequencePool(const SequencePool&) = delete;
    SequencePool& operator=(const SequencePool&) = delete;

    float*  device_data();
    size_t  length() const;
    size_t  batch_size() const;

    struct View;
    View get_view();

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
