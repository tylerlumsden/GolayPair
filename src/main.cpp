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
#include "coprimes.h"

struct Options {
    int order;
    std::vector<int> compress = {1};
    std::string temp_dir = "results";
};

int main(int argc, char* argv[]) {
    Options opts;

    CLI::App app{"Complementary Pairs Pipeline"};

    app.add_option("order", opts.order, "Order");
    app.add_option("-c,--compress", opts.compress, "Set compression level (default=1)");
    app.add_option("-d,--dir", opts.temp_dir, "Set directory for populating temporary files (default=result)");
    CLI11_PARSE(app, argc, argv);

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

    // Candidate generation step
    {
        std::ofstream file_a(FILE_A);
        std::ofstream file_b(FILE_B);
        generate_hybrid(opts.order, opts.compress[0], file_a, file_b); // OUT: a, OUT: b
    }

    // Sort results of the candidate generation step
    GNU_sort(FILE_A, FILE_A_SORTED);
    GNU_sort(FILE_B, FILE_B_SORTED);

    // Matching step
    {
        std::ofstream pairs(FILE_PAIRS);
        std::ifstream file_a_sorted(FILE_A_SORTED);
        std::ifstream file_b_sorted(FILE_B_SORTED);
        match_pairs(opts.order / opts.compress[0], file_a_sorted, file_b_sorted, pairs); // IN: a, IN: b, OUT: pairs
    }

    // Uncompression steps
    if(opts.compress[0] > 1) {
        for(size_t i = 0; i < opts.compress.size() - 1; i++) {
            std::cout << "Uncompressing to new compression ratio " << opts.compress[i + 1] << "\n";
            std::ifstream in_pairs(FILE_PAIRS);
            std::ofstream out_pairs(FILE_PAIRS_UNCOMPRESSED);
            uncompression_pipeline(opts.order, opts.compress[i], opts.compress[i + 1], in_pairs, out_pairs, WORK_DIR); // IN: pairs, OUT: pairs

            std::filesystem::rename(FILE_PAIRS_UNCOMPRESSED, FILE_PAIRS);
        }
    } 

    std::cout << "Filtering pairs of compression size " << opts.compress.back() << "\n";
    cache_filter(opts.order, opts.compress.back(), FILE_PAIRS, FILE_PAIRS + ".unique");

    return 0;
}