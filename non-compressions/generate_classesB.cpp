#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"../array.h"
#include"../fftw-3.3.10/api/fftw3.h"
#include"../decomps.h"
#include"../golay.h"
#include"../fourier.h"
#include"../equivalence.h"
#include<tgmath.h>
#include<algorithm>

using namespace std;

void writeSeq(FILE * out, array<int, ORDER> seq);
int classIsGenerated(vector<set<array<int, ORDER>>>& classes, array<int, ORDER>& seq);

double norm(fftw_complex dft) {
    return dft[0] * dft[0] + dft[1] * dft[1];
}

void printArray(array<int, ORDER> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
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

    clock_t start = clock();

    for(int i = 0; i < decomps_len[ORDER]; i++) {

        //write classesB to file
        char fname[100];
        sprintf(fname, "results/%d-unique-filtered-b-%d", ORDER, i);
        FILE * outb = fopen(fname, "w");

        set<array<int, ORDER>> classesB;

        array<int, ORDER> seq;

        unsigned long long int count = 0;
        int candidates = 0;


        seq.fill(1);
        int negcountb = (ORDER - decomps[ORDER][i][1]) / 2;
        for(int i = 0; i < negcountb; i++) {
            seq[i] = -1;
        }

        count = 0;

        printf("Generating Classes B\n");

        do {
            if(count % 100000000 == 0) {
                printf("B | count: %llu, candidates: %d, time elapsed: %lds\n", count, candidates, (clock() - start) / CLOCKS_PER_SEC);
            }
            out = dft(seq, in, out, plan);  
            if(dftfilter(out, ORDER)) {
                if(classesB.find(seq) == classesB.end()) {
                    candidates++;
                    set<array<int, ORDER>> classb = generateClassB(seq);
                    classesB.insert(classb.begin(), classb.end());
                    for(int i = 0; i < ORDER / 2; i++) {
                        fprintf(outb, "%d",    ORDER * 2 - (int)rint(norm(out[i])));
                    }
                    fprintf(outb, " ");
                    writeSeq(outb, seq);
                    fprintf(outb, "\n");
                }
            }
            count++;
        } while(next_permutation(seq.begin(), seq.end()) && seq[0] != 1);

        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(plan);

        fclose(outb);
    }
    
}

void writeSeq(FILE * out, array<int, ORDER> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        fprintf(out, "%d ", seq[i]);
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