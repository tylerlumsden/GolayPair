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
#include"../lib/golay.h"
#include"../lib/equivalence.h"

using namespace std;

int main(int argc, char ** argv) {

    int ORDER = stoi(argv[1]);
    int LEN = stoi(argv[2]);
    int proc = stoi(argv[3]);

    printf("Filtering Equivalent Pairs...\n");

    char fname[100];
    sprintf(fname, "results/%d-unique-pairs-found-%d", ORDER, proc);
    FILE * out = fopen(fname, "w");

    //match every seq a with seq b, generate an equivalence class for this sequence 
    
    set<GolayPair> classes;
    set<GolayPair> sequences;
    set<GolayPair> newset;

    sprintf(fname, "results/%d-pairs-found-%d", ORDER, proc);
    std::ifstream pairs(fname);

    if(!pairs.good()) {
        printf("Bad File.\n");
        return 0;
    }

    std::string a;
    std::string b;

    GolayPair seq;
    seq.a.resize(LEN);
    seq.b.resize(LEN);

    set<GolayPair> generators = constructGenerators(LEN);

    printf("Generating Equivalences\n");

    unsigned long long count = 0;

    while(pairs.good()) {
        for(int i = 0; i < LEN; i++) {
            pairs >> a;
            seq.a[i] = stoi(a);
        }

        for(int i = 0; i < LEN; i++) {
            pairs >> b;
            seq.b[i] = stoi(b);
        }

        if(!pairs.good()) {
            break;
        }

        set<GolayPair> classes = generateClassPairs(generators, seq);
        count++;

        seq = *classes.begin();

        if(count % 1000 == 0) {
            printf("%llu classes generated\n", count);
        }

        for(int i = 0; i < LEN; i++) {
            fprintf(out, "%d ", seq.a[i]);
        }

        fprintf(out, " ");

        for(int i = 0; i < LEN; i++) {
            fprintf(out, "%d ", seq.b[i]);
        }

        fprintf(out, "\n");

    }
}
