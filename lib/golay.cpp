#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"golay.h"

using namespace std;



int PAF(vector<int> seq, int s) { 
    int result = 0;
    for(size_t i = 0; i < seq.size(); i++) {
        result = result + (seq[i] * seq[(i + s) % seq.size()]);
    }
    return result;
}

int check_if_pair(vector<int> a, vector<int> b) {
    for(size_t i = 1; i <= a.size() / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != 0) {
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
