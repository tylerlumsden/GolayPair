#pragma once

#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

inline void write_seq_psd(std::vector<int> seq, std::vector<double> psd, std::ofstream& out) {
    for(std::size_t i = 1; i < psd.size(); i++) {
        out << (int)rint(psd[i]);
    }
    out << " ";
    for(std::size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
    out << "\n";
}

inline void write_seq_psd_invert(std::vector<int> seq, std::vector<double> psd, std::ofstream& out, const int BOUND) {
    for(std::size_t i = 1; i < psd.size(); i++) {
        out << BOUND - (int)rint(psd[i]);
    }
    out << " ";
    for(std::size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
    out << "\n";
}

inline void print_seq(std::vector<int> seq, std::ofstream& out) {
    for(int val : seq) {
        out << val << " ";
    }
    out << "\n";
}
