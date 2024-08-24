#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"../lib/orderly_equivalence.h"
#include"fftw3.h"
#include"../lib/array.h"
#include"../lib/decomps.h"
#include"../lib/fourier.h"
#include<tgmath.h>
#include<algorithm>
#include<fstream>
#include"../lib/binary.h"

using namespace std;

void writeSeq(FILE * out, vector<int> seq);


double norm(fftw_complex dft) {
    return dft[0] * dft[0] + dft[1] * dft[1];
}

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

int main(int argc, char ** argv) {

    int ORDER = stoi(argv[1]);
    int COMPRESS = stoi(argv[2]);
    int PAF_BOUND = stoi(argv[3]);
    int LEN = ORDER / COMPRESS;

    Runtime Runtime(PAF_BOUND, ORDER, LEN);

    //write classes to file
    char fname[100];
    sprintf(fname, "results/%d/%d-unique-filtered-a_%d", ORDER, ORDER, 1);
    std::ofstream outa(fname, std::ios::binary);

    sprintf(fname, "results/%d/%d-unique-filtered-b_%d", ORDER, ORDER, 1);
    std::ofstream outb(fname, std::ios::binary);

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
                if(Runtime.a_is_solution(sum + rowsum(seq)) || Runtime.b_is_solution(sum + rowsum(seq))) {
                    rowcombo.push_back(combo);
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

                    if(Runtime.a_is_solution(rowsum(newseq))) {
                        std::vector<double> psd = Runtime.PSD(newseq);
                        if(Runtime.PSD_filter(psd) && isCanonical(newseq, generatorsA)) {
                            count++;
                            binaryWriteSeq(outa, newseq, alphabet);
                        }
                    }

                    if(Runtime.b_is_solution(rowsum(newseq))) {
                        std::vector<double> psd = Runtime.PSD(newseq);
                        if(Runtime.PSD_filter(psd) && isCanonical(newseq, generatorsB)) {
                            count++;
                            binaryWriteSeq(outb, newseq, alphabet);
                        }
                    }

                } while(next_permutation(newseq.begin() + LEN / 2, newseq.end()));
                
            }
        }
    }

    printf("%llu\n", count);
    
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