#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<array>
#include<vector>
#include<set>
#include<time.h>
#include<string>
#include<fstream>
#include"../lib/golay.h"
#include"../lib/equivalence.h"

using namespace std;

GolayPair strToPair(std::string a, std::string b) {
    array<int, LEN> seqa;
    array<int, LEN> seqb;
    for(int i = 0; i < LEN; i++) {
        seqa[i] = int(a[i]);

        seqb[i] = int(b[i]);
    }

    GolayPair seq;
    seq.a = seqa;
    seq.b = seqb;

    return seq;
}

int main() {

    printf("Filtering Equivalent Pairs...\n");

    char fname[100];
    sprintf(fname, "results/%d-unique-pairs-found", ORDER);
    FILE * out = fopen(fname, "w");

    //match every seq a with seq b, generate an equivalence class for this sequence 
    
    set<GolayPair> classes;

    sprintf(fname, "results/%d-pairs-found", ORDER);
    std::ifstream pairs(fname);

    std::string a;
    std::string b;

    while(pairs.good()) {

        GolayPair seq;

        for(int i = 0; i < LEN; i++) {
            pairs >> a;
            seq.a[i] = stoi(a);
        }

        for(int i = 0; i < LEN; i++) {
            pairs >> b;
            seq.b[i] = stoi(b);
        }

        if(classes.find(seq) == classes.end()) {
            set<GolayPair> equiv = generateClassPairs(seq);

            classes.insert(equiv.begin(), equiv.end());

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
}
