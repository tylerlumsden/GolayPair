#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <mpi.h>

#include "constants.h"
#include "generate_hybrid.h"
#include "sort.h"
#include "match_pairs.h"
#include "uncompression.h"
#include "filter.h"
#include "CLI11.hpp"
#include "generate_orderly.h"

struct Options {
    int order;
    int paf_constant = 0;
    int parallel_factor = 1;
    std::vector<int> compress = {1};
    std::string temp_dir = "results";
};

struct Paths {
    const std::string WORK_DIR;
    const std::string FILE_A;
    const std::string FILE_B;
    const std::string FILE_A_SORTED;
    const std::string FILE_B_SORTED;
    const std::string FILE_PAIRS;
    const std::string FILE_PAIRS_UNCOMPRESSED;
    
    Paths(const std::string& temp_dir, int order)
        : WORK_DIR(std::format("{}/order-{}", temp_dir, order))
        , FILE_A(std::format("{}/{}-filtered-a", WORK_DIR, order))
        , FILE_B(std::format("{}/{}-filtered-b", WORK_DIR, order))
        , FILE_A_SORTED(FILE_A + ".sorted")
        , FILE_B_SORTED(FILE_B + ".sorted")
        , FILE_PAIRS(std::format("{}/{}-pairs", WORK_DIR, order))
        , FILE_PAIRS_UNCOMPRESSED(FILE_PAIRS + ".uncompress")
    {}
};

// Pipeline stage type
using PipelineStage = std::function<int(const Options&, const Paths&)>;

// Individual pipeline stages
int stage_generate(const Options& opts, const Paths& paths) {
    std::cout << "Generating Candidates\n";
    for(int i = 0; i < opts.parallel_factor; i++) {
        std::ofstream file_a(paths.FILE_A + "-" + std::to_string(i));
        std::ofstream file_b(paths.FILE_B + "-" + std::to_string(i));
        if(generate_hybrid(opts.order, opts.compress[0], opts.paf_constant, file_a, file_b, i, opts.parallel_factor) > 0) return 1;
    }
    return 0;
}

int stage_generate_mpi(const Options& opts, const Paths& paths) {
    static bool mpi_initialized = false;
    if(!mpi_initialized) {
        MPI_Init(nullptr, nullptr);
        mpi_initialized = true;
    }
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(rank == 0) {
        std::cout << "Generating Candidates with " << size << " MPI processes\n";
    }

    {
        std::ofstream file_a(paths.FILE_A + "-" + std::to_string(rank));
        std::ofstream file_b(paths.FILE_B + "-" + std::to_string(rank));
        if(generate_hybrid(opts.order, opts.compress[0], opts.paf_constant, file_a, file_b, rank, size) > 0) return 1;
    }
    
    // Synchronize all processes before continuing
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Only rank 0 continues with rest of pipeline
    if(rank != 0) {
        MPI_Finalize();
        exit(0);
    }
    
    return 0;
}

int stage_sort(const Options& opts, const Paths& paths) {
    std::vector<std::string> files_a;
    for(int i = 0; i < opts.parallel_factor; i++) {
        files_a.push_back(std::format("{}-{}", paths.FILE_A, i));
    }

    std::vector<std::string> files_b;
    for(int i = 0; i < opts.parallel_factor; i++) {
        files_b.push_back(std::format("{}-{}", paths.FILE_B, i));
    }

    std::cout << "Sorting Candidates\n";
    if(GNU_sort(files_a, paths.FILE_A_SORTED) > 0) return 1;
    if(GNU_sort(files_b, paths.FILE_B_SORTED) > 0) return 1;
    return 0;
}

int stage_match(const Options& opts, const Paths& paths) {
    std::cout << "Matching Candidates\n";
    std::ofstream pairs(paths.FILE_PAIRS);
    std::ifstream file_a_sorted(paths.FILE_A_SORTED);
    std::ifstream file_b_sorted(paths.FILE_B_SORTED);
    return match_pairs(opts.order, opts.compress[0], opts.paf_constant, file_a_sorted, file_b_sorted, pairs);
}

