#include "mixed_radix_pool.h"
#include "view_types.h"
#include "cuda_error.h"

struct MixedRadixPool::Impl {
    int*             num_pool;
    int*             base_num;
    int*             d_radices;
    int              digits;
    std::vector<int> host_radices;

    Impl(const std::vector<int>& input_radices, uint64_t num_threads) {
        digits = input_radices.size();
        check_cuda_error(cudaMalloc(&d_radices, digits * sizeof(int)));
        check_cuda_error(cudaMalloc(&base_num,  digits * sizeof(int)));
        check_cuda_error(cudaMalloc(&num_pool,  num_threads * digits * sizeof(int)));
        check_cuda_error(cudaMemcpy(d_radices, input_radices.data(), digits * sizeof(int), cudaMemcpyHostToDevice));
        host_radices = input_radices;
        std::vector<int> zeros(digits, 0);
        set_base(zeros);
    }

    ~Impl() {
        cudaFree(num_pool);
        cudaFree(base_num);
        cudaFree(d_radices);
    }

    void set_base(const std::vector<int>& mixed_base) {
        check_cuda_error(cudaMemcpy(base_num, mixed_base.data(), digits * sizeof(int), cudaMemcpyHostToDevice));
    }
};

MixedRadixPool::MixedRadixPool(const std::vector<int>& radices, uint64_t items_per_iter)
    : impl(std::make_unique<Impl>(radices, items_per_iter)) {}

MixedRadixPool::~MixedRadixPool() = default;

void MixedRadixPool::set_base(const std::vector<int>& mixed_base) {
    impl->set_base(mixed_base);
}

const std::vector<int>& MixedRadixPool::radices() const {
    return impl->host_radices;
}

MixedRadixPool::View MixedRadixPool::get_view() {
    return View(impl->num_pool, impl->base_num, impl->d_radices, impl->digits);
}
