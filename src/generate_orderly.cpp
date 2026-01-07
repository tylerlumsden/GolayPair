#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"orderly_equivalence.h"
#include"fftw3.h"
#include"array.h"
#include"decomps.h"
#include"fourier.h"
#include<tgmath.h>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<format>

double norm_squared(fftw_complex dft) {
    return dft[0] * dft[0] + dft[1] * dft[1];
}

int rowsum(vector<int> seq) {
    int sum = 0;
    for(unsigned int i = 0; i < seq.size(); i++) {
        sum = sum + seq[i];
    }
    return sum;
}

int sum_constant(int order, int paf) {
    return order * 2 + (order - 1) * paf;
}

bool nextBranch(vector<int>& seq, unsigned int len, set<int> alphabet);

void write_seq_psd(std::vector<int> seq, std::vector<double> psd, std::ofstream& out) {
    for(std::size_t i = 1; i < psd.size(); i++) {
        out << (int)rint(psd[i]);
    }
    out << " ";
    for(std::size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
    out << "\n";
}

void write_seq_psd_invert(std::vector<int> seq, std::vector<double> psd, std::ofstream& out, const int BOUND) {
    for(std::size_t i = 1; i < psd.size(); i++) {
        out << BOUND - (int)rint(psd[i]);
    }
    out << " ";
    for(std::size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
    out << "\n";
}

int generate_orderly(const int ORDER, const int COMPRESS, const int PAF_CONSTANT, std::ofstream& out_a, std::ofstream& out_b) {

    const std::vector<std::pair<int, int>> decompslist = getdecomps(sum_constant(ORDER, PAF_CONSTANT));

    const size_t LEN = ORDER / COMPRESS;

    Fourier FourierManager = Fourier(LEN);

    set<int> alphabet = {-1, 1};
    vector<int> seq(LEN, -1);

    do {
        if(seq.size() == LEN) {
            for(std::pair<int, int> decomp : decompslist) {
                if(decomp.first == rowsum(seq)) {
                    // check PSD
                    std::vector<double> psd = FourierManager.calculate_psd(seq);
                    if(FourierManager.psd_filter(psd, ORDER, PAF_CONSTANT)) {
                        write_seq_psd(seq, psd, out_a);
                    }
                }
                if(decomp.second == rowsum(seq)) {
                    // check PSD
                    std::vector<double> psd = FourierManager.calculate_psd(seq);
                    if(FourierManager.psd_filter(psd, ORDER, PAF_CONSTANT)) {
                        write_seq_psd_invert(seq, psd, out_b, ORDER * 2 - PAF_CONSTANT); // need to invert psd here
                    }
                }
            }
        }
    } while(nextBranch(seq, LEN, alphabet));

    return 0;
}

bool nextBranch(vector<int>& seq, unsigned int len, set<int> alphabet) {

    int max = *alphabet.rbegin();
    int min = *alphabet.begin();

        if(seq.size() == len) {
            while(seq.size() != 0 && seq[seq.size() - 1] == max) {
                seq.pop_back();
            }
            if(seq.size() == 0) {
                return false;
            }
            int next = seq.back() + 2;
            seq.pop_back();
            seq.push_back(next);
        } else {
            seq.push_back(min);
        }
    
    return true;
}