int stage_uncompress(const Options& opts, const Paths& paths) {
    if(opts.compress[0] <= 1) return 0;
    
    std::cout << "Running Uncompression Pipeline\n";
    for(size_t i = 0; i < opts.compress.size() - 1; i++) {
        std::cout << "Uncompressing to new compression ratio " << opts.compress[i + 1] << "\n";
        std::ifstream in_pairs(paths.FILE_PAIRS);
        std::ofstream out_pairs(paths.FILE_PAIRS_UNCOMPRESSED);
        if(uncompression_pipeline(opts.order, opts.compress[i], opts.compress[i + 1], opts.paf_constant, in_pairs, out_pairs, paths.WORK_DIR) > 0) return 1;
        std::filesystem::rename(paths.FILE_PAIRS_UNCOMPRESSED, paths.FILE_PAIRS);
    }
    return 0;
}

int stage_filter(const Options& opts, const Paths& paths) {
    std::cout << "Filtering pairs of compression size " << opts.compress.back() << "\n";
    return cache_filter(opts.order, opts.compress.back(), paths.FILE_PAIRS, paths.FILE_PAIRS + ".unique");
}

int run_pipeline(const std::vector<PipelineStage>& pipeline, const Options& opts, const Paths& paths) {
    for(const auto& stage : pipeline) {
        if(stage(opts, paths) > 0) return 1;
    }
    return 0;
}

int verify_opts(const Options& opts) {
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

    return 0;
}
 
int main(int argc, char* argv[]) {
    Options opts;
    bool do_generate = false;
    bool do_sort = false;
    bool do_match = false;
    bool do_uncompress = false;
    bool do_filter = false;

    CLI::App app{"Complementary Pairs Pipeline"};

    app.add_option("order", opts.order, "Order");
    app.add_option("-c,--compress", opts.compress, "Set compression level (default=1)");
    app.add_option("--paf", opts.paf_constant, "Set PAF constant (default=0)");
    app.add_option("-p,--proc", opts.parallel_factor, "Set parallelization factor (default=1)");
    app.add_option("-d,--dir", opts.temp_dir, "Set directory for populating temporary files (default=result)");
    app.add_flag("--generate", do_generate, "Run generation stage");
    app.add_flag("--sort", do_sort, "Run sorting stage");
    app.add_flag("--match", do_match, "Run matching stage");
    app.add_flag("--uncompress", do_uncompress, "Run uncompression stage");
    app.add_flag("--filter", do_filter, "Run filtering stage");
    CLI11_PARSE(app, argc, argv);

    if(verify_opts(opts) > 0) return 1;

    std::cout << "Searching for complementary sequences of order " << opts.order << "\n";
    std::cout << "With paf-constant " << opts.paf_constant << "\n";
    std::cout << "And compression factor " << opts.compress[0] << "\n";
    std::cout << "Using directory " << opts.temp_dir << " To store temporary files\n";

    const Paths paths(opts.temp_dir, opts.order);

    // Make sure temporary directories are created beforehand
    std::error_code ec;
    std::filesystem::create_directories(paths.WORK_DIR, ec);
    if(ec) {
        std::cerr << "Failed to create temp directories: " << ec.message() << "\n";
        return 1;
    }

    // Build pipeline based on flags
    std::vector<PipelineStage> pipeline;
    if(do_generate) pipeline.push_back(opts.parallel_factor > 1 ? stage_generate_mpi : stage_generate);
    if(do_sort) pipeline.push_back(stage_sort);
    if(do_match) pipeline.push_back(stage_match);
    if(do_uncompress) pipeline.push_back(stage_uncompress);
    if(do_filter) pipeline.push_back(stage_filter);
    
    // If no stages specified, run all (default full pipeline)
    if(pipeline.empty()) {
        pipeline = {opts.parallel_factor > 1 ? stage_generate_mpi : stage_generate, stage_sort, stage_match, stage_uncompress, stage_filter};
    }
    
    // Execute pipeline
    if(run_pipeline(pipeline, opts, paths) > 0) return 1;

    return 0;
}