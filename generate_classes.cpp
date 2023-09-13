#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"array.h"
#include"fftw-3.3.5-dll64/fftw3.h"
#include"decomps.h"
#include"golay.h"
#include"fourier.h"
#include"equivalence.h"

using namespace std;

void writeSeq(FILE * out, array<int, ORDER> seq);
int classIsGenerated(vector<set<array<int, ORDER>>>& classes, array<int, ORDER>& seq);

void printArray(array<int, ORDER> seq) {
    for(int i = 0; i < seq.size(); i++) {
        if(seq[i] == 1) {
            printf("+");
        }
        if(seq[i] == -1) {
            printf("-");
        }
    }
}

int main() {

    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    plan = fftw_plan_dft_1d(ORDER, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    for(int i = 0; i < decomps_len[ORDER]; i++) {
        
        vector<set<array<int, ORDER>>> classesA;
        vector<set<array<int, ORDER>>> classesB;

        array<int, ORDER> seq;
        seq.fill(-1);
        int currentSum = -ORDER;

        int SumsA = decomps[ORDER][i][0];
        int SumsB = decomps[ORDER][i][1];

        do {
            
            if(currentSum == SumsA) {
                out = dft(seq, in, out, plan);  
                if(dftfilter(out, ORDER)) {
                    if(!classIsGenerated(classesA, seq)) {
                        classesA.push_back(generateClassA(seq));
                    }
                }
            }

            if(currentSum == SumsB) {
                out = dft(seq, in, out, plan);  
                if(dftfilter(out, ORDER)) {
                    if(!classIsGenerated(classesB, seq)) {
                        classesB.push_back(generateClassB(seq));
                    }
                }
                printArray(seq);
                printf("\n");
            }
            
        } while(NextCombinationRowSums(seq, ORDER, &currentSum));

        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(plan);

        //write classesA to file
        char fname[100];
        sprintf(fname, "results/%d-unique-filtered-a-%d", ORDER, i);
        FILE * out = fopen(fname, "w");

        for(set<array<int,ORDER>> set : classesA) {
            writeSeq(out, *(set.begin()));
            fprintf(out, "\n");
        }

        fclose(out);

        //write classesB to file
        sprintf(fname, "results/%d-unique-filtered-b-%d", ORDER, i);
        out = fopen(fname, "w");

        for(set<array<int,ORDER>> set : classesB) {
            writeSeq(out, *(set.begin()));
            fprintf(out, "\n");
        }

        fclose(out);
    }
    
}

void writeSeq(FILE * out, array<int, ORDER> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        if(seq[i] == 1) {
            fprintf(out, "+");
        }
        if(seq[i] == -1) {
            fprintf(out, "-");
        }
    }
}

int classIsGenerated(vector<set<array<int, ORDER>>>& classes, array<int, ORDER>& seq) {
    for(set<array<int, ORDER>> map : classes) {
        if(map.find(seq) != map.end()) {
            return 1;
        }
    }
    return 0;
}