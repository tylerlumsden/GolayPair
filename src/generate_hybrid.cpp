#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"orderly_equivalence.h"
#include"fftw3.h"
#include"array.h"
#include"decomps.h"
#include"fourier.h"
#include<tgmath.h>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<format>
#include <functional>

#include "constants.h"
#include "io.h"
#include "lyndon.h"

using namespace std;

void writeSeq(FILE * out, vector<int> seq);

void printArray(vector<int> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
}

int rowsum(const std::vector<int>& seq) {
    int sum = 0;
    for(unsigned int i = 0; i < seq.size(); i++) {
        sum = sum + seq[i];
    }
    return sum;
}

bool nextBranch(vector<int>& seq, unsigned int len, set<int> alphabet);

int sum_constant(int order, int paf) {
    return order * 2 + (order - 1) * paf;
}

std::vector<std::vector<int>> finish_with_partitions(std::vector<int> partialseq, std::vector<std::pair<int, int>> decompslist, const int LEN, std::set<int> alphabet) {
        std::vector<std::vector<int>> rowcombo = {{}};
        if(LEN > (int)partialseq.size()) {
            rowcombo = {};
            //finish the constructions
            vector<vector<int>> combinations = getCombinations(LEN - partialseq.size(), alphabet);

            for(std::vector<int> combo : combinations) {
                int sum = rowsum(combo);
                for(std::pair<int, int> decomp : decompslist) {
                    if(sum == decomp.first - rowsum(partialseq) || sum == decomp.second - rowsum(partialseq)) {
                        std::sort(combo.begin(), combo.end());
                        rowcombo.push_back(combo);
                    }
                }
            }  
        }
        return rowcombo;
}

void generate_orderly_prefix(const int LEN, 
    const std::set<int>& alphabet, 
    std::vector<int>& seq, 
    std::function<void()> callback) {

    size_t origlen = seq.size();
    
    do {
        if(!partialCanonical(seq)) {
            if(!nextBranch(seq, seq.size(), alphabet)) {
                return;
            }
        }

        if(seq.size() == (size_t)LEN) {
            callback();
        }
    } while(nextBranch(seq, LEN, alphabet) && seq.size() > origlen);
}

void generate_partition_postfix(const int LEN, 
    const std::set<int>& alphabet, 
    std::vector<int>& seq, 
    const std::vector<std::pair<int, int>> decompslist,
    std::function<void()> callback) {

    size_t curr_length = seq.size();
    std::vector<std::vector<int>> rowcombo = finish_with_partitions(seq, decompslist, LEN, alphabet);
    for(vector<int> tail : rowcombo) {
        seq.insert(seq.end(), tail.begin(), tail.end());
        
        do {
            callback();
        } while(next_permutation(seq.begin() + curr_length, seq.end()));
        seq.resize(curr_length);
    }
}

int generate_hybrid(const int ORDER, const int COMPRESS, const int PAF_CONSTANT, std::ofstream& out_a, std::ofstream& out_b, const int PROC_ID = 0, const int PROC_NUM = 1) {

    const int LEN = ORDER / COMPRESS;
    const std::vector<std::pair<int, int>> decompslist = getdecomps(sum_constant(ORDER, PAF_CONSTANT));

    if(decompslist.size() == 0) {
        std::cerr << "Order " << ORDER << " cannot be decomposed into a sum of squares\n" << ORDER << "*2\n";
        std::cerr << "Hence there are no solutions.\n";
        return 1;
    }

    for(std::pair<int, int> decomp : decompslist) {
        std::cout << decomp.first << " " << decomp.second << "\n";
    }

    std::set<int> alphabet = getalphabet(COMPRESS);
 
    set<vector<int>> generatorsA = constructGenerators(0, LEN);
    set<vector<int>> generatorsB = constructGenerators(1, LEN);

    boost::multiprecision::cpp_int count = 0;
    boost::multiprecision::cpp_int orderly_count = 0;
    boost::multiprecision::cpp_int seq_count = necklace_count(LEN, alphabet.size());

    Progress Prog(seq_count);
    Fourier FourierManager = Fourier(LEN);

    std::cout << "Filtering " << seq_count << " sequences\n";
    std::vector<int> alpha(alphabet.begin(), alphabet.end());
    generate_necklaces_wrapper(LEN, alpha, PROC_ID, PROC_NUM, [&](const std::vector<int>& seq) {
        ++orderly_count;
        Prog.update(orderly_count);
        for(const std::pair<int, int>& decomp : decompslist) {
            if(rowsum(seq) == decomp.first) {
                const std::vector<double>& psd = FourierManager.calculate_psd(seq);
                if(FourierManager.psd_filter(psd, ORDER, PAF_CONSTANT) && isCanonical(seq, generatorsA)) {
                    count++;
                    write_seq_psd(seq, psd, out_a);
                }
            }

            if(rowsum(seq) == decomp.second) {
                const std::vector<double>& psd = FourierManager.calculate_psd(seq);
                if(FourierManager.psd_filter(psd, ORDER, PAF_CONSTANT) && isCanonical(seq, generatorsB)) {
                    count++;
                    write_seq_psd_invert(seq, psd, out_b, ORDER * 2 - PAF_CONSTANT);
                }
            }
        }
    });

    std::cout << "Necklace Count: " << necklace_count(LEN, alphabet.size()) << "\n";
    std::cout << "Orderly Count: " << orderly_count << "\n";
    std::cout << "Passed PSD filter: " << count << "\n";

    return 0;
}

bool nextBranch(vector<int>& seq, unsigned int len, set<int> alphabet) {

    int max = *alphabet.rbegin();
    int min = *alphabet.begin();
    if(seq.size() > len) {
        return false;
    }

    if(seq.size() == len) {
        while(seq.size() != 0 && seq[seq.size() - 1] == max) {
            seq.pop_back();
        }
        if(seq.size() == 0) {
            return false;
        }
        int next = seq.back() + 2;
        seq.pop_back();
        seq.push_back(next);
    } else {
        seq.push_back(min);
    }

    return true;

}

int classIsGenerated(vector<set<vector<int>>>& classes, vector<int>& seq) {
    for(set<vector<int>> map : classes) {
        if(map.find(seq) != map.end()) {
            return 1;
        }
    }
    return 0;
}