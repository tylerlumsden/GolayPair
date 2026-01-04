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
#include"golay.h"
#include"equivalence.h"

using namespace std;

int canon_filter(const int ORDER, const int COMPRESS) {
    const int LEN = ORDER / COMPRESS;

    FILE * out;
    char fname[100];

    sprintf(fname, "results/%d-unique-pairs-found", ORDER);
    out = fopen(fname, "w");

    sprintf(fname, "results/order-%d/%d-pairs-found_1", ORDER, ORDER);
    std::ifstream pairs(fname);

    if(!pairs.good()) {
        printf("Bad File.\n");
        return 0;
    }

    printf("Filtering Equivalent Pairs...\n");


    //match every seq a with seq b, generate an equivalence class for this sequence 
    
    set<GolayPair> classes;
    set<GolayPair> sequences;
    set<GolayPair> newset;

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

        if(count % 1 == 0) {
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

    return 0;
}

int cache_filter(const int ORDER, const int COMPRESS) {
    const int LEN = ORDER / COMPRESS;

    printf("Filtering Equivalent Pairs...\n");

    char fname[100];
    sprintf(fname, "results/%d-unique-pairs-found", ORDER);
    FILE * out = fopen(fname, "w");

    //match every seq a with seq b, generate an equivalence class for this sequence 
    
    set<GolayPair> classes;
    set<GolayPair> sequences;
    set<GolayPair> newset;

    sprintf(fname, "results/order-%d/%d-pairs-found_1", ORDER, ORDER);
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

    while(pairs.good()) {

        for(int i = 0; i < LEN; i++) {
            pairs >> a;
            seq.a[i] = stoi(a);
        }

        if(!pairs.good()) {
            break;
        }

        for(int i = 0; i < LEN; i++) {
            pairs >> b;
            seq.b[i] = stoi(b);
        }

        sequences.insert(seq);
    }

    printf("%lu sequences loaded.\n", sequences.size());

    printf("Constructing Generators\n");

    set<GolayPair> generators = constructGenerators(LEN);

    printf("Generating Equivalences\n");

    int count = 0;
/*
    set<GolayPair> equiv;

    auto prev = sequences.begin();
    auto it = sequences.begin();
    it++;
    while(it != sequences.end()) {

        if(equiv.find(*it) != equiv.end()) {
            sequences.erase(*it);
            
            it = prev;
        } else {
            set<GolayPair> classes = generateClassPairs(generators, *it);
            equiv.insert(classes.begin(), classes.end());
            count++;
            printf("%d classes generated\n", count);

            prev = it;
        }

        it++;
    }
*/

    for(auto it = sequences.begin(); it != sequences.end();) {
        set<GolayPair> classes = generateClassPairs(generators, *it);
        count++;
        printf("%d classes generated\n", count);

        if(classes.size() > sequences.size()) {

            for(auto iter = std::next(it, 1); iter != sequences.end();) {
                GolayPair current = *iter;
                iter++;
                if(classes.find(current) != classes.end()) {
                    sequences.erase(current);
                }
            }
            printf("Filtered. Size: %lu\n", sequences.size());
            it++;
        } else {
            set<GolayPair> newset;
            GolayPair base = *it;
            for(GolayPair seq : classes) {
                sequences.erase(seq);
            }
            sequences.insert(base);
            printf("Classwise filter. Size: %lu\n", sequences.size());
            it = sequences.find(base);
            it++;
        }
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

    return 0;
}