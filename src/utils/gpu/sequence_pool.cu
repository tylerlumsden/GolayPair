#include "sequence_pool.h"
#include "view_types.h"
#include <thrust/device_vector.h>

struct SequencePool::Impl {
    thrust::device_vector<float> values;
    size_t len;
    size_t bat;

    Impl(size_t len, size_t bat) : values(len * bat), len(len), bat(bat) {}
};

SequencePool::SequencePool(size_t length, size_t batch)
    : impl(std::make_unique<Impl>(length, batch)) {}

SequencePool::~SequencePool() = default;

float* SequencePool::device_data() {
    return thrust::raw_pointer_cast(impl->values.data());
}

size_t SequencePool::length() const    { return impl->len; }
size_t SequencePool::batch_size() const { return impl->bat; }

SequencePool::View SequencePool::get_view() {
    return View(device_data(), impl->len, impl->bat);
}
