#include <cstdio>
#include <vector>
#include <cuda_runtime.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <stdexcept>
#include <format>
#include <chrono>

#include "uncompress_kernel.h"
#include "cuda_error.h"
#include "flat_perm_list.h"
#include "memorypool.h"

using BigInt = boost::multiprecision::cpp_int;

UncompressKernel::UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant)
    : order(order), compress(compress), new_compress(new_compress), paf_constant(paf_constant), permutations(permutations) {

    this->length     = order / compress;
    this->new_length = order / new_compress;
}

void UncompressKernel::run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer) {
    if (seq.size() != this->length) {
        throw std::invalid_argument(
            std::format("Compressed sequence length of {} is not equal to kernel length of {}", seq.size(), this->length)
        );
    }

    std::vector<int> radices;
    for (auto list : this->permutations) {
        radices.push_back(list.size());
    }

    BigInt search_count = 1;
    for (int num : radices) {
        search_count *= num;
    }
    std::cout << "Uncompression search space size: " << search_count << "\n";

    FlatPermList perm_list(this->permutations);

    // Precompute Barrett magic numbers: magic[i] = (1ULL << 32) / radices[i].
    // d=1 must be special-cased: (1ULL<<32)/1 = 0x100000000 truncates to 0 as uint32_t,
    // breaking the reduction. UINT32_MAX gives the correct result for d=1.
    std::vector<uint32_t> magic(this->length);
    for (size_t i = 0; i < this->length; i++) {
        uint64_t d = (uint64_t)radices[i];
        magic[i] = (d <= 1) ? UINT32_MAX : (uint32_t)((1ULL << 32) / d);
    }

    size_t free_mem, total_mem;
    cudaMemGetInfo(&free_mem, &total_mem);

    constexpr size_t max_per_iter = 1000000;
    size_t items_per_iter = static_cast<size_t>(
        std::min(
            search_count,
            static_cast<BigInt>(std::min(
                MemoryPool<int>::items_storable(this->new_length, free_mem),
                max_per_iter
            ))
        )
    );

    printf("Iterating with %zu sequences per iteration\n", items_per_iter);

    MemoryPool<uint32_t> magic_buf(1, this->length);
    MemoryPool<int>      radix_offset(1, this->length);
    MemoryPool<int>      base_radices_buf(1, this->length);
    MemoryPool<float>    output(items_per_iter, this->new_length);
    MemoryPool<int>      input_output(items_per_iter, this->new_length);

    check_cuda_error(cudaMemcpy(magic_buf.values, magic.data(), this->length * sizeof(uint32_t), cudaMemcpyHostToDevice));

    unsigned int* output_count;
    check_cuda_error(cudaMalloc(&output_count, sizeof(unsigned int)));
    check_cuda_error(cudaMemcpy(base_radices_buf.values, radices.data(), this->length * sizeof(int), cudaMemcpyHostToDevice));

    const float threshold = 2.0f * order - paf_constant + 0.01f;
    const dim3 block(THREADS_PER_BLOCK);
    auto perm_data_info = perm_list.data();
    const size_t perm_smem = (size_t)(perm_data_info.indexes_size + perm_data_info.data_size) * sizeof(int);
    const size_t smem = THREADS_PER_BLOCK * smem_char_stride((int)this->new_length) + perm_smem;
    printf("Perm table: %d indexes + %d values = %.1f KB in smem\n",
           perm_data_info.indexes_size, perm_data_info.data_size, perm_smem / 1024.0);
    BigInt total_count = 0;
    double kernel_ms = 0.0, gpu_kernel_ms = 0.0, writer_ms = 0.0;

    using Clock = std::chrono::high_resolution_clock;
    auto run_start = Clock::now();

    cudaEvent_t ev_start, ev_stop;
    check_cuda_error(cudaEventCreate(&ev_start));
    check_cuda_error(cudaEventCreate(&ev_stop));

    for (BigInt offset = 0; offset < search_count; offset += items_per_iter) {
        std::cout << "Current Offset: " << offset << "\n";
        BigInt remaining       = search_count - offset;
        size_t items_this_iter = static_cast<size_t>(std::min(remaining, static_cast<BigInt>(items_per_iter)));

        check_cuda_error(cudaMemset(output_count, 0, sizeof(unsigned int)));

        std::vector<int> offset_radix(this->length);
        BigInt temp_offset = offset;
        for (int i = (int)this->length - 1; i >= 0; i--) {
            offset_radix[i] = static_cast<int>(temp_offset % radices[i]);
            temp_offset /= radices[i];
        }
        check_cuda_error(cudaMemcpy(radix_offset.values, offset_radix.data(), this->length * sizeof(int), cudaMemcpyHostToDevice));

        dim3 grid((items_this_iter + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK);

        auto t0 = Clock::now();
        check_cuda_error(cudaEventRecord(ev_start));
        launch_uncompress_kernel(
            grid, block, smem,
            base_radices_buf.values, radix_offset.values, magic_buf.values, perm_list.data(),
            output.values, input_output.values, output_count,
            (unsigned int)items_this_iter,
            (int)this->new_length, (int)this->length, threshold,
            (unsigned int)items_per_iter
        );
        check_cuda_error(cudaEventRecord(ev_stop));
        check_cuda_error(cudaDeviceSynchronize());
        kernel_ms += std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
        float ev_ms = 0.0f;
        check_cuda_error(cudaEventElapsedTime(&ev_ms, ev_start, ev_stop));
        gpu_kernel_ms += ev_ms;

        unsigned int count;
        check_cuda_error(cudaMemcpy(&count, output_count, sizeof(unsigned int), cudaMemcpyDeviceToHost));
        total_count += count;

        if (count > 0) {
            std::vector<int>    h_input(count * this->new_length);
            std::vector<float>  h_output_f(count * this->new_length);
            std::vector<double> h_output(count * this->new_length);

            check_cuda_error(cudaMemcpy(h_input.data(),    input_output.values, count * this->new_length * sizeof(int),   cudaMemcpyDeviceToHost));
            check_cuda_error(cudaMemcpy(h_output_f.data(), output.values,        count * this->new_length * sizeof(float), cudaMemcpyDeviceToHost));

            std::transform(h_output_f.begin(), h_output_f.end(), h_output.begin(), [](float v) { return (double)v; });

            auto tw0 = Clock::now();
            for (unsigned int i = 0; i < count; i++) {
                writer(
                    std::span<int>   (h_input.data()  + i * this->new_length, this->new_length),
                    std::span<double>(h_output.data() + i * this->new_length, this->new_length)
                );
            }
            writer_ms += std::chrono::duration<double, std::milli>(Clock::now() - tw0).count();
        }
    }

    check_cuda_error(cudaEventDestroy(ev_start));
    check_cuda_error(cudaEventDestroy(ev_stop));
    check_cuda_error(cudaFree(output_count));

    double total_ms = std::chrono::duration<double, std::milli>(Clock::now() - run_start).count();
    double sync_overhead_ms = kernel_ms - gpu_kernel_ms;
    printf("Total passing sequences: %s\n",  total_count.str().c_str());
    printf("Total wall time:         %.1f ms\n", total_ms);
    printf("Time in kernel+sync:     %.1f ms  (%.1f%%)\n", kernel_ms,        100.0 * kernel_ms        / total_ms);
    printf("  GPU kernel time:       %.1f ms  (%.1f%%)\n", gpu_kernel_ms,    100.0 * gpu_kernel_ms    / total_ms);
    printf("  Sync overhead (WSL2):  %.1f ms  (%.1f%%)\n", sync_overhead_ms, 100.0 * sync_overhead_ms / total_ms);
    printf("Time in writer:          %.1f ms  (%.1f%%)\n", writer_ms,        100.0 * writer_ms        / total_ms);

}
