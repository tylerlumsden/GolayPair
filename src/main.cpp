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

    // Make sure temporary directories are created beforehand
    std::string temp_path = std::format("{}/generate/order-{}", opts.temp_dir, opts.order);
    std::error_code ec;
    std::filesystem::create_directories(temp_path, ec);
    if(ec) {
        std::cerr << "Failed to create temp directories: " << ec.message() << "\n";
    }

    // Application logic goes here

    std::string filepath_a = std::format("{}/generate/order-{}/{}-filtered-a_1", opts.temp_dir, opts.order, opts.order);
    std::string filepath_b = std::format("{}/generate/order-{}/{}-filtered-b_1", opts.temp_dir, opts.order, opts.order);
    generate_hybrid(opts.order, opts.compress, filepath_a, filepath_b); // OUT: a, OUT: b

    GNU_sort(filepath_a, filepath_a + ".sorted");
    GNU_sort(filepath_b, filepath_b + ".sorted");

    std::string pairs_path = std::format("{}/generate/order-{}/{}-pairs-found", opts.temp_dir, opts.order, opts.order);
    match_pairs(opts.order, opts.compress, filepath_a + ".sorted", filepath_b + ".sorted", pairs_path); // IN: a, IN: b, OUT: pairs
    
    if(opts.compress > 1) {
        std::cout << "Uncompressing\n";
        uncompression_pipeline(opts.order, opts.compress, 1, pairs_path, pairs_path + ".uncompress", opts.temp_dir); // IN: pairs, OUT: pairs
    }

    cache_filter(opts.order, 1, pairs_path, pairs_path + ".unique"); // IN: pairs, OUT: pairs

    return 0;
}