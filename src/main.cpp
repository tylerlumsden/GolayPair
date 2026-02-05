#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>

#include "constants.h"
#include "generate_hybrid.h"
#include "sort.h"
#include "match_pairs.h"
#include "uncompression.h"
#include "filter.h"
#include "CLI11.hpp"
#include "generate_orderly.h"
#include "io.h"

struct Options {
    int order;
    int paf_constant = 0;
    int job_id = 0;
    int job_count = 1;
    std::vector<int> compress = {1};
    std::string temp_dir = "results";
};

struct Paths {
    const std::string WORK_DIR;
    const std::string FILE_A;
    const std::string FILE_B;
    const std::string FILE_A_SORTED;
    const std::string FILE_B_SORTED;
    const std::string FILE_A_UNCOMPRESSED;
    const std::string FILE_B_UNCOMPRESSED;
    const std::string FILE_A_UNCOMPRESSED_SORTED;
    const std::string FILE_B_UNCOMPRESSED_SORTED;
    const std::vector<std::string> FILE_A_LIST;
    const std::vector<std::string> FILE_B_LIST;
    const std::vector<std::string> FILE_PAIRS_LIST;
    const std::string FILE_PAIRS_FILTERED;
    
    Paths(const Options& opts)
        : WORK_DIR(std::format("{}/order-{}", opts.temp_dir, opts.order))
        , FILE_A(std::format("{}/{}-filtered-a", WORK_DIR, opts.order))
        , FILE_B(std::format("{}/{}-filtered-b", WORK_DIR, opts.order))
        , FILE_A_SORTED(FILE_A + ".sorted")
        , FILE_B_SORTED(FILE_B + ".sorted")
        , FILE_A_UNCOMPRESSED(std::format("{}/{}-uncompressed-a", WORK_DIR, opts.order))
        , FILE_B_UNCOMPRESSED(std::format("{}/{}-uncompressed-b", WORK_DIR, opts.order))
        , FILE_A_UNCOMPRESSED_SORTED(FILE_A_UNCOMPRESSED + ".sorted")
        , FILE_B_UNCOMPRESSED_SORTED(FILE_B_UNCOMPRESSED + ".sorted")
        , FILE_A_LIST ([&] {
            std::vector<std::string> list;
            for(int i = 0; i < opts.job_count; ++i) {
                list.push_back(FILE_A + "-" + std::to_string(i));
            }
            return list;
        }())
        , FILE_B_LIST ([&] {
            std::vector<std::string> list;
            for(int i = 0; i < opts.job_count; ++i) {
                list.push_back(FILE_B + "-" + std::to_string(i));
            }
            return list;
        }())
        , FILE_PAIRS_LIST([&] {
            std::vector<std::string> list;
            for(int compress : opts.compress) {
                list.push_back(std::format("{}/{}-pairs-{}", WORK_DIR, opts.order, compress));
            }
            return list;
        }())
        , FILE_PAIRS_FILTERED(std::format("{}/{}-pairs-unique", WORK_DIR, opts.order))
    {}
};

// Individual pipeline stages
int stage_generate(const Options& opts, const Paths& paths) {
    std::cout << "Generating Candidates\n";

    std::ofstream file_a(paths.FILE_A_LIST[opts.job_id]);
    std::ofstream file_b(paths.FILE_B_LIST[opts.job_id]);
    if(generate_hybrid(opts.order, opts.compress[0], opts.paf_constant, file_a, file_b, opts.job_id, opts.job_count) > 0) return 1;

    return 0;
}

int stage_sort(const Options& opts, const Paths& paths) {
    std::cout << "Sorting Candidates\n";

    if(GNU_sort(paths.FILE_A_LIST, paths.FILE_A_SORTED) > 0) return 1;
    if(GNU_sort(paths.FILE_B_LIST, paths.FILE_B_SORTED) > 0) return 1;

    return 0;
}

