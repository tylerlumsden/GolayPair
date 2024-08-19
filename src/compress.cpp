#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<array>
#include<vector>
#include<set>
#include<time.h>
#include<string>
#include<fstream>
#include<iostream>
#include<map>
#include"../lib/golay.h"
#include"../lib/fourier.h"
#include"fftw3.h"

using namespace std;

int main(int argc, char ** argv) {
    

    int ORDER = stoi(argv[1]);
    int LEN = stoi(argv[2]);
    int NEWCOMPRESS = stoi(argv[3]);

    fftw_complex *input, *output;
    fftw_plan plan;

    input = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * LEN);
    output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * LEN);
    plan = fftw_plan_dft_1d(LEN, input, output, FFTW_FORWARD, FFTW_ESTIMATE);

    char fname[100];
    sprintf(fname, "results/%d-unique-pairs-found", ORDER);
    std::ifstream in(fname);

    sprintf(fname, "results/%d-%d-compressions", ORDER, NEWCOMPRESS);
    FILE * out = fopen(fname, "w");

    if(!in.good()) {
        printf("Bad File.\n");
        return 0;
    }

    vector<int> seqa;
    vector<int> seqb;
    seqa.resize(LEN);
    seqb.resize(LEN);

    std::string a;
    std::string b;

    std::map<GolayPair, int> compresscount;

    while(in.good()) {

        GolayPair seq;
        seq.a.resize(ORDER / NEWCOMPRESS);
        seq.b.resize(ORDER / NEWCOMPRESS);

        for(int i = 0; i < LEN; i++) {
            in >> a;
            seqa[i] = stoi(a);
        }

        if(!in.good()) {
            break;
        }

        for(int i = 0; i < LEN; i++) {
            in >> b;
            seqb[i] = stoi(b);
        }

        output = dft(seqa, input, output, plan);
        output = dft(seqb, input, output, plan);

        for(int i = 0; i < LEN / NEWCOMPRESS; i++) {
            int sum = 0;
            for(int j = 0; j < NEWCOMPRESS; j++) {
                sum += seqa[i + j * (LEN / NEWCOMPRESS)];
            }

            seq.a[i] = sum;
        }


        for(int i = 0; i < LEN / NEWCOMPRESS; i++) {
            int sum = 0;
            for(int j = 0; j < NEWCOMPRESS; j++) {
                sum += seqb[i + j * (LEN / NEWCOMPRESS)];

            }

            seq.b[i] = sum;
        }


        if(compresscount.count(seq)) {
            compresscount[seq]++;
        } else {
            compresscount.insert(make_pair(seq, 1));
        }
    }



    for(std::pair count : compresscount) {

        GolayPair seq = count.first;
        int num = count.second;

        for(unsigned int i = 0; i < seq.a.size(); i++) {
            fprintf(out, "%d ", seq.a[i]);
        }

        fprintf(out, " ");

        for(unsigned int i = 0; i < seq.b.size(); i++) {
            fprintf(out, "%d ", seq.b[i]);
        }
        fprintf(out, " %d\n", num);
    }

    
    fftw_free(input);
    fftw_free(output);
    fftw_destroy_plan(plan);
}

