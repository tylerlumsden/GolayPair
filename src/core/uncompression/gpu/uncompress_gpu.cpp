#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <functional>
#include <cstdio>

#include "array.h"
#include "equivalence.h"
#include "constants.h"
#include "io.h"
#include <boost/multiprecision/cpp_int.hpp>
#include "uncompress_kernel.h"

int uncompress_gpu(std::vector<int>& orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, const int PROC_ID, const int PROC_NUM, std::ofstream& outfile, int seqflag) {
    const int ORDER = orig.size() * COMPRESS;

    std::set<int> alphabet = getalphabet(COMPRESS);
    std::set<int> newalphabet = getalphabet(NEWCOMPRESS);

    std::vector<std::vector<int>> parts = getCombinations(COMPRESS / NEWCOMPRESS, newalphabet);
    std::vector<std::vector<int>> partition;
    std::map<int, std::vector<std::vector<int>>> partitions;

    for(int letter : alphabet) {
        partition.clear();
        for(std::vector<int> part : parts) {
            int sum = 0;
            for(long unsigned int i = 0; i < part.size(); i++) {
                sum += part[i];
            }
            if(sum == letter) {
                do {
                    partition.push_back(part);
                } while(next_permutation(part.begin(), part.end()));
            }
        }
        partitions.insert(make_pair(letter, partition));
    }

    std::set<int> seta;
    for(int element : orig) {
        seta.insert(element);
    }

    size_t max = 0;
    int best = orig[0];
    for(int element : seta) {
        if(partitions.at(element).size() > max) {
            max = partitions.at(element).size();
            best = element;
        }
    }
    for(size_t i = 0; i < orig.size(); i++) {
        if(orig[i] == best) {
            rotate(orig.begin(), orig.begin() + i, orig.end());
        }
    }

    std::set<std::vector<int>> perma;
    for(std::vector<int> perm : partitions.at(orig[0])) {
        std::set<std::vector<int>> equiv = generateUncompress(perm);
        perma.insert(*equiv.begin());
    }

    std::vector<std::vector<int>> newfirsta(perma.begin(), perma.end());

    PermList permutation_list;
    permutation_list.push_back(newfirsta);
    for(size_t i = 1; i < orig.size(); ++i) {
        permutation_list.push_back(partitions.at(orig[i]));
    }

    std::function<void(std::span<int>, std::span<double>)> write_function;
    if(seqflag) {
        write_function = [&outfile](std::span<int> seq, std::span<double> psd) {
            write_seq_psd(seq, psd, outfile);
        };
    } else {
        int bound = ORDER * 2 - PAF_CONSTANT;
        write_function = [&outfile, bound](std::span<int> seq, std::span<double> psd) {
            write_seq_psd_invert(seq, psd, outfile, bound);
        };
    }

    UncompressKernel kernel(permutation_list, ORDER, COMPRESS, NEWCOMPRESS, PAF_CONSTANT);
    kernel.run(orig, write_function);

    return 0;
}