int stage_match(const Options& opts, const Paths& paths) {
    std::cout << "Matching Candidates\n";
    std::ofstream pairs(paths.FILE_PAIRS_LIST.front());
    std::ifstream file_a_sorted(paths.FILE_A_SORTED);
    std::ifstream file_b_sorted(paths.FILE_B_SORTED);
    return match_pairs(opts.order, opts.compress[0], opts.paf_constant, file_a_sorted, file_b_sorted, pairs);
}

int uncompress_line(const Options& opts, const Paths& paths, int linenumber) {
    if(opts.compress[0] <= 1 || opts.compress.size() < 2) return 0;

    std::cout << "Uncompressing line " << linenumber << "\n";


    std::cout << "Uncompressing to new compression ratio " << opts.compress[1] << "\n";
    std::ifstream in_pairs(paths.FILE_PAIRS_LIST[0]);

    std::vector<int> a, b;
    for(long long linecount = 0; read_pair(in_pairs, a, b); ++linecount) {
        if(static_cast<int>(a.size()) != opts.order / opts.compress[0] || static_cast<int>(b.size()) != opts.order / opts.compress[0]) {
            std::cerr << "Compressed pair has invalid length: " << a.size() << " " << b.size() << "\n";
            return 1;
        }

        if(linecount == linenumber) {
            std::ofstream outa(paths.FILE_A_LIST[opts.job_id]);
            std::ofstream outb(paths.FILE_B_LIST[opts.job_id]);

            uncompress_recursive(a, opts.compress[0], opts.compress[1], opts.paf_constant, opts.job_id, opts.job_count, outa, 0);
            uncompress_recursive(b, opts.compress[0], opts.compress[1], opts.paf_constant, opts.job_id, opts.job_count, outb, 1);

            return 0;
        }
        a.clear();
        b.clear();
    }

    return 0;
}

int stage_uncompress(const Options& opts, const Paths& paths) {
    if(opts.compress[0] <= 1) return 0;

    std::cout << "Running Uncompression Pipeline\n";
    for(size_t i = 0; i < opts.compress.size() - 1; i++) {
        std::cout << "Uncompressing to new compression ratio " << opts.compress[i + 1] << "\n";

        std::ifstream in_pairs(paths.FILE_PAIRS_LIST[i]);
        std::ofstream out_pairs(paths.FILE_PAIRS_LIST[i + 1]);

        std::vector<int> a, b;
        for(long long linecount = 0; read_pair(in_pairs, a, b); ++linecount) {
            if(static_cast<int>(a.size()) != opts.order / opts.compress[i] || static_cast<int>(b.size()) != opts.order / opts.compress[i]) {
                std::cerr << "Compressed pair has invalid length: " << a.size() << " " << b.size() << "\n";
                return 1;
            }

            // TODO: Only compute the line if it is the work of the current job

            std::cout << "Uncompressing line: " << linecount << "\n";

            std::ofstream outa(paths.FILE_A_UNCOMPRESSED);
            std::ofstream outb(paths.FILE_B_UNCOMPRESSED);

            uncompress_recursive(a, opts.compress[i], opts.compress[i + 1], opts.paf_constant, 0, 1, outa, 0);
            uncompress_recursive(b, opts.compress[i], opts.compress[i + 1], opts.paf_constant, 0, 1, outb, 1);
            outa.close();
            outb.close();

            GNU_sort({paths.FILE_A_UNCOMPRESSED}, paths.FILE_A_UNCOMPRESSED_SORTED);
            GNU_sort({paths.FILE_B_UNCOMPRESSED}, paths.FILE_B_UNCOMPRESSED_SORTED);
            std::ifstream ina(paths.FILE_A_UNCOMPRESSED_SORTED);
            std::ifstream inb(paths.FILE_B_UNCOMPRESSED_SORTED);
            match_pairs(opts.order, opts.compress[i + 1], opts.paf_constant, ina, inb, out_pairs);

            a.clear();
            b.clear();
        }
    }
    return 0;
}

