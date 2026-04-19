#pragma once
#include <memory>
#include <cstddef>

class FourierPool {
public:
    FourierPool(size_t length, size_t batch);
    ~FourierPool();
    FourierPool(const FourierPool&) = delete;
    FourierPool& operator=(const FourierPool&) = delete;

    void*  device_data();
    size_t length() const;
    size_t batch_size() const;

    struct View;
    View get_view();

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
