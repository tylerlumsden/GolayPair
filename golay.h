
#include<array>
#include<string>
#define LEN 90
#define COMPRESS 3
#define ORDER LEN / COMPRESS

#ifndef GOLAY_H
#define GOLAY_H

//A:3+3+3+3+3+3+3+3+3+1+1+1+-1+-1+-1+-1+-1+-1+-1+-1+-1+-1+-1+-1+-1+-1+-1+-3+-3+-3
//9 3's, 3 1's, 15 -1's, 3 -3's

//B:3+3+3+3+3+3+3+3+3+3+1+1+1+1+1+1+1+1+1+-1+-1+-1+-3+-3+-3+-3+-3+-3+-3+-3
//10 3's 9 1's, 3 -1's, 8 -3's

//const std::array<int, ORDER> seqA = {-3,-3,-3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,3,3,3,3,3,3,3,3,3,3,};
//const std::array<int, ORDER> seqB = {-3,-3,-3,-3,-3,-3,-3,-3,-1,-1,-1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3};

//A:3+3+3+3+3+3+3+3+3+1+1+1+1+1+1+1+1+1+-1+-1+-1+-3+-3+-3+-3+-3+-3+-3+-3+-3
//9 3's, 9 1's, 3 -1's, 9 -3's

//B:3+3+3+3+3+3+3+3+3+3+1+1+1+1+1+1+1+-1+-1+-1+-1+-1+-1+-1+-3+-3+-3+-3+-3+-3
//10 3's, 7 1's, 7 -1's, 6 -3's
//const std::array<int, ORDER> seqA = {-3,-3,-3,-3,-3,-3,-3,-3,-3,-1,-1,-1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3};
//const std::array<int, ORDER> seqB = {-3,-3,-3,-3,-3,-3,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3};


//A: 13 1's, 10 -1's, 4 3's, 3 -3's
//B: 17 1's, 5 -1's, 4 3's, 4 -3's
//const std::array<int, ORDER> seqA = {-3, -3, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3};
const std::array<int, ORDER> seqB = {-3, -3, -3, -3, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3};

//A:3+3+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+-1+-1+-1+-1+-3+-3+-3+-3+-3
//2 3's, 5 -3's, 4 -1's, 19 1's

const std::array<int, ORDER> seqA = {-3,-3,-3,-3,-3,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3};

//const std::array<int, ORDER> seqA = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//const std::array<int, ORDER> seqB = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

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

        bool operator==(const GolayPair& golay) const {
            return (a == golay.a && b == golay.b);
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

//copied following code from stack-overflow: https://stackoverflow.com/questions/37007307/fast-hash-function-for-stdvector
//using boost::hash_combine
template <class T>
inline void hash_combine(std::size_t& seed, T const& v)
{
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
    template <>
    struct hash<GolayPair>
    {
        typedef GolayPair argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& in) const
        {
            size_t size = in.a.size();
            size_t seed = 0;
            for (size_t i = 0; i < size; i++)
                //Combine the hash of the current vector with the hashes of the previous ones
                hash_combine(seed, in.a[i]);

            for (size_t i = 0; i < size; i++)
            //Combine the hash of the current vector with the hashes of the previous ones
                hash_combine(seed, in.b[i]);

            return seed;
        }
    };
}



void write_seq(FILE * out, array<int, ORDER> seq);
void write_unique_seq(FILE * out, int rowsum, int flag);
int check_if_pair(array<int, ORDER> a, array<int, ORDER> b);
void fill_from_string(array<int, ORDER>& seq, char str[]);

#endif