int stage_filter(const Options& opts, const Paths& paths) {
    std::cout << "Filtering pairs of compression size " << opts.compress.back() << "\n";
    return cache_filter(opts.order, opts.compress.back(), paths.FILE_PAIRS_LIST.back(), paths.FILE_PAIRS_FILTERED);
}
 
int main(int argc, char* argv[]) {
    Options opts;
    bool do_full = false;
    bool do_generate = false;
    bool do_sort = false;
    bool do_match = false;
    bool do_uncompress = false;
    bool do_filter = false;
    bool mpi_enabled = false;
    std::optional<int> linenumber = std::nullopt;

    CLI::App app{"Complementary Pairs Pipeline"};

    app.add_option("order", opts.order, "Order")->required();
    app.add_option("-c,--compress", opts.compress, "Set compression level (default=1)");
    app.add_option("--paf", opts.paf_constant, "Set PAF constant (default=0)");
    app.add_option("-j,--jobid", opts.job_id, "Set job id (default=0)");
    app.add_option("-n,--numjob", opts.job_count, "Set number of jobs (default=1)");
    app.add_option("-d,--dir", opts.temp_dir, "Set directory for populating temporary files (default=result)");
    app.add_flag("-l,--line", linenumber, "Line number to uncompress (default=nullopt)");
    app.add_flag("--full", do_full, "Run full pipeline");
    app.add_flag("--generate", do_generate, "Run generation stage");
    app.add_flag("--sort", do_sort, "Run sorting stage");
    app.add_flag("--match", do_match, "Run matching stage");
    app.add_flag("--uncompress", do_uncompress, "Run uncompression stage");
    app.add_flag("--filter", do_filter, "Run filtering stage");
    app.add_flag("--mpi", mpi_enabled, "Parallelize with MPI");
    CLI11_PARSE(app, argc, argv);

    // TODO: Check verify that solutions can exist given order and paf constant

    // Verify that options are valid
    if(opts.job_count > 1 && do_full) {
        std::cerr << "Cannot run full pipeline with job_count > 1. Run the pipeline in separate steps\n";
        return 1;
    }
    if(opts.order % opts.compress[0] != 0) {
        std::cerr << "Invalid compression value: " << opts.compress[0] << " does not divide " << opts.order << "\n";
        return 1;
    }
    for(size_t i = 0; i < opts.compress.size() - 1; i++) {
        if(opts.compress[i] % opts.compress[i + 1] != 0) {
            std::cerr << "Invalid compression value: " << opts.compress[i + 1] << " does not divide " << opts.compress[i] << "\n";
            return 1;
        }
    }

    std::cout << "Searching for complementary sequences of order " << opts.order << "\n";
    std::cout << "With paf-constant " << opts.paf_constant << "\n";
    std::cout << "And compression factor " << opts.compress[0] << "\n";
    std::cout << "Using directory " << opts.temp_dir << " To store temporary files\n";
    std::cout << "With " << opts.job_count << " jobs" << "\n";
    std::cout << "Current job: " << opts.job_id << "\n";

    const Paths paths(opts);

    // Make sure temporary directories are created beforehand
    std::error_code ec;
    std::filesystem::create_directories(paths.WORK_DIR, ec);
    if(ec) {
        std::cerr << "Failed to create temp directories: " << ec.message() << "\n";
        return 1;
    }

    if(linenumber.has_value()) {
        uncompress_line(opts, paths, linenumber.value());
        return 0;
    }

    // Build pipeline based on flags
    if(do_full || do_generate) stage_generate(opts, paths);
    if(do_full || do_sort) stage_sort(opts, paths);
    if(do_full || do_match) stage_match(opts, paths);
    if(do_full || do_uncompress) stage_uncompress(opts, paths);
    if(do_full || do_filter) stage_filter(opts, paths);

    return 0;
}