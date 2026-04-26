#include<cstdio>
#include <vector>
#include <cuda_runtime.h>

#include "uncompress_kernel.h"
#include "flat_perm_list.h"
#include "jit_headers.h"

const std::string program = R"(
#include "view_types.h"

__global__
void uncompress_kernel(FlatPermListData data) {
    FlatPermList::View permutations(data);
    printf("Hello World!\n");
}
)";

UncompressKernel::UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant)
    : order(order), compress(compress), new_compress(new_compress), paf_constant(paf_constant), permutations(permutations) {

    cudaFree(0);
    static jitify2::ProgramCache<> cache(100, *jitify2::Program("uncompress_program", program,
        {{"flat_perm_list.h", flat_perm_list_jit},
         {"view_types.h", view_types_jit}})
        ->preprocess({
            "-I" + jitify2::get_cuda_include_dir(),
            "-I" + jitify2::get_cuda_include_dir() + "/cccl"
        }));

    this->kernel = cache.get_kernel(jitify2::reflection::Template("uncompress_kernel").instantiate());
}

UncompressKernel::~UncompressKernel() {}

void UncompressKernel::run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer) {
    FlatPermList perm_list(this->permutations);

    this->kernel->configure(1, 1)->launch(perm_list.data());
}
