#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"golay.h"

using namespace std;



int PAF(array<int, LEN> seq, int s) { 
    int result = 0;
    for(int i = 0; i < LEN; i++) {
        result = result + (seq[i] * seq[(i + s) % (LEN)]);
    }
    return result;
}

int check_if_pair(array<int, LEN> a, array<int, LEN> b) {
    for(int i = 1; i <= (LEN) / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != 0) {
            return 0;
        }
    }

    return 1;
}

void fill_from_string(array<int, LEN>& seq, char str[]) {
    for(int i = 0; i < LEN; i++) {
        if(str[i] == '+') {
            seq[i] = 1;
            continue;
        } 
        if(str[i] == '-') {
            seq[i] = -1;
            continue;
        }
    }
}

void write_seq(FILE * out, array<int, LEN> seq) {
    for(int i = 0; i < LEN; i++) {
        fprintf(out, "%d ", seq[i]);
    }
}
