#include<stdio.h>
#include<set>
#include<array>
#include<vector>
#include"golay.h"
#include"coprimes.h"
#include"decomps.h"
#include<algorithm>
#include<iostream>

using namespace std;

set<array<int, ORDER>> shift_equivalence(array<int, ORDER> seq, array<int, ORDER> base);
set<array<int, ORDER>> decimation_equivalence(array<int, ORDER> seq, array<int, ORDER> base);
set<array<int, ORDER>> reverse_equivalence(array<int, ORDER> seq, array<int, ORDER> base);

int generateClass(array<int, ORDER> base, int flag) {
    set<array<int, ORDER>> map;
    set<array<int, ORDER>> equiv;


    unsigned int size = 0;

    map.insert(base);
    for(array<int, ORDER> seq : map) {
        while(map.size() != size) {
            size = map.size();

            if(flag == 0) {
                equiv = decimation_equivalence(seq, base);

                if(equiv.size() == 0) {
                    return 0;
                }

                map.insert(equiv.begin(), equiv.end());
            }

            equiv = shift_equivalence(seq, base);

            if(equiv.size() == 0) {
                return 0;
            }

            map.insert(equiv.begin(), equiv.end());
       
            equiv = reverse_equivalence(seq, base);
            
            if(equiv.size() == 0) {
                return 0;
            }
            
            map.insert(equiv.begin(), equiv.end());
        }
    }

    return 1;
}

set<array<int, ORDER>> shift_equivalence(array<int, ORDER> seq, array<int, ORDER> base) {
    set<array<int,ORDER>> map;
    set<array<int, ORDER>> null;

    for(unsigned int i = 0; i < seq.size(); i++) {
        rotate(seq.begin(), seq.begin() + 1, seq.end());

        if(seq < base) {
            return null;
        }

        map.insert(seq);
    }
    return map;
}

set<array<int, ORDER>> reverse_equivalence(array<int, ORDER> seq, array<int, ORDER> base) {
    set<array<int, ORDER>> map;
    set<array<int, ORDER>> null;

    reverse(seq.begin(), seq.end());

    if(seq < base) {
        return null;
    }

    map.insert(seq);

    return map;
}

array<int, ORDER> permute(array<int, ORDER> seq, int coprime) {
    array<int, ORDER> newseq;
    for(int i = 0; i < ORDER; i++) {
        newseq[i] = seq[i * coprime % ORDER];
    }
    return newseq;
}

set<array<int, ORDER>> decimation_equivalence(array<int, ORDER> seq, array<int, ORDER> base) {
    set<array<int, ORDER>> map;
    set<array<int, ORDER>> null;

    for(int i = 0; i < coprimelength[ORDER]; i++) {
        array<int, ORDER> newseq = permute(seq, coprimelist[ORDER][i]);

        if(newseq < base) {
            return null;
        }

        map.insert(newseq);
    }
    return map;
}






