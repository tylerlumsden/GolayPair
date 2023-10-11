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
#include<mpi.h>

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

    int numproc;
    int rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &numproc);

    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    printf("%d %d\n", numproc, rank);

    int flag = stoi(argv[1]);

    if(rank == 0) {

        char fname[100];
        sprintf(fname, "results/%d-unique-filtered-%d-%d", ORDER, flag, 0);
        FILE * outa = fopen(fname, "w");

        set<array<int, ORDER>> classes;
        int finishcount = 0;
        while(finishcount != numproc - 1) {
            MPI_Status status;
            array<int, ORDER> seq;
            vector<array<int, ORDER>> equiv;
            equiv.resize(512);

            MPI_Recv(&seq[0], ORDER, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if(status.MPI_TAG == 0) {
                finishcount++;
                printf("Process %d has completed\n", status.MPI_SOURCE);
                continue;
            }

            if(classes.find(seq) == classes.end()) {
                MPI_Send(0, 0, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);

                MPI_Recv(&equiv[0], 100000, MPI_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

                /*
                for(array<int, ORDER> arr : equiv) {
                    for(int i = 0; i < ORDER; i++) {
                        printf("%d", arr[i]);
                    }
                    printf("\n");
                } 
                printf("\n");
                */
                

                classes.insert(equiv.begin(), equiv.end());

                if(flag == 0) {

                    fprintf(outa, " ");
                    writeSeq(outa, seq);
                    fprintf(outa, "\n");
                }

                if(flag == 1) {

                    fprintf(outa, " ");
                    writeSeq(outa, seq);
                    fprintf(outa, "\n");
                }

            } else {
                
                MPI_Send(0, 0, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                continue;
            }
        }
        MPI_Finalize();
    } else {

    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    plan = fftw_plan_dft_1d(ORDER, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    clock_t start = clock();

    for(int i = 0; i < decomps_len[ORDER]; i++) {

        array<int, ORDER> seq;
        int negcount = (ORDER - decomps[ORDER][i][flag]) / 2;
        seq.fill(1);

        unsigned long long int count = 0;
        int candidates = 0;

        for(int i = 0; i < negcount; i++) {
            seq[i] = -1;
        }

        printf("Generating Classes %d\n", flag);

        do {
            if(count % rank == 0) {
                if(count % 100000000 == 0) {
                    printf("%d | count: %llu, candidates: %d, time elapsed: %lds\n", flag, count, candidates, (clock() - start) / CLOCKS_PER_SEC);
                }
                out = dft(seq, in, out, plan);  
                if(dftfilter(out, ORDER)) {
                    MPI_Status status;
                    MPI_Send(&seq[0], seq.size(), MPI_INT, 0, 1, MPI_COMM_WORLD);
                    MPI_Recv(0, 0, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

                    if(status.MPI_TAG == 1) {
                        candidates++;
                        vector<array<int, ORDER>> equiv;
                        equiv = generateClass(seq, flag);
                        
                        MPI_Send(&equiv[0], equiv.size() * ORDER, MPI_INT, 0, 1, MPI_COMM_WORLD);
                    }
                }
            }
            count++;
        } while(next_permutation(seq.begin(), seq.end()) && seq[0] != 1);

        MPI_Send(0, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);

        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(plan);

        MPI_Finalize();
    }
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