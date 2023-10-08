#define ORDER 16

#ifndef GOLAY_H
#define GOLAY_H

#include<array>
#include<string>

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

        operator std::string() {
            std::string seq;

            for(int i = 0; i < ORDER; i++) {
                if(a[i] == 1) {
                    seq.push_back('+'); 
                }
                if(a[i] == -1) {
                    seq.push_back('-'); 
                }
            }

            seq.push_back(' ');

            for(int i = 0; i < ORDER; i++) {
                if(b[i] == 1) {
                    seq.push_back('+'); 
                }
                if(b[i] == -1) {
                    seq.push_back('-'); 
                }
            }
            return seq;
        }
};


void write_seq(FILE * out, array<int, ORDER> seq);
void write_unique_seq(FILE * out, int rowsum, int flag);
int check_if_pair(array<int, ORDER> a, array<int, ORDER> b);
void fill_from_string(array<int, ORDER>& seq, char str[]);

#endif
