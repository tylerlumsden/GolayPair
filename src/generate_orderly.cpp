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

#define LEN ORDER / COMPRESS

using namespace std;

void writeSeq(FILE * out, array<int, LEN> seq);


double norm(fftw_complex dft) {
    return dft[0] * dft[0] + dft[1] * dft[1];
}

void printArray(array<int, LEN> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
}

int main(int argc, char ** argv) {

    int flag = stoi(argv[1]);

    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * LEN);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * LEN);
    plan = fftw_plan_dft_1d(LEN, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    clock_t start = clock();

        //write classes to file
        char fname[100];
        sprintf(fname, "results/%d-unique-filtered-%d", ORDER, flag);
        FILE * outa = fopen(fname, "w");

        unsigned long long int count = 0;
        int candidates = 0;

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

        std::vector<std::vector<int>> combinations = getCombinations(LEN, alphabet);
        std::vector<std::vector<int>> rowcombo;

        for(std::vector<int> seq : combinations) {
            int sum = 0;
            for(int i = 0; i < LEN; i++) {
                sum += seq[i];
            }
            if(sum == decomps[ORDER][0][flag]) {
                rowcombo.push_back(seq);
            }
        }  

        printf("%lu candidate combinations found for sum %d\n", rowcombo.size(), decomps[ORDER][0][flag]);
        

        /*
        //calculate starting and ending sequence
        long long total = calculateBinomialCoefficient(LEN - 1, negcount - 1);
        printf("%d, total: %lld\n", flag, total);
        long long division = total / numproc;
        long long index = rank * division;
        long long endindex = (rank + 1) * division; 
        array<int, LEN> seq = getPermutationK(index, baseseq);
        array<int, LEN> endseq = getPermutationK(endindex, baseseq);
        */
        
    //array<int, LEN> test = {-1, 1, -1, 1, -1, -1, -1, -1, 1, 1, 1, 1, -1, 1, 1, 1, -1, 1, -1, 1, -1 , -1, 1, 1, 1, 1};

        printf("Generating Classes %d\n", flag);
        for(std::vector<int> base : rowcombo) {
            array<int, LEN> seq;
            for(int i = 0; i < LEN; i++) {
                seq[i] = base[i];
            }

            std::sort(seq.begin(), seq.end());

            do {


                if(count % 100000000 == 0) {
                    printf("%d | count: %llu, candidates: %d, time elapsed: %lds\n", flag, count, candidates, (clock() - start) / CLOCKS_PER_SEC);
                }
                    out = dft(seq, in, out, plan);

                    if(dftfilter(out, LEN)) {
                        if(isOrderly(seq, flag)) {

                            if(flag == 0) {
                                for(int i = 0; i < LEN / 2; i++) {
                                    fprintf(outa, "%d",    (int)rint(norm(out[i])));
                                }
                                fprintf(outa, " ");
                                writeSeq(outa, seq);
                                fprintf(outa, "\n");
                            }

                            if(flag == 1) {


                                for(int i = 0; i < LEN / 2; i++) {
                                    fprintf(outa, "%d",   ORDER * 2 - (int)rint(norm(out[i])));
                                }
                                fprintf(outa, " ");
                                writeSeq(outa, seq);
                                fprintf(outa, "\n");
                            }
                        }
                }
                count++;
            } while(next_permutation(seq.begin(), seq.end()));
        }

        printf("%llu\n", count);


        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(plan);

        fclose(outa);
    
}

void writeSeq(FILE * out, array<int, LEN> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        fprintf(out, "%d ", seq[i]);
    }
}

int classIsGenerated(vector<set<array<int, LEN>>>& classes, array<int, LEN>& seq) {
    for(set<array<int, LEN>> map : classes) {
        if(map.find(seq) != map.end()) {
            return 1;
        }
    }
    return 0;
}