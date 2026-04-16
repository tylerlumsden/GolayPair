#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <span>
#include <sstream>

#include "io.h"

void write_seq_psd(std::span<const int> seq, std::span<const double> psd, std::ofstream& out) {
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

void write_seq_psd_invert(std::span<const int> seq, std::span<const double> psd, std::ofstream& out, const int BOUND) {
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

namespace IO {
PairReader& PairReader::operator>>(PairType& pair) {
    SequenceType a;
    SequenceType b;

    if(std::string line; std::getline(input, line)) {
        SequenceType seq;
        ValueType val;
        std::istringstream iss(line);

        while(iss >> val) {
            seq.push_back(val);
        }

        if(seq.size() != length * 2) {
            throw std::runtime_error(std::format(
                "PairReader: input line {}: length is {}. Expected {}", line_number, seq.size(), this->length * 2
            ));
        }

        SequenceType seqa;
        for(size_t i = 0; i < this->length; ++i) {
            a.push_back(seq[i]);
        }

        SequenceType seqb;
        for(size_t i = 0; i < this->length; ++i) {
            b.push_back(seq[i + this->length]);
        }

        ++line_number;  
    } 
    pair.first = a;
    pair.second = b;
    return *this;
}

PairWriter& PairWriter::operator<<(const PairType& pair) {
    SequenceType a = pair.first;
    SequenceType b = pair.second;
    
    if(a.size() != this->length || b.size() != this->length) {
        throw std::runtime_error(std::format( 
            "PairWriter: input length is {} and {}. Expected {}", a.size(), b.size(), this->length 
        ));
    }

    for(auto val : a) {
        this->output << val << " ";
    }
    this->output << " ";
    for(auto val : b) { 
        this->output << val << " ";
    }
    this->output << "\n";

    return *this;
}
}

