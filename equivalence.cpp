#include<stdio.h>
#include<set>
#include<array>
#include<vector>
#include"golay.h"
#include"coprimes.h"
#include<algorithm>

using namespace std;

void shift_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void negative_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void altnegative_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void unishift_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void decimation_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> seq);

void generate_equivalence_class(vector<set<array<int, ORDER>>>& classes, array<int, ORDER> seq) {
    set<array<int, ORDER>> map;

    for(set<array<int, ORDER>> map : classes) {
        if(map.find(seq) != map.end()) {
            return;
        }
    }

    map.insert(seq);
    shift_equivalence(map, seq);  
    negative_equivalence(map, seq);
    altnegative_equivalence(map, seq);
    //decimation_equivalence(map, seq);

    classes.push_back(map);
}

void shift_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        rotate(seq.begin(), seq.begin() + 1, seq.end());
        
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

void permute(array<int, ORDER>& seq, int coprime) {
    for(int i = 0; i < ORDER; i++) {
        seq[i] = seq[i * coprime % ORDER];
    }
}

void decimation_equivalence(set<array<int, ORDER>>& map, array<int, ORDER> seq) {

    for(int i = 0; i <= coprimelength[ORDER]; i++) {

        permute(seq, coprimelist[ORDER][i]);

        map.insert(seq);
    }
}






