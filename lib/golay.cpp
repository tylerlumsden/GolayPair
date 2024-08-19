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

std::set<std::pair<int, int>> sumoftwosquares(int constant) {
    std::set<std::pair<int, int>> solutions;
    for(int a = 0; a < constant; a++) {
        for(int b = a; b < constant; b++) {
            if(a * a + b * b == constant) {
                solutions.insert(make_pair(a, b));
            }
        }
    }
    return solutions;
}

int PAF(vector<int> seq, int s) { 
    int result = 0;
    for(size_t i = 0; i < seq.size(); i++) {
        result = result + (seq[i] * seq[(i + s) % seq.size()]);
    }
    return result;
}

int check_if_pair(vector<int> a, vector<int> b) {

    for(size_t i = 1; i <= a.size() / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != BOUND) {
            return 0;
        }
    }

    return 1;
}

bool double_equal(double a, int b) {
    if(abs(a - b) < 0.001) {
        return true;
    }
    return false;
}


void write_seq(FILE * out, vector<int> seq) {
    for(size_t i = 0; i < seq.size(); i++) {
        fprintf(out, "%d ", seq[i]);
    }
}
