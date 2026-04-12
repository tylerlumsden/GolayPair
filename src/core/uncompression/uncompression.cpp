#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<map>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"fftw3.h"
#include"array.h"
#include"fourier.h"
#include"equivalence.h"
#include<tgmath.h>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<format>
#include <functional>

#include"golay.h"
#include"constants.h"
#include"io.h"
#include <thread>
#include <filesystem>
#include "uncompression.h"

int uncompress_recursive(std::vector<int>& orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, const int PROC_ID, const int PROC_NUM, std::ofstream& outfile, int seqflag);
int uncompress_gpu(std::vector<int>& orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, const int PROC_ID, const int PROC_NUM, std::ofstream& outfile, int seqflag);

int uncompress_gpu(std::vector<int>& orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, const int PROC_ID, const int PROC_NUM, std::ofstream& outfile, int seqflag) {
    const int ORDER = orig.size() * COMPRESS;

    Fourier FourierManager = Fourier(ORDER / NEWCOMPRESS);

    std::set<int> alphabet = getalphabet(COMPRESS);

    std::set<int> newalphabet = getalphabet(NEWCOMPRESS);

    std::vector<std::vector<int>> parts = getCombinations(COMPRESS / NEWCOMPRESS, newalphabet);
    std::vector<std::vector<int>> partition;

    std::map<int, std::vector<std::vector<int>>> partitions;

    //generate all permutations of possible decompositions for each letter in the alphabet
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

    //shift original sequence such that the element with the largest number of permutations is in the front
    set<int> seta;
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

    set<vector<int>> perma;
    for(vector<int> perm : partitions.at(orig[0])) {
        set<vector<int>> equiv = generateUncompress(perm);
        perma.insert(*equiv.begin());
    }

    vector<vector<int>> newfirsta;
    for(vector<int> perm : perma) {
        newfirsta.push_back(perm);
    }

    PermList permutation_list;
    permutation_list.push_back(newfirsta);
    for(size_t i = 1; i < orig.size(); ++i) {
        permutation_list.push_back(partitions.at(orig[i]));
    }
    
    std::function<void(std::span<int>, std::span<double>)> write_function; 
    if(seqflag) {
        write_function =
        [&outfile](std::span<int> seq, std::span<double> psd) {
            write_seq_psd(seq, psd, outfile);
        };
    } else {
        int bound = ORDER * 2 - PAF_CONSTANT;
        write_function = 
        [&outfile, bound](std::span<int> seq, std::span<double> psd) {
            write_seq_psd_invert(seq, psd, outfile, bound);
        };
    }

    uncompress_kernel(
        orig, 
        permutation_list,
        ORDER / NEWCOMPRESS, 
        ORDER, 
        PAF_CONSTANT,
        write_function
    );

    return 0;
}

int uncompress_recursive(std::vector<int>& orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, const int PROC_ID, const int PROC_NUM, std::ofstream& outfile, int seqflag) {
    const int ORDER = orig.size() * COMPRESS;
    const int LEN = ORDER / COMPRESS;

    Fourier FourierManager = Fourier(ORDER / NEWCOMPRESS);

    std::set<int> alphabet = getalphabet(COMPRESS);

    std::set<int> newalphabet = getalphabet(NEWCOMPRESS);

    std::vector<std::vector<int>> parts = getCombinations(COMPRESS / NEWCOMPRESS, newalphabet);
    std::vector<std::vector<int>> partition;

    std::map<int, std::vector<std::vector<int>>> partitions;

    //generate all permutations of possible decompositions for each letter in the alphabet
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
    
    //shift original sequence such that the element with the largest number of permutations is in the front
    set<int> seta;
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

    set<vector<int>> perma;
    for(vector<int> perm : partitions.at(orig[0])) {
        set<vector<int>> equiv = generateUncompress(perm);
        perma.insert(*equiv.begin());
    }

    vector<vector<int>> newfirsta;
    for(vector<int> perm : perma) {
        newfirsta.push_back(perm);
    }
    
    auto uncompress_lambda = [&](const auto& self, std::vector<int>& seq, size_t curr_index, size_t depth_index, std::function<void(const std::vector<int>&)> callback) {
        if(curr_index >= orig.size() || curr_index == depth_index) {
            callback(seq);
            return;
        }

        else if(curr_index == 0) {
            for(const std::vector<int>& permutation : newfirsta) {
                for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                    seq[curr_index + (LEN * i)] = permutation[i];
                }
                self(self, seq, curr_index + 1, depth_index, callback);
            }
        } else {
            for(const std::vector<int>& permutation : partitions.at(orig[curr_index])) {
                for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                    seq[curr_index + (LEN * i)] = permutation[i];
                }
                self(self, seq, curr_index + 1, depth_index, callback);
            }
        }
    };

    std::vector<int> seq;
    seq.resize(ORDER / NEWCOMPRESS);
    std::vector<std::vector<int>> prev_depth = {seq};
    size_t depth = 0;
    if(PROC_NUM > 1) {
        long long count = 0;
        for(; depth < orig.size() && count < 1000 * PROC_NUM; ++depth) {
            count = 0;
            std::vector<std::vector<int>> curr_depth;
            for(std::vector<int>& partial : prev_depth) {
                uncompress_lambda(uncompress_lambda, partial, depth, depth + 1, [&](const std::vector<int>& partial_seq) {
                    curr_depth.push_back(partial_seq);
                    ++count;
                });
            }
            prev_depth = curr_depth;
        }
    }

    std::vector<std::vector<int>> partial_list;
    for(size_t i = 0; i < prev_depth.size(); ++i) {
        if(static_cast<int>(i) % PROC_NUM == PROC_ID) {
            partial_list.push_back(prev_depth[i]);
        }
    }

    std::cout << "Partial size: " << partial_list.size() << "\n";

    for(std::vector<int>& partial_seq : partial_list) {
        uncompress_lambda(uncompress_lambda, partial_seq, depth, orig.size(), [&](const std::vector<int>& full_seq) {
            const std::vector<double>& psd = FourierManager.calculate_psd(full_seq);

            if(FourierManager.psd_filter(psd, ORDER, PAF_CONSTANT)) { 
                if(seqflag) {
                    write_seq_psd(full_seq, psd, outfile);
                } else {
                    write_seq_psd_invert(full_seq, psd, outfile, ORDER * 2 - PAF_CONSTANT);
                }
            }
        });
    }

    return 0;
}

