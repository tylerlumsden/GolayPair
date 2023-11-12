#include<stdio.h>
#include<set>
#include<array>
#include<vector>
#include"golay.h"
#include"coprimes.h"
#include<algorithm>
#include<iostream>

using namespace std;

int shift_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> base);
int decimation_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> base);
int reverse_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> base);

int isOrderly(array<int, ORDER> base, int flag) {
    set<array<int, ORDER>> map;
    set<array<int, ORDER>> equiv;


    unsigned int size = 0;

    map.insert(base);

    while(map.size() != size) {
        size = map.size();

        if(flag == 0) {
            if(!decimation_equivalence(map, base)) {
                return 0;
            }
        }

        if(!shift_equivalence(map, base)) {
            return 0;
        }

       
        if(!reverse_equivalence(map, base)) {
            return 0;
        }
    }

    return 1;
}

int shift_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> base) {
    for(array<int, ORDER> seq: map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            rotate(seq.begin(), seq.begin() + 1, seq.end());

            if(seq < base) {
                return 0;
            }

            map.insert(seq);
        }
    }
    return 1;
}

int reverse_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> base) {
    for(array<int, ORDER> seq: map) { 
        reverse(seq.begin(), seq.end());

        if(seq < base) {
            return 0;
        }

        map.insert(seq);
    }
    return 1;
}

array<int, ORDER> permute(array<int, ORDER> seq, int coprime) {
    array<int, ORDER> newseq;
    for(int i = 0; i < ORDER; i++) {
        newseq[i] = seq[i * coprime % ORDER];
    }
    return newseq;
}

int decimation_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> base) {
    for(array<int, ORDER> seq : map) {
        for(int i = 0; i < coprimelength[ORDER]; i++) {
            array<int, ORDER> newseq = permute(seq, coprimelist[ORDER][i]);

            if(newseq < base) {
                return 0;
            }
            
            map.insert(newseq);
        }
    }
    return 1;
}