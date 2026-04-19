#include<cstdio>

#include "uncompress_kernel.h"
#include "uncompress_kernel_impl.h"

const std::string program =
"__global__\n"
"void uncompress_kernel() {\n"
"   printf(\"Hello World!\\n\");\n"
"}\n";

UncompressKernel::UncompressKernel(const PermList& permutations, int order, int compress, int new_compress, int paf_constant) {
    this->impl = std::make_unique<Impl>(UncompressKernel::Impl(order, compress, new_compress, paf_constant));

    cudaFree(0);
    static jitify2::ProgramCache<> cache(100, *jitify2::Program("uncompress_program", program)->preprocess());

    this->impl->kernel = cache.get_kernel(jitify2::reflection::Template("uncompress_kernel").instantiate());
}

UncompressKernel::~UncompressKernel() {}

void UncompressKernel::Impl::launch_kernel() {
    this->kernel->configure(1, 1)->launch();
}