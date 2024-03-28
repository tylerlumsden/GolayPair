#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"golay.h"

using namespace std;

#define BOUND 0



int PAF(vector<int> seq, int s) { 
    int result = 0;
    for(size_t i = 0; i < seq.size(); i++) {
        result = result + (seq[i] * seq[(i + s) % seq.size()]);
    }
    return result;
}

int check_if_pair(vector<int> a, vector<int> b) {

    for(int i = 0; i < a.size(); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    for(int i = 0; i < a.size(); i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    for(size_t i = 1; i <= a.size() / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != BOUND) {
            return 0;
        }
    }

    return 1;
}


void write_seq(FILE * out, vector<int> seq) {
    for(size_t i = 0; i < seq.size(); i++) {
        fprintf(out, "%d ", seq[i]);
    }
}
