#include<stdio.h>
#include<set>
#include<array>
#include<vector>
#include"golay.h"
#include"coprimes.h"
#include<algorithm>
#include<iostream>
#include<unordered_set>

using namespace std;

void shift_equivalence(set<array<int,ORDER>>& map);
void negative_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void altnegative_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void unishift_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void decimation_equivalence(set<array<int, ORDER>>& map);
void reverse_equivalence(set<array<int, ORDER>>& map);
void shift_pair(unordered_set<GolayPair>& map);
void decimate_pair(unordered_set<GolayPair>& map);
void reverse_pair(unordered_set<GolayPair>& map);
void altnegative_pair(unordered_set<GolayPair>& map);
void negate_pair(unordered_set<GolayPair>& map);
void swap_pair(unordered_set<GolayPair>& map);

unordered_set<GolayPair> generateClassPairs(GolayPair seq) {
    unordered_set<GolayPair> map;
    map.rehash(100000000);

    unsigned int size = 0;

    map.insert(seq);

    while(map.size() != size) {
        size = map.size();

        shift_pair(map);
        altnegative_pair(map);
        reverse_pair(map);
        decimate_pair(map);
        negate_pair(map);
        swap_pair(map);
        printf("%d\n", size);
    }

    return map;
}

set<array<int, ORDER>> generateClass(array<int, ORDER> seq, int flag) {
    set<array<int, ORDER>> map;

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

    return map;
}

void swap_pair(unordered_set<GolayPair>& map) {
    for(GolayPair seq : map) {
        array<int, ORDER> temp = seq.a;
        seq.a = seq.b;
        seq.b = temp;

        map.insert(seq);
    }
}


void shift_pair(unordered_set<GolayPair>& map) {
    GolayPair temp;
    for(GolayPair seq: map) {
        temp = seq;
        for(unsigned int i = 0; i < seq.a.size() - 1; i++) {
            for(unsigned int j = 0; j < seq.a.size() - 1; j++) {
                rotate(seq.b.begin(), seq.b.begin() + 1, seq.b.end());

                map.insert(seq);

            }
            rotate(seq.a.begin(), seq.a.begin() + 1, seq.a.end());
        }
    }
}

void shift_equivalence(set<array<int, ORDER>>& map) {
    for(array<int, ORDER> seq: map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            rotate(seq.begin(), seq.begin() + 1, seq.end());
            map.insert(seq);
        }
    }
}

void reverse_pair(unordered_set<GolayPair>& map) {
    for(GolayPair seq: map) { 
        array<int, ORDER> temp = seq.a;

        reverse(seq.a.begin(), seq.a.end());
        map.insert(seq);

        reverse(seq.b.begin(), seq.b.end());
        map.insert(seq);

        seq.a = temp;
        map.insert(seq);
    }
}

void reverse_equivalence(set<array<int, ORDER>>& map) {
    for(array<int, ORDER> seq: map) { 
        reverse(seq.begin(), seq.end());

        map.insert(seq);
    }
}

void negate_pair(unordered_set<GolayPair>& map) {
    for(GolayPair seq : map) {
        array<int, ORDER> temp = seq.a;
        for(unsigned int i = 0; i < seq.a.size(); i++) {
                seq.a[i] = -seq.a[i];
        }
        map.insert(seq);

        for(unsigned int i = 0; i < seq.b.size(); i++) {
            seq.b[i] = -seq.b[i];
        }
        map.insert(seq);

        seq.a = temp;
        map.insert(seq);
    }
}

void negative_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        seq[i] = -seq[i];
    }
    map.insert(seq);
}

void altnegative_pair(unordered_set<GolayPair>& map) {
    for(GolayPair seq: map) { 
        array<int, ORDER> temp = seq.a;
        for(unsigned int i = 0; i < seq.a.size(); i++) {
            if(i % 2 == 1) { 
                seq.a[i] = -seq.a[i];
            }
        }
        map.insert(seq);

        for(unsigned int i = 0; i < seq.b.size(); i++) {
            if(i % 2 == 1) { 
                seq.b[i] = -seq.b[i];
            }
        }
        map.insert(seq);

        seq.a = temp;
        map.insert(seq);
    }
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

void decimate_pair(unordered_set<GolayPair>& map) {
    for(GolayPair seq : map) {
        for(int i = 0; i < coprimelength[ORDER]; i++) {
            GolayPair newseq;
            newseq.a = permute(seq.a, coprimelist[ORDER][i]);
            newseq.b = permute(seq.b, coprimelist[ORDER][i]);

            map.insert(newseq);
        }
    }
}

void decimation_equivalence(set<array<int, ORDER>>& map) {
    for(array<int, ORDER> seq : map) {
        for(int i = 0; i < coprimelength[ORDER]; i++) {
            array<int, ORDER> newseq = permute(seq, coprimelist[ORDER][i]);

            map.insert(newseq);
        }
    }
}






