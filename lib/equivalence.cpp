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
set<GolayPair> shift_pair(set<GolayPair>& map);
set<GolayPair> decimate_pair(set<GolayPair>& map);
set<GolayPair> reverse_pair(set<GolayPair>& map);
set<GolayPair> altnegative_pair(set<GolayPair>& map);
set<GolayPair> negate_pair(set<GolayPair>& map);
set<GolayPair> swap_pair(set<GolayPair>& map);

set<GolayPair> generateExhaust(GolayPair seq) {
        set<GolayPair> map;
    set<GolayPair> newmap;

    unsigned int size = 0;

    map.insert(seq);
    newmap.insert(seq);

    while(map.size() != size) {

        set<GolayPair> iter;

        size = map.size();

        set<GolayPair> temp;

        
        temp = shift_pair(newmap);
        iter.insert(temp.begin(), temp.end());
        newmap.insert(iter.begin(), iter.end());
        
        /*
        temp = altnegative_pair(newmap);
        iter.insert(temp.begin(), temp.end());
        newmap.insert(iter.begin(), iter.end());
        */
        
        temp = reverse_pair(newmap);
        iter.insert(temp.begin(), temp.end());
        newmap.insert(iter.begin(), iter.end());
        
        temp = swap_pair(newmap);
        iter.insert(temp.begin(), temp.end());
        newmap.insert(iter.begin(), iter.end());
        
        
        temp = decimate_pair(newmap);
        iter.insert(temp.begin(), temp.end());
        newmap.insert(iter.begin(), iter.end());
        
        for(GolayPair seq : map) {
            if(iter.count(seq)) {
                iter.erase(seq);
            }
        }

        map.insert(iter.begin(), iter.end());
        newmap = iter;

        printf("%d, %d\n", newmap.size(), map.size());
    }

    return map;
}

set<GolayPair> constructGenerators() {
    GolayPair seq;

    for(int i = 1; i <= LEN; i++) {
        seq.a[i - 1] = i;
        seq.b[i - 1] = (LEN) + i;
    }

    return generateExhaust(seq);
} 

set<GolayPair> generateClassPairs(set<GolayPair> generators, GolayPair seq) {

    set<GolayPair> equiv;

    for(GolayPair item : generators) {
        GolayPair newseq;


        if((item.a[0] < 0 && -item.a[0] > (LEN)) || (item.a[0] > 0 && item.a[0] > (LEN))) {
            for(int i = 0; i < LEN; i++) {
                if(item.a[i] < 0) {
                    newseq.b[i] = -seq.a[(-item.a[i] - 1) % (LEN)];
                } else {
                    newseq.b[i] = seq.a[(item.a[i] - 1) % (LEN)];
                }

                if(item.b[i] < 0) {
                    newseq.a[i] = -seq.b[(-item.b[i] - 1) % (LEN)];
                } else {
                    newseq.a[i] = seq.b[(item.b[i] - 1) % (LEN)];
                }
            }
        } else {
            for(int i = 0; i < LEN; i++) {
                if(item.a[i] < 0) {
                    newseq.a[i] = -seq.a[(-item.a[i] - 1) % (LEN)];
                } else {
                    newseq.a[i] = seq.a[(item.a[i] - 1) % (LEN)];
                }

                if(item.b[i] < 0) {
                    newseq.b[i] = -seq.b[(-item.b[i] - 1) % (LEN)];
                } else {
                    newseq.b[i] = seq.b[(item.b[i] - 1) % (LEN)];
                }
            }
        }

        equiv.insert(newseq);
    }
    
    equiv.erase(seq);

    printf("%d\n", equiv.size());

    return equiv;
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

set<GolayPair> swap_pair(set<GolayPair>& map) {
    set<GolayPair> newmap;
    for(GolayPair seq : map) {
        array<int, LEN> temp = seq.a;
        seq.a = seq.b;
        seq.b = temp;

        newmap.insert(seq);
    }
    return newmap;
}


set<GolayPair> shift_pair(set<GolayPair>& map) {
    set<GolayPair> newmap;
    for(GolayPair seq: map) {
        for(unsigned int j = 0; j < (LEN) - 1; j++) {
            rotate(seq.b.begin(), seq.b.begin() + 1, seq.b.end());
            newmap.insert(seq);
        }
    }
    return newmap;
}

void shift_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq: map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            rotate(seq.begin(), seq.begin() + 1, seq.end());
            map.insert(seq);
        }
    }
}

set<GolayPair> reverse_pair(set<GolayPair>& map) {
    set<GolayPair> newmap;
    for(GolayPair seq: map) { 

        reverse(seq.b.begin(), seq.b.end());
        newmap.insert(seq);

    }
    return newmap;
}

void reverse_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq: map) { 
        reverse(seq.begin(), seq.end());

        map.insert(seq);
    }
}

set<GolayPair> negate_pair(set<GolayPair>& map) {
    set<GolayPair> newmap;
    for(GolayPair seq : map) {
        for(unsigned int i = 0; i < seq.b.size(); i++) {
            seq.b[i] = -seq.b[i];
        }
        newmap.insert(seq);
    }
    return newmap;
}

void negative_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq : map) {
        for(unsigned int i = 0; i < seq.size(); i++) {
            seq[i] = -seq[i];
        }
        map.insert(seq);
    }
}

set<GolayPair> altnegative_pair(set<GolayPair>& map) {
    set<GolayPair> newmap;
    for(GolayPair seq: map) { 
        for(unsigned int i = 0; i < seq.b.size(); i++) {
            if(i % 2 == 1) { 
                seq.b[i] = -seq.b[i];
                seq.a[i] = -seq.a[i];
            }
        }
        newmap.insert(seq);
    }
    return newmap;
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
        newseq[i] = seq[i * coprime % (LEN)];
    }
    return newseq;
}

set<GolayPair> decimate_pair(set<GolayPair>& map) {
    set<GolayPair> newmap;
    for(GolayPair seq : map) {
        for(int i = 0; i < coprimelength[LEN]; i++) {
            GolayPair newseq;
            newseq.a = permute(seq.a, coprimelist[LEN][i]);
            newseq.b = permute(seq.b, coprimelist[LEN][i]);

            newmap.insert(newseq);
        }
    }
    return newmap;
}

void decimation_equivalence(set<array<int, LEN>>& map) {
    for(array<int, LEN> seq : map) {
        for(int i = 0; i < coprimelength[LEN]; i++) {
            array<int, LEN> newseq = permute(seq, coprimelist[LEN][i]);

            map.insert(newseq);
        }
    }
}