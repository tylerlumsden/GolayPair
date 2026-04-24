#include<cstdio>
#include <vector>
#include <cuda_runtime.h>

#include "uncompress_kernel.h"
#include "flat_perm_list.h"

const std::string program =
"__global__\n"
"void uncompress_kernel() {\n"
"   printf(\"Hello World!\\n\");\n"
"}\n";

UncompressKernel::UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant)
    : order(order), compress(compress), new_compress(new_compress), paf_constant(paf_constant), permutations(permutations) {

    cudaFree(0);
    static jitify2::ProgramCache<> cache(100, *jitify2::Program("uncompress_program", program)->preprocess());

    this->kernel = cache.get_kernel(jitify2::reflection::Template("uncompress_kernel").instantiate());
}

UncompressKernel::~UncompressKernel() {}

void UncompressKernel::run(const std::vector<int>& seq, std::function<void(std::span<int>, std::span<double>)> writer) {
    FlatPermList perm_list(this->permutations);

    this->kernel->configure(1, 1)->launch();
}
