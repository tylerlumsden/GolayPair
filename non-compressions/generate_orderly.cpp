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
#include"../orderly_equivalence.h"
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
        printf("%d ", seq[i]);
    }
}

int main(int argc, char ** argv) {

    int flag = stoi(argv[1]);
    int rank = stoi(argv[2]);
    int numproc = stoi(argv[3]);

    array<int, ORDER> seq;

    if(flag == 0) {
        seq = seqA;
    }
    if(flag == 1) {
        seq = seqB;
    }

    printf("Process Number: %d, Total Processes: %d\n", rank, numproc);

    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    plan = fftw_plan_dft_1d(ORDER, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    clock_t start = clock();

        //write classes to file
        char fname[100];
        sprintf(fname, "results/%d-filtered-%d-%d", LEN, flag, rank);
        FILE * outa = fopen(fname, "w");

        unsigned long long int count = 0;

        printf("Generating Classes %d\n", flag);

        printf("%d Base sequence: ", flag);
        printArray(seq);
        printf("\n");

        do {
            if(count % 100000000 == 0) {
                printf("%d | count: %llu, time elapsed: %lds\n", flag, count, (clock() - start) / CLOCKS_PER_SEC);
            }
            if((count % numproc) == rank) {
                out = dft(seq, in, out, plan);  
                if(dftfilter(out, ORDER)) {
                    if(generateClass(seq, flag)) {

                        if(flag == 0) {
                                
                            for(int i = 0; i < ORDER / 2; i++) {
                                fprintf(outa, "%d",    (int)rint(norm(out[i])));
                            }
                            fprintf(outa, " ");
                            writeSeq(outa, seq);
                            fprintf(outa, "\n");
                        }

                        if(flag == 1) {


                            for(int i = 0; i < ORDER / 2; i++) {
                                fprintf(outa, "%d",   LEN * 2 - (int)rint(norm(out[i])));
                            }
                            fprintf(outa, " ");
                            writeSeq(outa, seq);
                            fprintf(outa, "\n");
                        }
                    }
                }
            }
            count++;
        } while(next_permutation(seq.begin(), seq.end()));


        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(plan);

        fclose(outa);
    
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