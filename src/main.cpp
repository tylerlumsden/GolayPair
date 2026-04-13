#include "CLI11.hpp"
#include "generate_hybrid.h"
#include "sort.h"
#include "match_pairs.h"
#include "uncompression.h"
#include "io.h"
#include "filter.h"

#include <format>
#include <optional>
#include <string>
#include <limits>

struct Options {
    int order;
    int paf_constant = 0;
    int job_id = 0;
    int job_count = 1;
    std::vector<int> compress = {1};
    std::string temp_dir = "results";

    std::string work_dir() const {
        return std::format("{}/order-{}", temp_dir, order);
    }
};

struct Gen_Options {
    std::string file_prefix = "filtered";
};

using Candidate_Files = std::pair<std::vector<std::string>, std::vector<std::string>>;
Candidate_Files candidate_output(const Options& opts, const std::string& prefix) {
    const std::string file_a = std::format("{}/{}-{}-a", opts.work_dir(), opts.order, prefix);
    const std::string file_b = std::format("{}/{}-{}-b", opts.work_dir(), opts.order, prefix);
    std::vector<std::string> list_a;
    std::vector<std::string> list_b;
    for(int i = 0; i < opts.job_count; ++i) {
        std::string indexed_file_a = file_a + "#" + std::to_string(i);
        list_a.push_back(indexed_file_a);
        std::string indexed_file_b = file_b + "#" + std::to_string(i);
        list_b.push_back(indexed_file_b);
    }
    return make_pair(list_a, list_b);
}

// Individual pipeline stages
int stage_generate(const Options& opts, const Gen_Options& gen_opts) {
    auto [files_a, files_b] = candidate_output(opts, gen_opts.file_prefix);
    std::ofstream file_a(files_a[opts.job_id]);
    std::ofstream file_b(files_b[opts.job_id]);
    if(generate_hybrid(opts.order, opts.compress[0], opts.paf_constant, file_a, file_b, opts.job_id, opts.job_count) > 0) return 1;

    return 0;
}

struct Sort_Options {
    std::string input_prefix = "filtered";
    std::string output_prefix = "filtered_sorted";
};

using Sorted_Files = std::pair<std::string, std::string>;
Sorted_Files sort_output(const Options& opts, const std::string& prefix) {
    std::string sorted_a = std::format("{}/{}-{}-a", opts.work_dir(), opts.order, prefix);
    std::string sorted_b = std::format("{}/{}-{}-b", opts.work_dir(), opts.order, prefix);

    return make_pair(sorted_a, sorted_b);
}

int stage_sort(const Options& opts, const Sort_Options& sort_opts) {
    std::cout << "Sorting Candidates\n";

    auto [files_a, files_b] = candidate_output(opts, sort_opts.input_prefix);
    auto [sorted_a, sorted_b] = sort_output(opts, sort_opts.output_prefix);

    if(GNU_sort(files_a, sorted_a, opts.work_dir()) > 0) return 1;
    if(GNU_sort(files_b, sorted_b, opts.work_dir()) > 0) return 1;

    return 0;
}

struct Match_Options {
    std::string input_prefix = "filtered_sorted";
    std::string output_prefix = "pairs";
    bool file_append = false;
};

using Match_File = std::string;
Match_File match_output(const Options& opts, const std::string& prefix, int compress_index) {
    return std::format("{}/{}-{}-{}", opts.work_dir(), opts.order, prefix, opts.compress[compress_index]);
}

int stage_match(const Options& opts, const Match_Options& match_opts) {
    std::cout << "Matching Candidates\n";
    auto [file_a_sorted, file_b_sorted] = sort_output(opts, match_opts.input_prefix);
    std::ifstream ifa(file_a_sorted);
    std::ifstream ifb(file_b_sorted);
    std::ofstream pairs(match_output(opts, match_opts.output_prefix, 0), match_opts.file_append ? std::ios::app : std::ios::trunc);
    return match_pairs(opts.order, opts.compress[0], opts.paf_constant, ifa, ifb, pairs);
}

struct Uncompress_Options {
    std::string input_prefix = "pairs";
    std::string internal_prefix = "filtered";
    std::string sorted_prefix = "filtered_sorted";
    std::string output_prefix = "pairs";
    std::string temp_prefix = "";
    std::optional<long long> line_number;
    size_t range_begin = 0;
    size_t range_end = std::numeric_limits<size_t>::max();
    size_t range_step = 1;
};

int stage_uncompress(const Options& opts, const Uncompress_Options& uncompress_opts) {
    for(size_t i = 0; i < opts.compress.size() - 1; ++i) {

        std::string prefix = (i == 0) ? uncompress_opts.input_prefix : uncompress_opts.output_prefix;
        std::ifstream in_pairs(match_output(opts, prefix, i));
        std::ofstream out_pairs(match_output(opts, prefix, i + 1));

        uncompress_pipeline(
            opts.order,
            opts.compress[i],
            opts.compress[i + 1],
            opts.paf_constant,
            in_pairs,
            out_pairs,
            opts.work_dir(),
            uncompress_opts.temp_prefix,
            uncompress_opts.range_begin,
            uncompress_opts.range_end,
            uncompress_opts.range_step
        );
    }

    return 0;
}

