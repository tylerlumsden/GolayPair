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

using namespace std;

int main(int argc, char ** argv) {

    int ORDER = stoi(argv[1]);
    int LEN = stoi(argv[2]);
    int NEWCOMPRESS = stoi(argv[3]);

    char fname[100];
    sprintf(fname, "results/%d-pair-%d", ORDER, LEN);
    FILE * in = fopen(fname, "r");

    char fname[100];
    sprintf(fname, "results/%d-pair-%d", ORDER, LEN / NEWCOMPRESS);
    FILE * in = fopen(fname, "w");

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

    for(int i = 0; i < LEN; i++) {
        pairs >> a;
        seqa[i] = stoi(a);
    }

    for(int i = 0; i < LEN; i++) {
        pairs >> b;
        seqb[i] = stoi(b);
    }

    for(int i = 0; i < LEN / NEWCOMPRESS; i++) {
        for(int j = 0; j < NEWCOMPRESS; i++) {
            int sum = 0;

            sum += a[i + j * (LEN / NEWCOMPRESS)];
        }

        fprintf(out, "%d ", sum);
    }

    for(int i = 0; i < LEN / NEWCOMPRESS; i++) {
        for(int j = 0; j < NEWCOMPRESS; i++) {
            int sum = 0;

            sum += b[i + j * (LEN / NEWCOMPRESS)];
        }

        fprintf(out, "%d ", sum);
    }
    fprintf(out, "\n");


}
