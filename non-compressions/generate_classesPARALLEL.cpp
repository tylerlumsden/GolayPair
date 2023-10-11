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
#include<omp.h>


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

int main(int argc, char ** argv) {

    int flag = stoi(argv[1]);

    clock_t start = clock();

    for(int i = 0; i < decomps_len[ORDER]; i++) {

        //write classes to file
        char fname[100];
        sprintf(fname, "results/%d-unique-filtered-%d-%d", ORDER, flag, i);
        FILE * outa = fopen(fname, "w");

        set<array<int, ORDER>> classes;

        #pragma omp parallel 
        {


            fftw_complex *in, *out;
            fftw_plan plan;

            in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
            out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);

            #pragma omp critical 
            {
                plan = fftw_plan_dft_1d(ORDER, in, out, FFTW_FORWARD, FFTW_PATIENT);
            }


            array<int, ORDER> seq;
            int negcount = (ORDER - decomps[ORDER][i][flag]) / 2;
            seq.fill(1);

            unsigned long long int count = 0;
            int candidates = 0;

            for(int i = 0; i < negcount; i++) {
                seq[i] = -1;
            }

            printf("Generating Classes %d\n", flag);

            int id = omp_get_thread_num();
            int threads = omp_get_num_threads();

            count = id;

            do {
                if(count % threads == 0) {
                    if(count % 100000000 == 0) {
                        printf("%d | count: %llu, candidates: %d, time elapsed: %lds\n", flag, count, candidates, (clock() - start) / CLOCKS_PER_SEC);
                    }
                    out = dft(seq, in, out, plan);  
                    if(dftfilter(out, ORDER)) {
                        if(classes.find(seq) == classes.end()) {
                            candidates++;
                            vector<array<int, ORDER>> equiv;
                            equiv = generateClass(seq, flag);

                            #pragma omp critical 
                            {
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
                                        fprintf(outa, "%d",   ORDER * 2 - (int)rint(norm(out[i])));
                                    }
                                    fprintf(outa, " ");
                                    writeSeq(outa, seq);
                                    fprintf(outa, "\n");
                                }
                                
                                classes.insert(equiv.begin(), equiv.end());
                            }
                        }
                    }
                }
                count++;
            } while(next_permutation(seq.begin(), seq.end()) && seq[0] != 1);
            fftw_free(in);
            fftw_free(out);

            #pragma omp critical 
            {
                fftw_destroy_plan(plan);
            }

        }

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