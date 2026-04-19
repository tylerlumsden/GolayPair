#include "fourier_pool.h"
#include "view_types.h"
#include <thrust/device_vector.h>

struct FourierPool::Impl {
    thrust::device_vector<cuComplex> values;
    size_t len;
    size_t bat;

    Impl(size_t len, size_t bat) : values(len * bat), len(len), bat(bat) {}
};

FourierPool::FourierPool(size_t length, size_t batch)
    : impl(std::make_unique<Impl>(length, batch)) {}

FourierPool::~FourierPool() = default;

void* FourierPool::device_data() {
    return thrust::raw_pointer_cast(impl->values.data());
}

size_t FourierPool::length() const    { return impl->len; }
size_t FourierPool::batch_size() const { return impl->bat; }

FourierPool::View FourierPool::get_view() {
    return View(reinterpret_cast<cuComplex*>(device_data()), impl->len, impl->bat);
}
