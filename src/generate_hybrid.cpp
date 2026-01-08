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

#include "constants.h"
#include "io.h"

using namespace std;

void writeSeq(FILE * out, vector<int> seq);

void printArray(vector<int> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
}

int rowsum(vector<int> seq) {
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

int generate_hybrid(const int ORDER, const int COMPRESS, const int PAF_CONSTANT, std::ofstream& out_a, std::ofstream& out_b, const int PROC_ID = 0, const int PROC_NUM = 1) {

    const std::vector<std::pair<int, int>> decompslist = getdecomps(sum_constant(ORDER, PAF_CONSTANT));

    if(decompslist.size() == 0) {
        std::cerr << "Order " << ORDER << " cannot be decomposed into a sum of squares\n" << ORDER << "*2\n";
        std::cerr << "Hence there are no solutions.\n";
        return 1;
    }

    for(std::pair<int, int> decomp : decompslist) {
        std::cout << decomp.first << " " << decomp.second << "\n";
    }

    const int LEN = ORDER / COMPRESS;

    Fourier FourierManager = Fourier(LEN);

    unsigned long long int count = 0;
    std::set<int> alphabet;
 
    if(COMPRESS % 2 == 0) {
        for(int i = 0; i <= COMPRESS; i += 2) {
            alphabet.insert(i);
            alphabet.insert(-i);
        }
    } else {
        for(int i = 1; i <= COMPRESS; i += 2) {
            alphabet.insert(i);
            alphabet.insert(-i);
        }
    }

    set<vector<int>> partialsols;
    set<vector<int>> generatorsA = constructGenerators(0, LEN);
    set<vector<int>> generatorsB = constructGenerators(1, LEN);
    
    std::vector<int> seq;
    std::vector<std::vector<int>> proc_work = {{}};
    if(PROC_NUM > 1) {
        for(int i = 1; i <= LEN; i++) {
            proc_work.clear();
            int count = 0;
            while(nextBranch(seq, i, alphabet)) {
                if((int)seq.size() == i && partialCanonical(seq)) {
                    count++;
                    if(count % PROC_NUM == PROC_ID) {
                        proc_work.push_back(seq);
                    }
                }
            }
            if(count >= PROC_NUM * 1000) {
                break;
            }
        }
    }
    std::ofstream out("test");
    for(std::vector<int> seq : proc_work) {
        do {
            if(!partialCanonical(seq)) {
                if(!nextBranch(seq, seq.size(), alphabet)) {
                    break;
                }
            }

            size_t curr_length = seq.size();
            if((int)curr_length >= (LEN / 2) + 1) {
                std::vector<std::vector<int>> rowcombo = finish_with_partitions(seq, decompslist, LEN, alphabet);
                for(vector<int> tail : rowcombo) {

                    vector<int> newseq = seq;
                    newseq.insert(newseq.end(), tail.begin(), tail.end());

                    do {
                        for(std::pair<int, int> decomp : decompslist) {
                            if(rowsum(newseq) == decomp.first) {
                                std::vector<double> psd = FourierManager.calculate_psd(newseq);
                                if(FourierManager.psd_filter(psd, ORDER, PAF_CONSTANT) && isCanonical(newseq, generatorsA)) {
                                    count++;
                                    write_seq_psd(newseq, psd, out_a);
                                }
                            }

                            if(rowsum(newseq) == decomp.second) {
                                std::vector<double> psd = FourierManager.calculate_psd(newseq);
                                if(FourierManager.psd_filter(psd, ORDER, PAF_CONSTANT) && isCanonical(newseq, generatorsB)) {
                                    count++;
                                    write_seq_psd_invert(newseq, psd, out_b, ORDER * 2 - PAF_CONSTANT);
                                }
                            }
                        }

                    } while(next_permutation(newseq.begin() + curr_length, newseq.end()));
                    
                }
            }
        } while(nextBranch(seq, (LEN / 2) + 1, alphabet));
    }

    printf("%llu\n", count);

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