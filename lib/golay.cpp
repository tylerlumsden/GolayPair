#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"golay.h"
#include<iostream>

#include <fstream>

using namespace std;

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

int check_if_pair(vector<int> a, vector<int> b, const int PAF_CONSTANT, const int COMPRESS) {

    for(size_t i = 1; i <= a.size() / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != PAF_CONSTANT * COMPRESS) {
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


void write_seq(std::ofstream& out, vector<int> seq) {
    for(size_t i = 0; i < seq.size(); i++) {
        out << seq[i] << " ";
    }
}

std::set<int> getalphabet(const int COMPRESS) {
    std::set<int> alphabet;
    if(COMPRESS % 2 == 0) {
        for(int i = 0; i <= COMPRESS; i += 2) {
            alphabet.insert(i);
            alphabet.insert(-i);
        }
    } else {
        for(int i = 1; i <= COMPRESS; i += 2) {
            alphabet.insert(i);
            alphabet.insert(-i);
        }
    }

    return alphabet;
}
