#include<stdio.h>
#include<set>
#include<array>
#include<vector>
#include"golay.h"
#include"coprimes.h"
#include<algorithm>
#include<iostream>

using namespace std;

void shift_equivalence(set<array<int,LEN>>& map);
void negative_equivalence(set<array<int,LEN>>& map);
void altnegative_equivalence(set<array<int,LEN>>& map);
void unishift_equivalence(set<array<int,LEN>>& map, array<int,LEN> seq);
void decimation_equivalence(set<array<int, LEN>>& map);
void reverse_equivalence(set<array<int, LEN>>& map);
void shift_pair(set<GolayPair>& map);
void decimate_pair(set<GolayPair>& map);
void reverse_pair(set<GolayPair>& map);
void altnegative_pair(set<GolayPair>& map);
void negate_pair(set<GolayPair>& map);
void swap_pair(set<GolayPair>& map);

set<GolayPair> generateClassPairs(GolayPair seq) {
    set<GolayPair> map;

    unsigned int size = 0;

    map.insert(seq);

    while(map.size() != size) {
        size = map.size();

        shift_pair(map);
        altnegative_pair(map);
        reverse_pair(map);
        decimate_pair(map);
        swap_pair(map);
        printf("%d\n", size);
    }

    return map;
}

vector<array<int, LEN>> generateClass(array<int, LEN> seq, int flag) {
    set<array<int, LEN>> map;

    unsigned int size = 0;

    map.insert(seq);

    while(map.size() != size) {
        size = map.size();

        if(flag == 0) {
            decimation_equivalence(map);
        }

        shift_equivalence(map);  
        reverse_equivalence(map);
    }

    vector<array<int, LEN>> out;

    for(array<int, LEN> seq : map) {
        out.push_back(seq);
    }

    return out;
}

void swap_pair(set<GolayPair>& map) {
    for(GolayPair seq : map) {
        array<int, LEN> temp = seq.a;
        seq.a = seq.b;
        seq.b = temp;

        map.insert(seq);
    }
}


void shift_pair(set<GolayPair>& map) {
    for(GolayPair seq: map) {
        for(unsigned int j = 0; j < LEN; j++) {
            rotate(seq.b.begin(), seq.b.begin() + 1, seq.b.end());
            map.insert(seq);
        }
    }
}

void shift_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq: map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            rotate(seq.begin(), seq.begin() + 1, seq.end());
            map.insert(seq);
        }
    }
}

void reverse_pair(set<GolayPair>& map) {
    for(GolayPair seq: map) { 

        reverse(seq.b.begin(), seq.b.end());
        map.insert(seq);

    }
}

void reverse_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq: map) { 
        reverse(seq.begin(), seq.end());

        map.insert(seq);
    }
}

void negate_pair(set<GolayPair>& map) {
    for(GolayPair seq : map) {
        for(unsigned int i = 0; i < seq.b.size(); i++) {
            seq.b[i] = -seq.b[i];
        }
        map.insert(seq);
    }
}

void negative_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq : map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            seq[i] = -seq[i];
        }
        map.insert(seq);
    }
}

void altnegative_pair(set<GolayPair>& map) {

    for(GolayPair seq: map) { 
        for(unsigned int i = 0; i < seq.b.size(); i++) {
            if(i % 2 == 1) { 
                seq.b[i] = -seq.b[i];
            }
        }
        map.insert(seq);
    }
}

void altnegative_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq : map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            if(i % 2 == 1) { 
                seq[i] = -seq[i];
            }
        }
        map.insert(seq);
    }
}

array<int, LEN> permute(array<int, LEN>& seq, int coprime) {
    array<int, LEN> newseq;
    for(int i = 0; i < LEN; i++) {
        newseq[i] = seq[i * coprime % LEN];
    }
    return newseq;
}

void decimate_pair(set<GolayPair>& map) {
    for(GolayPair seq : map) {
        for(int i = 0; i < coprimelength[LEN]; i++) {
            GolayPair newseq;
            newseq.a = permute(seq.a, coprimelist[LEN][i]);
            newseq.b = permute(seq.b, coprimelist[LEN][i]);

            map.insert(newseq);
        }
    }
}

void decimation_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq : map) {
        for(int i = 0; i < coprimelength[LEN]; i++) {
            array<int, LEN> newseq = permute(seq, coprimelist[LEN][i]);

            map.insert(newseq);
        }
    }
}



