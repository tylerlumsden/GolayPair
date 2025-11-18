#ifndef GOLAY_H
#define GOLAY_H

#include<array>
#include<string>
#include<vector>
#include<set>
#include"fourier.h"
#include<math.h>

using namespace std;

std::set<std::pair<int, int>> sumoftwosquares(int constant);
void write_seq(FILE * out, vector<int> seq);
void write_unique_seq(FILE * out, int rowsum, int flag);
int check_if_pair(vector<int> a, vector<int> b);

class GolayPair {
    public:
        vector<int> a;
        vector<int> b;
        
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


#endif
