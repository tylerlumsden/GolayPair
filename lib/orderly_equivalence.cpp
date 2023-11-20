#include<stdio.h>
#include<set>
#include<array>
#include<vector>
#include"golay.h"
#include"coprimes.h"
#include<algorithm>
#include<iostream>

using namespace std;

int shift_equivalence(set<array<int, LEN>>& map, array<int, LEN> base);
int decimation_equivalence(set<array<int, LEN>>& map, array<int, LEN> base);
int reverse_equivalence(set<array<int, LEN>>& map, array<int, LEN> base);

int isOrderly(array<int, LEN> base, int flag) {
    set<array<int, LEN>> map;
    set<array<int, LEN>> equiv;


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

int shift_equivalence(set<array<int, LEN>>& map, array<int, LEN> base) {
    for(array<int, LEN> seq: map) {
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

int reverse_equivalence(set<array<int, LEN>>& map, array<int, LEN> base) {
    for(array<int, LEN> seq: map) { 
        reverse(seq.begin(), seq.end());

        if(seq < base) {
            return 0;
        }

        map.insert(seq);
    }
    return 1;
}

array<int, LEN> permute(array<int, LEN> seq, int coprime) {
    array<int, LEN> newseq;
    for(int i = 0; i < LEN; i++) {
        newseq[i] = seq[(i * coprime) % (LEN)];
    }
    return newseq;
}

int decimation_equivalence(set<array<int, LEN>>& map, array<int, LEN> base) {

    for(array<int, LEN> seq : map) {
        for(int i = 0; i < coprimelength[LEN]; i++) {

            array<int, LEN> newseq = permute(seq, coprimelist[LEN][i]);

            if(newseq < base) {
                return 0;
            }
            
            map.insert(newseq);
        }
    }
    return 1;
}