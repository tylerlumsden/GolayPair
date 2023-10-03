#include<stdio.h>
#include<set>
#include<array>
#include<vector>
#include"golay.h"
#include"coprimes.h"
#include<algorithm>

using namespace std;

void shift_equivalence(set<array<int,ORDER>>& map);
void negative_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void altnegative_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void unishift_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void decimation_equivalence(set<array<int, ORDER>>& map);
void reverse_equivalence(set<array<int, ORDER>>& map);

set<array<int, ORDER>> generateClassA(array<int, ORDER>& seq) {
    set<array<int, ORDER>> map;

    unsigned int size = 0;

    map.insert(seq);

    while(map.size() != size) {
        size = map.size();
        
        shift_equivalence(map);  
        decimation_equivalence(map);
    }

    return map;
}

set<array<int, ORDER>> generateClassB(array<int, ORDER>& seq) {
    set<array<int, ORDER>> map;

    unsigned int size = 0;

    map.insert(seq);

    while(map.size() != size) {
        size = map.size();

        shift_equivalence(map);  
        reverse_equivalence(map);
    }

    return map;
}
/*
set<pair<array<int, ORDER>,array<int, ORDER>>> generateClassPairs(pair<array<int, ORDER>,array<int, ORDER>> seq) {
    set<pair<array<int, ORDER>,array<int, ORDER>>> map;

    unsigned int size = 0;

    map.insert(seq);

    while(map.size() != size) {
        size = map.size();

        decimation_equivalence(map);  
    }

    return map;
}
*/



void shift_equivalence(set<array<int, ORDER>>& map) {
    for(array<int, ORDER> seq: map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            rotate(seq.begin(), seq.begin() + 1, seq.end());
            if(seq[0] != 1) {
                map.insert(seq);
            }
        }
    }
}

void reverse_equivalence(set<array<int, ORDER>>& map) {
    for(array<int, ORDER> seq: map) { 
        reverse(seq.begin(), seq.end());

         map.insert(seq);
    }
}

void negative_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        seq[i] = -seq[i];
    }
    map.insert(seq);
}

void altnegative_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        if(i % 2 == 1) { 
            seq[i] = -seq[i];
        }
    }
    map.insert(seq);
}

array<int, ORDER> permute(array<int, ORDER>& seq, int coprime) {
    array<int, ORDER> newseq;
    for(int i = 0; i < ORDER; i++) {
        newseq[i] = seq[i * coprime % ORDER];
    }
    return newseq;
}

void decimation_equivalence(set<array<int, ORDER>>& map) {
    for(array<int, ORDER> seq : map) {
        for(int i = 0; i < coprimelength[ORDER]; i++) {
            array<int, ORDER> newseq = permute(seq, coprimelist[ORDER][i]);

            map.insert(newseq);
        }
    }
}






