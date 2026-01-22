#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <chrono>

void write_seq_psd(const std::vector<int>& seq, const std::vector<double>& psd, std::ofstream& out) {
    out << "PSD";
    for(std::size_t i = 1; i < psd.size(); i++) {
        out << (int)rint(psd[i]);
    }
    out << " ";
    for(std::size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
    out << "\n";
}

void write_seq_psd_invert(const std::vector<int>& seq, const std::vector<double>& psd, std::ofstream& out, const int BOUND) {
    out << "PSD";
    for(std::size_t i = 1; i < psd.size(); i++) {
        out << BOUND - (int)rint(psd[i]);
    }
    out << " ";
    for(std::size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
    out << "\n";
}
