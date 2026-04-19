#include "gpu_fourier.h"
#include "sequence_pool.h"
#include "fourier_pool.h"
#include <cufft.h>
#include <format>
#include <stdexcept>
#include <cuComplex.h>

struct GPUFourier::Impl {
    cufftHandle plan;
    float*     input_ptr;
    cuComplex* output_ptr;

    Impl(SequencePool& seq, FourierPool& fourier) {
        input_ptr  = seq.device_data();
        output_ptr = reinterpret_cast<cuComplex*>(fourier.device_data());

        int n[]   = { (int)seq.length() };
        int batch = (int)seq.batch_size();
        auto result = cufftPlanMany(
            &plan,
            1, n,
            n, batch, 1,
            n, batch, 1,
            CUFFT_R2C,
            batch
        );
        if(result != CUFFT_SUCCESS)
            throw std::runtime_error(std::format("cuFFT plan failed: {}\n", static_cast<int>(result)));
    }

    ~Impl() { cufftDestroy(plan); }

    void launch_batch() {
        auto result = cufftExecR2C(
            plan,
            reinterpret_cast<cufftReal*>(input_ptr),
            reinterpret_cast<cufftComplex*>(output_ptr)
        );
        if(result != CUFFT_SUCCESS)
            throw std::runtime_error(std::format("cuFFT launch failed: {}\n", static_cast<int>(result)));
    }
};

GPUFourier::GPUFourier(SequencePool& input, FourierPool& output)
    : impl(std::make_unique<Impl>(input, output)) {}

GPUFourier::~GPUFourier() = default;

void GPUFourier::launch_batch() { impl->launch_batch(); }