struct Filter_Options {
    std::string input_prefix = "pairs";
    std::string output_prefix = "unique";
};

using Filter_File = std::string;
Filter_File filter_output(const Options& opts, const std::string& prefix) {
    return std::format("{}/{}-{}", opts.work_dir(), opts.order, prefix);
}

int stage_filter(const Options& opts, const Filter_Options& filter_opts) {
    std::cout << "Filtering pairs of compression size " << opts.compress.back() << "\n";
    return cache_filter(
        opts.order, 
        opts.compress.back(), 
        match_output(opts, filter_opts.input_prefix, opts.compress.size() - 1), 
        filter_output(opts, filter_opts.output_prefix)
    );
}


int main(int argc, char* argv[]) {
    Options opts;

    CLI::App app{"Complementary Pairs Pipeline"};

    // SUBCOMMANDS

    auto all = app.add_subcommand("all", "Run all steps in the pipeline");

    Gen_Options gen_opts;
    auto gen = app.add_subcommand("gen", "Candidate generation step");
    gen->add_option("--output,-o", gen_opts.file_prefix, "Output file");

    Sort_Options sort_opts;
    auto sort = app.add_subcommand("sort", "File sorting step");
    sort->add_option("--input,-i", sort_opts.input_prefix, "Input file");
    sort->add_option("--output,-o", sort_opts.output_prefix, "Output file");

    Match_Options match_opts;
    auto match = app.add_subcommand("match", "Candidate matching step");
    match->add_option("--input,-i", match_opts.input_prefix, "Input file");
    match->add_option("--output,-o", match_opts.output_prefix, "Output file");
    match->add_option("-a,--append", match_opts.file_append, "Matched pairs files are opened to append instead of overwrite");
    
    Uncompress_Options uncompress_opts;
    auto uncompress = app.add_subcommand("uncompress", "Pair uncompression step");
    uncompress->add_option("--input,-i", uncompress_opts.input_prefix, "Input file");
    uncompress->add_option("--output,-o", uncompress_opts.output_prefix, "Output file");
    uncompress->add_option("--internal", uncompress_opts.internal_prefix, "Internal candidate file prefix");
    uncompress->add_option("--sorted", uncompress_opts.sorted_prefix, "Sorted candidate file prefix");
    uncompress->add_option("--line,-l", uncompress_opts.line_number, "Process only this line number (1-indexed)");
    uncompress->add_option("-b,--range_begin", uncompress_opts.range_begin, "Beginning range of lines to uncompress");
    uncompress->add_option("-e,--range_end", uncompress_opts.range_end, "Ending range of lines to uncompress");
    uncompress->add_option("-s,--range_step", uncompress_opts.range_step, "Step of range to uncompress");
    uncompress->add_option("-p,--prefix", uncompress_opts.temp_prefix, "Prefix for generated temp files");

    Filter_Options filter_opts;
    auto filter = app.add_subcommand("filter", "Pair equivalence filter step");
    filter->add_option("--input,-i", uncompress_opts.input_prefix, "Input file");
    filter->add_option("--output,-o", uncompress_opts.output_prefix, "Output file");

    // Require a minimum of one subcommand, and any maximum
    app.require_subcommand(1, 0);

    // GLOBAL OPTIONS
    app.add_option("order", opts.order, "Order")->required();
    app.add_option("-c,--compress", opts.compress, "Set compression level (default=1)");
    app.add_option("--paf", opts.paf_constant, "Set PAF constant (default=0)");
    app.add_option("-j,--jobid", opts.job_id, "Set job id (default=0)");
    app.add_option("-n,--numjob", opts.job_count, "Set number of jobs (default=1)");
    app.add_option("-d,--dir", opts.temp_dir, "Set directory for populating temporary files (default=result)");
    CLI11_PARSE(app, argc, argv);

    std::error_code ec;
    std::filesystem::create_directories(opts.work_dir(), ec);
    if(ec) {
        std::cerr << "Failed to create temp directories: " << ec.message() << "\n";
        return 1;
    }

    if(*gen || *all) {
        if(stage_generate(opts, gen_opts)) return 1;
    }

    if(*sort || *all) {
        if(stage_sort(opts, sort_opts)) return 1;
    }

    if(*match || *all) {
        if(stage_match(opts, match_opts)) return 1;
    }

    if(*uncompress || *all) {
        if(stage_uncompress(opts, uncompress_opts)) return 1;
    }

    if(*filter || *all) {
        if(stage_filter(opts, filter_opts)) return 1;
    }
    
    return 0;
}