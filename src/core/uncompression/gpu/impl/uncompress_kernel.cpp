#include <cstdio>
#include <vector>
#include <cuda_runtime.h>
#include <boost/multiprecision/cpp_int.hpp>

#include "uncompress_kernel.h"
#include "flat_perm_list.h"
#include "jit_headers.h"
#include "memorypool.h"

const std::string program = R"(
#include "view_types.h"
#include "cufftdx.hpp"

using namespace cufftdx;

using FFT_base = decltype(
    Size<FFT_SIZE>() + Type<fft_type::r2c>() +
    Precision<__half>() + SM<SM_ARCH>() + Block()
);

using FFT = decltype(FFT_base() + FFTsPerBlock<FFT_base::suggested_ffts_per_block>());

__device__ const unsigned int fft_block_dim_x    = FFT::block_dim.x;
__device__ const unsigned int fft_shared_mem     = (unsigned int)FFT::shared_memory_size;
__device__ const unsigned int fft_suggested_ffts = FFT::suggested_ffts_per_block;

__global__ void uncompress_kernel(FlatPermListData data) {
    FlatPermList::View permutations(data);
}
)";

using BigInt = boost::multiprecision::cpp_int;

UncompressKernel::UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant)
    : order(order), compress(compress), new_compress(new_compress), paf_constant(paf_constant), permutations(permutations) {

    cudaFree(0);

    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);
    int sm_arch = prop.major * 100 + prop.minor * 10;
    int seq_length = order / new_compress;

    static jitify2::ProgramCache<> cache(100, *jitify2::Program("uncompress_program", program,
        {{"flat_perm_list.h", flat_perm_list_jit},
         {"view_types.h", view_types_jit}})
        ->preprocess({
            "-I" + jitify2::get_cuda_include_dir(),
            "-I" + jitify2::get_cuda_include_dir() + "/cccl",
            "-I" + jit_third_party_dir,
            "-DFFT_SIZE=" + std::to_string(seq_length),
            "-DSM_ARCH=" + std::to_string(sm_arch)
        }));

    this->kernel = cache.get_kernel("uncompress_kernel");

    unsigned int block_dim_x, shared_mem, suggested_ffts;
    this->kernel->program().get_global_value("fft_block_dim_x",    &block_dim_x);
    this->kernel->program().get_global_value("fft_shared_mem",     &shared_mem);
    this->kernel->program().get_global_value("fft_suggested_ffts", &suggested_ffts);
    cudaDeviceSynchronize();

    this->launch_params = {block_dim_x, shared_mem, suggested_ffts};
}

// TODO: Write destructor
UncompressKernel::~UncompressKernel() {}

void UncompressKernel::run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer) {
    std::vector<int> radices;
    for (auto list : this->permutations) {
        radices.push_back(list.size());
    }

    BigInt search_count = 1;
    for (int num : radices) {
        search_count *= num;
    }

    FlatPermList perm_list(this->permutations);

    size_t free_mem, total_mem;
    cudaMemGetInfo(&free_mem, &total_mem);

    constexpr size_t max_per_iter = 1000000;
    size_t items_per_iter = static_cast<size_t>(
        std::min(
            search_count,
            static_cast<BigInt>(std::min(
                MemoryPool<int>::items_storable(seq.size(), free_mem),
                max_per_iter
            ))
        )
    );

    printf("Iterating with %lu sequences per iteration\n", items_per_iter);
    printf("  block_dim_x:    %u\n", launch_params.block_dim_x);
    printf("  shared_mem:     %u bytes\n", launch_params.shared_mem);
    printf("  ffts_per_block: %u\n", launch_params.ffts_per_block);

    MemoryPool<int> seq_pool(items_per_iter, seq.size());

    for (BigInt offset = 0; offset < search_count; offset += items_per_iter) {
        BigInt remaining = search_count - offset;
        size_t items_this_iter = static_cast<size_t>(std::min(remaining, static_cast<BigInt>(items_per_iter)));

        dim3 grid((items_this_iter + launch_params.ffts_per_block - 1) / launch_params.ffts_per_block);
        dim3 block(launch_params.block_dim_x);
        printf("  grid: %u, block: %u, ffts_per_block: %u\n", grid.x, block.x, launch_params.ffts_per_block);
        
        this->kernel->configure(grid, block, launch_params.shared_mem)->launch(perm_list.data());
    }
}
