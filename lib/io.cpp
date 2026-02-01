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

bool read_pair(std::ifstream& in, std::vector<int>& a, std::vector<int>& b) {
    std::string line;
    if(std::getline(in, line)) {
        std::vector<int> seq;
        std::istringstream iss(line);
        std::string val;

        while(iss >> val) {
            seq.push_back(std::stoi(val));
        }

        std::vector<int> seqa;
        for(size_t i = 0; i < seq.size() / 2; ++i) {
            a.push_back(seq[i]);
        }

        std::vector<int> seqb;
        for(size_t i = seq.size() / 2; i < seq.size(); ++i) {
            b.push_back(seq[i]);
        }
        
        return true;
    } else {
        return false;
    }
}
