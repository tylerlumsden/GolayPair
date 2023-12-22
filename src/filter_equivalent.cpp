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
    set<GolayPair> sequences;
    set<GolayPair> newset;

    sprintf(fname, "results/%d-pairs-found", ORDER);
    std::ifstream pairs(fname);

    if(!pairs.good()) {
        printf("Bad File.\n");
        return 0;
    }

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

        sequences.insert(seq);
    }

    printf("%lu sequences loaded.\n", sequences.size());

    printf("Constructing Generators\n");

    set<GolayPair> generators = constructGenerators();

    printf("Generating Equivalences\n");

    int count = 0;

    for(auto it = sequences.begin(); it != sequences.end();) {
        set<GolayPair> classes = generateClassPairs(generators, *it);
        count++;
        printf("%d classes generated\n", count);
        for(auto iter = std::next(it, 1); iter != sequences.end();) {
            GolayPair current = *iter;
            iter++;
            if(classes.find(current) != classes.end()) {
                sequences.erase(current);
            }
        }
        it++;
    }

    printf("%lu unique sequences found.\n", sequences.size());

    for(GolayPair seq : sequences) {
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
