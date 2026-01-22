#pragma once

#include"fftw3.h"
#include"golay.h"
#include<array>
#include<set>
#include<vector>

class Fourier {
private:
    fftw_complex* input;
    fftw_complex* output;
    fftw_plan plan;
    std::vector<double> psd;
    std::size_t len;

public:
    Fourier(std::size_t length);
    ~Fourier();
    const std::vector<double>& calculate_psd(const std::vector<int>& seq);
    bool psd_filter(const std::vector<double>& psd, const int ORDER, const int PAF_CONSTANT);
};


fftw_complex * dft(std::vector<int> seq, fftw_complex * in, fftw_complex * out, fftw_plan p);
int dftfilter(fftw_complex * seqdft, int len, int ORDER, int PAF_CONSTANT);
int dftfilterpair(fftw_complex *dftA, fftw_complex *dftB, int len);
std::set<int> spectrumthree(int len, int ORDER);
