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
#include"match_pairs.h"
#include"sort.h"
#include"constants.h"
#include"io.h"
#include <thread>
#include <filesystem>
#include "uncompression.h"

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