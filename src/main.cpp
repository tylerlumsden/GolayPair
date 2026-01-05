#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <format>
#include <fstream>

#include "constants.h"
#include "generate_hybrid.h"
#include "sort.h"
#include "match_pairs.h"
#include "uncompression.h"
#include "filter.h"
#include "CLI11.hpp"

struct Options {
    int order;
    int compress;
    std::string temp_dir;
};

void print_usage(const char* func) {
    std::cerr << "Usage: " << func << " [options] <order>\n"
              << "Options:\n"
              << "  -c, --compress (int)    Set compression level (default: 1)\n"
              << "  -d, --dir (string)      Set temp directory path (default: results)\n"
              << "  order (int)             Required order value (integer)\n";
}

Options parse_args(int argc, char* argv[]) {
    Options opts;

    // Assign default values for Options
    opts.compress = 1;
    opts.temp_dir = "results";

    std::vector<std::string> args;
    for(int i = 0; i < argc; i++) {
        args.push_back(argv[i]);
    }

    std::vector<std::string> positional;

    // Override default values if input
    int i = 1;
    for(; i < argc; i++) {
        const std::string arg = args.at(i);
        if(arg == "-c"  || arg == "--compress") {
            opts.compress = std::stoi(args.at(i + 1));
            i++;
        }
        else if(arg == "-d" || arg == "--dir") {
            opts.temp_dir = args.at(i + 1);
            i++;
        } else {
            positional.push_back(arg);
        }
    }

    // Assign positional values
    if(positional.size() != 1) {
        throw std::invalid_argument("Expected exactly 1 positional argument, got " + std::to_string(positional.size()));
    }
    opts.order = std::stoi(positional.at(0));

    if(opts.compress < 1 || opts.order % opts.compress != 0) {
        throw std::invalid_argument("compress must be a positive divisor of order.");
    }
    if(opts.order < 1) {
        throw std::invalid_argument("order should be positive.");
    }

    return opts;
}

int main(int argc, char* argv[]) {
    Options opts;
    try {
        opts = parse_args(argc, argv);
    } catch(const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        print_usage(argv[0]);
        return 1;
    }

    const std::string WORK_DIR = std::format("{}/order-{}", opts.temp_dir, opts.order);
    const std::string FILE_A = std::format("{}/{}-filtered-a", WORK_DIR, opts.order);
    const std::string FILE_B = std::format("{}/{}-filtered-b", WORK_DIR, opts.order);
    const std::string FILE_A_SORTED = FILE_A + ".sorted";
    const std::string FILE_B_SORTED = FILE_B + ".sorted";
    const std::string FILE_PAIRS = std::format("{}/{}-pairs", WORK_DIR, opts.order);
    const std::string FILE_PAIRS_UNCOMPRESSED = FILE_PAIRS + ".uncompress";

    // Make sure temporary directories are created beforehand
    std::error_code ec;
    std::filesystem::create_directories(WORK_DIR, ec);
    if(ec) {
        std::cerr << "Failed to create temp directories: " << ec.message() << "\n";
    }

    // Application logic goes here
    {
        std::ofstream file_a(FILE_A);
        std::ofstream file_b(FILE_B);
        generate_hybrid(opts.order, opts.compress, file_a, file_b); // OUT: a, OUT: b
    }

    GNU_sort(FILE_A, FILE_A_SORTED);
    GNU_sort(FILE_B, FILE_B_SORTED);

    {
        std::ofstream pairs(FILE_PAIRS);
        std::ifstream file_a_sorted(FILE_A_SORTED);
        std::ifstream file_b_sorted(FILE_B_SORTED);
        match_pairs(opts.order / opts.compress, file_a_sorted, file_b_sorted, pairs); // IN: a, IN: b, OUT: pairs
    }
    
    if(opts.compress > 1) {
        std::cout << "Uncompressing\n";
        {
            std::ifstream in_pairs(FILE_PAIRS);
            std::ofstream out_pairs(FILE_PAIRS_UNCOMPRESSED);
            uncompression_pipeline(opts.order, opts.compress, 1, in_pairs, out_pairs, WORK_DIR); // IN: pairs, OUT: pairs
        }

        cache_filter(opts.order, 1, FILE_PAIRS_UNCOMPRESSED, FILE_PAIRS + ".unique");
    } else {
        cache_filter(opts.order, 1, FILE_PAIRS, FILE_PAIRS + ".unique");
    }

    return 0;
}