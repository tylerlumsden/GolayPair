#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <chrono>

bool read_pair(std::ifstream& in, std::vector<int>& a, std::vector<int>& b);
void write_seq_psd(const std::vector<int>& seq, const std::vector<double>& psd, std::ofstream& out);
void write_seq_psd_invert(const std::vector<int>& seq, const std::vector<double>& psd, std::ofstream& out, const int BOUND);

inline void print_seq(std::vector<int> seq, std::ofstream& out) {
    for(int val : seq) {
        out << val << " ";
    }
    out << "\n";
}

class Progress {

    using cpp_int = boost::multiprecision::cpp_int;
    using cpp_dec_float_50 = boost::multiprecision::cpp_dec_float_50;
    using milliseconds = std::chrono::milliseconds;
    using clock = std::chrono::steady_clock;

public:

    Progress(cpp_int end_count, milliseconds interval = milliseconds(10)) 
        : end_count(end_count), interval(interval) {}

    void update(boost::multiprecision::cpp_int curr_count) {

        clock::time_point now = clock::now();
        if(curr_count != end_count && next_print > now) {
            return;
        }
        next_print = now + interval;

        cpp_dec_float_50 percent = (cpp_dec_float_50(curr_count) / cpp_dec_float_50(end_count)) * 100;

        std::cerr << '\r'
                    << "Progress: " << std::setw(6) << std::fixed << std::setprecision(3)
                    << percent << '%'
                    << "\x1b[K"
                    << std::flush;

        if(curr_count == end_count) {
            std::cerr << "\n";
        }
    }

    ~Progress() {
        std::cerr << '\n'; // leave terminal in a clean state
    }

private:
    const cpp_int end_count;
    const milliseconds interval;
    clock::time_point next_print = clock::now();
};
