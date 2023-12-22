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

int isOrderly(vector<int> base) {
    set<vector<int>> map;
    set<vector<int>> equiv;

    unsigned int size = 0;

    map.insert(base);

    while(map.size() != size) {
        size = map.size();

        if(!shift_equivalence(map, base)) {
            return 0;
        }

    }

    return 1;
}

int shift_equivalence(set<vector<int>>& map, vector<int> base) {
    for(vector<int> seq : map) {
        while(seq.size() != 0) {
            seq.erase(seq.begin());

            for(unsigned int i = 0; i < seq.size(); i++) {
                if(seq[i] < base[i]) {
                    return 0;
                } else if(seq[i] == base[i]) {
                    continue;
                } else {
                    break;
                }
            }
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