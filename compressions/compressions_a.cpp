
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<algorithm>
#include<time.h>
#include"../array.h"
#include"../fftw-3.3.5-dll64/fftw3.h"
#include"../golay.h"
#include"../fourier.h"
#include"../equivalence.h"
#include<tgmath.h>
#include<fstream>
#include<iostream>


using namespace std;

int classIsGenerated(vector<set<array<int, ORDER>>>& classes, array<int, ORDER>& seq) {
    for(set<array<int, ORDER>> map : classes) {
        if(map.find(seq) != map.end()) {
            return 1;
        }
    }
    return 0;
}

double norm(fftw_complex num) {
    return (num[0] * num[0]) + (num[1] * num[1]);
}

int rowsum(array<int, ORDER> seq) {
    int sum = 0;
    for(int i = 0; i < ORDER; i++) {
        sum += seq[i];
    }
    return sum;
}

int main() {

    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    plan = fftw_plan_dft_1d(ORDER, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    array<int, ORDER> seq;
    seq.fill(-1);

    for(int i = 0; i < 7; i++) {
        seq[i] = -3;
    }

    vector<set<array<int, ORDER>>> classes;

    FILE * outfile = fopen("compressions.a", "a+");

    if(outfile) {

        printf("Regenerating Classes...\n");

        std::ifstream filea("compressions.a");
        std::string a;

        filea >> a;

        while(filea.good()) {

            for(int i = 0; i < 30; i++) {
                filea >> a;
                seq[i] = stoi(a);
            }
            filea >> a;
            classes.push_back(generateClassA(seq));
        }
    }

    printf("Generating new candidates...\n");

    do {
        if(rowsum(seq) == 6) {
            do {
                out = dft(seq, in, out, plan);  
                if(dftfilter(out, ORDER)) {
                    if(!classIsGenerated(classes, seq)) {
                        classes.push_back(generateClassA(seq));
                        fprintf(outfile, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", (int)rint(norm(out[1])), (int)rint(norm(out[2])), (int)rint(norm(out[3])), (int)rint(norm(out[4])), (int)rint(norm(out[5])), (int)rint(norm(out[6])), (int)rint(norm(out[7])), (int)rint(norm(out[8])), (int)rint(norm(out[9])), (int)rint(norm(out[10])), (int)rint(norm(out[11])), (int)rint(norm(out[12])), (int)rint(norm(out[13])), (int)rint(norm(out[14])), (int)rint(norm(out[15])),  seq[0], seq[1],seq[2],seq[3],seq[4],seq[5],seq[6],seq[7],seq[8],seq[9],seq[10],seq[11],seq[12],seq[13],seq[14],seq[15],seq[16],seq[17],seq[18],seq[19],seq[20],seq[21],seq[22],seq[23],seq[24],seq[25],seq[26],seq[27],seq[28],seq[29]);
                    }
                }
                
            } while(next_permutation(seq.begin(), seq.end()));
        }
    } while(nextCombinationA(seq));


    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(plan);
}

