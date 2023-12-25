#include<stdio.h>
#include<set>
#include<array>
#include<vector>
#include"golay.h"
#include"coprimes.h"
#include<algorithm>
#include<iostream>

using namespace std;
 
int shift_equivalence(set<vector<int>>& map, vector<int> base);
int decimation_equivalence(set<vector<int>>& map, vector<int> base);
int reverse_equivalence(set<vector<int>>& map, vector<int> base);
set<vector<int>> generateExhaust(vector<int> base, int flag);

set<vector<int>> constructGenerators(int flag) {
    vector<int> seq;
    seq.resize(LEN);

    for(int i = 1; i <= LEN; i++) {
        seq[i - 1] = i;
    }


    return generateExhaust(seq, flag);
} 

set<vector<int>> generateExhaust(vector<int> base, int flag) {
    set<vector<int>> map;


    unsigned int size = 0;

    map.insert(base);

    while(map.size() != size) {
        size = map.size();

        if(flag == 0) {
            decimation_equivalence(map, base);
        }

        shift_equivalence(map, base);
       
        reverse_equivalence(map, base);
    }

    return map;
}

int isCanonical(vector<int> seq, set<vector<int>> generators) {

    vector<int> newseq;
    newseq.resize(LEN);

    for(vector<int> item : generators) {
        for(int i = 0; i < LEN; i++) {
            newseq[i] = seq[item[i] - 1];
        }
        if(newseq < seq) {
            return 0;
        }
    }
    return 1;
}

bool partialCanonical(vector<int> base) {
    vector<int> seq = base;
    while(seq.size() != 0) {
        seq.erase(seq.begin());

        for(unsigned int i = 0; i < seq.size(); i++) {
            if(seq[i] < base[i]) {
                return false;
            } else if(seq[i] == base[i]) {
                continue;
            } else {
                break;
            }
        }
    }
    return true;
}

int shift_equivalence(set<vector<int>>& map, vector<int> base) {
    for(vector<int> seq: map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            rotate(seq.begin(), seq.begin() + 1, seq.end());

            map.insert(seq);
        }
    }
    return 1;
}

int reverse_equivalence(set<vector<int>>& map, vector<int> base) {
    for(vector<int> seq: map) { 
        reverse(seq.begin(), seq.end());

        if(seq < base) {
            return 0;
        }

        map.insert(seq);
    }
    return 1;
}

vector<int> permute(vector<int> seq, int coprime) {
    vector<int> newseq;
    newseq.resize(LEN);
    for(int i = 0; i < LEN; i++) {
        newseq[i] = seq[(i * coprime) % (LEN)];
    }
    return newseq;
}

int decimation_equivalence(set<vector<int>>& map, vector<int> base) {

    for(vector<int> seq : map) {
        for(int i = 0; i < coprimelength[LEN]; i++) {

            vector<int> newseq = permute(seq, coprimelist[LEN][i]);

            if(newseq < base) {
                return 0;
            }
            
            map.insert(newseq);
        }
    }
    return 1;
}