#include<cstdio>
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

__global__
void uncompress_kernel(FlatPermListData data) {
    FlatPermList::View permutations(data);
    printf("Hello World!\n");
}
)";

using BigInt = boost::multiprecision::cpp_int;

UncompressKernel::UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant)
    : order(order), compress(compress), new_compress(new_compress), paf_constant(paf_constant), permutations(permutations) {

    cudaFree(0);
    static jitify2::ProgramCache<> cache(100, *jitify2::Program("uncompress_program", program,
        {{"flat_perm_list.h", flat_perm_list_jit},
         {"view_types.h", view_types_jit}})
        ->preprocess({
            "-I" + jitify2::get_cuda_include_dir(),
            "-I" + jitify2::get_cuda_include_dir() + "/cccl",
            "-I" + jit_third_party_dir
        }));
    
    this->kernel = cache.get_kernel(jitify2::reflection::Template("uncompress_kernel").instantiate());
}
// TODO: Write destructor
UncompressKernel::~UncompressKernel() {}

void UncompressKernel::run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer) {
    std::vector<int> radices;
    for(auto list : this->permutations) {
        radices.push_back(list.size());
    }

    BigInt search_count = 1;
    for(int num : radices) {
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
    MemoryPool<int> seq_pool(items_per_iter, seq.size());

    this->kernel->configure(1, 1)->launch(perm_list.data());
}
