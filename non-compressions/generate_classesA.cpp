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

        //write classesA to file
        char fname[100];
        sprintf(fname, "results/%d-unique-filtered-a-%d", ORDER, i);
        FILE * outa = fopen(fname, "w");

        set<array<int, ORDER>> classesA;

        array<int, ORDER> seq;
        int negcounta = (ORDER - decomps[ORDER][i][0]) / 2;
        seq.fill(1);

        unsigned long long int count = 0;
        int candidates = 0;

        for(int i = 0; i < negcounta; i++) {
            seq[i] = -1;
        }

        printf("Generating Classes A\n");

        do {
            if(count % 100000000 == 0) {
                printf("A | count: %llu, candidates: %d, time elapsed: %lds\n", count, candidates, (clock() - start) / CLOCKS_PER_SEC);
            }
            out = dft(seq, in, out, plan);  
            if(dftfilter(out, ORDER)) {
                if(classesA.find(seq) == classesA.end()) {
                    candidates++;
                    set<array<int, ORDER>> classa = generateClassA(seq);
                    classesA.insert(classa.begin(), classa.end());
                    for(int i = 0; i < ORDER / 2; i++) {
                        fprintf(outa, "%d",    (int)rint(norm(out[i])));
                    }
                    fprintf(outa, " ");
                    writeSeq(outa, seq);
                    fprintf(outa, "\n");
                }
            }
            count++;
        } while(next_permutation(seq.begin(), seq.end()) && seq[0] != 1);


        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(plan);

        fclose(outa);
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