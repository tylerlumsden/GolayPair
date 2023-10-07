#define ORDER 34

#ifndef GOLAY_H
#define GOLAY_H

#include<array>

using namespace std;

class GolayPair {
    public:
        array<int, ORDER> a;
        array<int, ORDER> b;
        
        bool operator<(const GolayPair& golay) const {
            if(a == golay.a) {
                return b < golay.b;
            } else {
                return a < golay.a;
            }
}
};


void write_seq(FILE * out, array<int, ORDER> seq);
void write_unique_seq(FILE * out, int rowsum, int flag);
int check_if_pair(array<int, ORDER> a, array<int, ORDER> b);
void fill_from_string(array<int, ORDER>& seq, char str[]);

#endif
