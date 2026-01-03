#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "generate_hybrid.h"

struct Options {
    int order;
    int compress;
    std::string output_dir;
};

void print_usage(const char* func) {
    std::cerr << "Usage: " << func << " [options] <order>\n"
              << "Options:\n"
              << "  -c, --compress (int)    Set compression level (default: 1)\n"
              << "  -d, --dir (string)      Set output directory path (default: results)\n"
              << "  order (int)             Required order value (integer)\n";
}

Options parse_args(int argc, char* argv[]) {
    Options opts;

    // Assign default values for Options
    opts.compress = 1;
    opts.output_dir = "results";

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
            opts.output_dir = args.at(i + 1);
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

    // Application logic goes here
    std::cout << "Generating Candidates\n";
    generate_hybrid(opts.order, opts.compress);
    std::cout << "Generated Candidates\n";

    return 0;
}