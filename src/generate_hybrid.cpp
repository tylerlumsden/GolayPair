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

template<class BidirIt>
bool nextPermutation(BidirIt first, BidirIt last, set<int> alphabet);

int sum_constant(int order, int paf) {
    return order * 2 + (order - 1) * paf;
}

void write_seq_psd(std::vector<int> seq, std::vector<double> psd, std::ofstream& out) {
    for(std::size_t i = 1; i < psd.size(); i++) {
        out << (int)rint(psd[i]);
    }
    out << " ";
    for(std::size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
    out << "\n";
}

void write_seq_psd_invert(std::vector<int> seq, std::vector<double> psd, std::ofstream& out, const int BOUND) {
    for(std::size_t i = 1; i < psd.size(); i++) {
        out << BOUND - (int)rint(psd[i]);
    }
    out << " ";
    for(std::size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
    out << "\n";
}

int generate_hybrid(const int ORDER, const int COMPRESS, const int PAF_CONSTANT, std::ofstream& out_a, std::ofstream& out_b) {

    const std::vector<std::pair<int, int>> decompslist = getdecomps(sum_constant(ORDER, PAF_CONSTANT));

    if(decompslist.size() == 0) {
        std::cerr << "Order " << ORDER << " cannot be decomposed into a sum of squares\n" << ORDER << "*2\n";
        std::cerr << "Hence there are no solutions.\n";
        return 1;
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
    vector<int> seq;
    set<vector<int>> generatorsA = constructGenerators(0, LEN);
    set<vector<int>> generatorsB = constructGenerators(1, LEN);

    vector<int> test = {1};

    while(nextBranch(seq, LEN / 2, alphabet)) {

        if(!partialCanonical(seq)) {
            if(!nextBranch(seq, seq.size(), alphabet)) {
                break;
            }
        }

        if((int)seq.size() == LEN / 2) {

            //finish the constructions
            vector<vector<int>> combinations = getCombinations(LEN - seq.size(), alphabet);
            std::vector<std::vector<int>> rowcombo;

            for(std::vector<int> combo : combinations) {
                int sum = rowsum(combo);
                for(std::pair<int, int> decomp : decompslist) {
                    if(sum == decomp.first - rowsum(seq) || sum == decomp.second - rowsum(seq)) {
                        rowcombo.push_back(combo);
                    }
                }
            }  

            for(vector<int> tail : rowcombo) {

                sort(tail.begin(), tail.end());

                vector<int> newseq = seq;
                
                newseq.insert(newseq.end(), tail.begin(), tail.end());

                do {


                    if(newseq.back() == *alphabet.begin()) {
                        continue;
                    }

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

                } while(next_permutation(newseq.begin() + LEN / 2, newseq.end()));
                
            }
        }
    }

    printf("%llu\n", count);

    return 0;
}
template<class BidirIt>
bool nextPermutation(BidirIt first, BidirIt last, set<int> alphabet) {
    int min = *std::min_element(alphabet.begin(), alphabet.end());
    int max = *std::max_element(alphabet.begin(), alphabet.end());

    last = last - 1;

    auto curr = last;

    if(*curr != max) {

        *curr = *curr + 2;
        return true;

    } else if(*curr == max) {

        while(curr != first - 1) {
            if(*curr != max) {
                *curr = *curr + 2;
                curr++;
                while(curr != last + 1) {
                    *curr = min;
                    curr++;
                }
                return true;
            }
            curr--;
        }

        curr++;
        while(curr != last) {
            *curr = min;
        }
        
        return false;
        
    }

    return false;
}

bool nextBranch(vector<int>& seq, unsigned int len, set<int> alphabet) {

    int max = *alphabet.rbegin();
    int min = *alphabet.begin();

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


void writeSeq(FILE * out, vector<int> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        fprintf(out, "%d ", seq[i]);
    }
}

int classIsGenerated(vector<set<vector<int>>>& classes, vector<int>& seq) {
    for(set<vector<int>> map : classes) {
        if(map.find(seq) != map.end()) {
            return 1;
        }
    }
    return 0;
}