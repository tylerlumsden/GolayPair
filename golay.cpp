#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"array.h"
#include"decomps.h"
#include"golay.h"
#include"fourier.h"
#include"equivalence.h"

using namespace std;


int PAF(array<int, ORDER> seq, int s) { 
    int result = 0;
    for(int i = 0; i < ORDER; i++) {
        result = result + (seq[i] * seq[(i + s) % ORDER]);
    }
    return result;
}

int check_if_pair(array<int, ORDER> a, array<int, ORDER> b) {
    for(int i = 1; i <= ORDER / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != 0) {
            return 0;
        }
    }

    return 1;
}

void fill_from_string(array<int, ORDER>& seq, char str[]) {
    for(int i = 0; i < ORDER; i++) {
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

void write_seq(FILE * out, array<int, ORDER> seq) {
    for(int i = 0; i < ORDER; i++) {
        if(seq[i] == 1) {
            fprintf(out, "+");
            continue;
        }
        if(seq[i] == -1) {
            fprintf(out, "-");
            continue;
        }
    }
}
