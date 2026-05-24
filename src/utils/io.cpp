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
#include <format>
#include <charconv>

#include "io.h"

static char* write_int(char* p, int v) {
    auto [end, _] = std::to_chars(p, p + 12, v);
    return end;
}

void write_seq_psd(std::span<const int> seq, std::span<const double> psd, std::ofstream& out) {
    // max bytes: 3 + (N-1)*12 + 1 + N*13 + 1; 8192 covers N up to ~300
    char buf[8192];
    char* p = buf;
    *p++ = 'P'; *p++ = 'S'; *p++ = 'D';
    for(std::size_t i = 1; i < psd.size(); i++)
        p = write_int(p, (int)rint(psd[i]));
    *p++ = ' ';
    for(int v : seq) {
        p = write_int(p, v);
        *p++ = ' ';
    }
    *p++ = '\n';
    out.write(buf, p - buf);
}

void write_seq_psd_invert(std::span<const int> seq, std::span<const double> psd, std::ofstream& out, const int BOUND) {
    char buf[8192];
    char* p = buf;
    *p++ = 'P'; *p++ = 'S'; *p++ = 'D';
    for(std::size_t i = 1; i < psd.size(); i++)
        p = write_int(p, BOUND - (int)rint(psd[i]));
    *p++ = ' ';
    for(int v : seq) {
        p = write_int(p, v);
        *p++ = ' ';
    }
    *p++ = '\n';
    out.write(buf, p - buf);
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