#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"../lib/orderly_equivalence.h"
#include"../lib/fftw-3.3.10/api/fftw3.h"
#include"../lib/array.h"
#include"../lib/decomps.h"
#include"../lib/fourier.h"
#include<tgmath.h>
#include<algorithm>

#define LEN (ORDER / COMPRESS)

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

    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * LEN);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * LEN);
    plan = fftw_plan_dft_1d(LEN, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    //write classes to file
    char fname[100];
    sprintf(fname, "results/%d-unique-filtered-0", ORDER);
    FILE * outa = fopen(fname, "w");

    sprintf(fname, "results/%d-unique-filtered-1", ORDER);
    FILE * outb = fopen(fname, "w");

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
    set<vector<int>> generatorsA = constructGenerators(0);
    set<vector<int>> generatorsB = constructGenerators(1);

    while(nextBranch(seq, LEN / 2, alphabet)) {

        if(!partialCanonical(seq)) {
            if(!nextBranch(seq, seq.size(), alphabet)) {
                break;
            }
        }

        if(seq.size() == LEN / 2) {

            //finish the constructions
            vector<vector<int>> combinations = getCombinations(LEN - seq.size(), alphabet);
            std::vector<std::vector<int>> rowcombo;

            for(std::vector<int> combo : combinations) {
                int sum = rowsum(combo);
                if(sum == decomps[ORDER][0][0] - rowsum(seq) || sum == decomps[ORDER][0][1] - rowsum(seq)) {
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

                    if(rowsum(newseq) == decomps[ORDER][0][0]) {
                        out = dft(newseq, in, out, plan);
                        if(dftfilter(out, LEN) && isCanonical(newseq, generatorsA)) {
                            count++;
                            for(int i = 0; i < LEN / 2; i++) {
                                fprintf(outa, "%d",    (int)rint(norm(out[i])));
                            }
                            fprintf(outa, " ");
                            writeSeq(outa, newseq);
                            fprintf(outa, "\n");
                        }
                    }

                    if(rowsum(newseq) == decomps[ORDER][0][1]) {
                        out = dft(newseq, in, out, plan);
                        if(dftfilter(out, LEN) && isCanonical(newseq, generatorsB)) {
                            count++;
                            for(int i = 0; i < LEN / 2; i++) {
                                fprintf(outb, "%d",   ORDER * 2 - (int)rint(norm(out[i])));
                            }
                            fprintf(outb, " ");
                            writeSeq(outb, newseq);
                            fprintf(outb, "\n");
                        }
                    }

                } while(next_permutation(newseq.begin() - 1 + LEN / 2, newseq.end()));
            }
        }
    }

    printf("%llu\n", count);

    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(plan);

    fclose(outa);
    
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