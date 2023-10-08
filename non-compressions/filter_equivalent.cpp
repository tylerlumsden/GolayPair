#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<array>
#include<vector>
#include<set>
#include<time.h>
#include<string>
#include<fstream>
#include"../golay.h"
#include "../equivalence.h"

using namespace std;

GolayPair strToPair(std::string a, std::string b) {
    array<int, ORDER> seqa;
    array<int, ORDER> seqb;
    for(int i = 0; i < ORDER; i++) {
        if(a[i] == '+') {
            seqa[i] = 1;
        }
        if(a[i] == '-') {
            seqa[i] = -1;
        }

        if(b[i] == '+') {
            seqb[i] = 1;
        }
        if(b[i] == '-') {
            seqb[i] = -1;
        }
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
        pairs >> a;
        pairs >> b;

        GolayPair seq = strToPair(a, b);

        if(classes.find(seq) == classes.end()) {
            vector<GolayPair> equiv = generateClassPairs(seq);

            classes.insert(equiv.begin(), equiv.end());

            for(int i = 0; i < ORDER; i++) {
                if(seq.a[i] == 1) {
                    fprintf(out, "+");
                }
                if(seq.a[i] == -1) {
                    fprintf(out, "-");
                }
            }

            fprintf(out, " ");

            for(int i = 0; i < ORDER; i++) {
                if(seq.b[i] == 1) {
                    fprintf(out, "+");
                }
                if(seq.b[i] == -1) {
                    fprintf(out, "-");
                }
            }

            fprintf(out, "\n");
        }
    }
}
