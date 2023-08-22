#include<stdio.h>
#include"array.h"
#include"fourier.h"
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<iterator>

#define LIMIT 90

using namespace std;


//copied following code from stack-overflow: https://stackoverflow.com/questions/37007307/fast-hash-function-for-stdvector
//using boost::hash_combine
template <class T>
inline void hash_combine(std::size_t& seed, T const& v)
{
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
    template<typename T>
    struct hash<vector<T>>
    {
        typedef vector<T> argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& in) const
        {
            size_t size = in.size();
            size_t seed = 0;
            for (size_t i = 0; i < size; i++)
                //Combine the hash of the current vector with the hashes of the previous ones
                hash_combine(seed, in[i]);
            return seed;
        }
    };
}

void shift_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq);
void negative_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq);
void altnegative_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq);

void generate_equivalence_class(vector<unordered_map<vector<int>, int>>& classes, vector<int> seq) {
    unordered_map<vector<int>, int> map;

    for(unordered_map<vector<int>, int> map : classes) {
        if(map.find(seq) != map.end()) {
            return;
        }
    }

    map.insert({seq, 1});
    shift_equivalence(map, seq); 
    negative_equivalence(map, seq);
    altnegative_equivalence(map, seq);

    classes.push_back(map);
}

void unishift_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq) {
    //rewrite for experiment
    for(int i = 0; i < seq.size(); i++) {
        for(int i = 0; i < seq.size(); i++) {
            int temp = seq[(i + 1) % seq.size()];
            seq[i + 1] = seq[i];

        }
    }
}


void shift_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        rotate(seq.begin(), seq.begin() + 1, seq.end());

        map.insert({seq, 1});
    }
}

void negative_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        seq[i] = -seq[i];
    }
    map.insert({seq, 1});
}

void altnegative_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        if(i % 2 == 1) { 
            seq[i] = -seq[i];
        }
    }
    map.insert({seq, 1});
}

constexpr int ** COPRIMES() {
    int count = 0;
    int * list[LIMIT]= {};

    for(int i = 0; i < LIMIT; i++) {

        int coprimes[LIMIT] = {};

        for(int j = 1; j < i; j++) {
            if(__gcd(i,j) == 1) {
                coprimes[count] = j;
                count++;
            }
        }
        list[i] = coprimes;
    }

    return list;
}

void permute(vector<int>& seq, int coprime) {
    for(int i = 0; i < seq.size(); i++) {
        seq[i] = seq[i * coprime % seq.size()];
    }
}

void decimation_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq) {

    int ** coprimes = COPRIMES();

    for(int i = 0; i < LIMIT; i++) {

        permute(seq, coprimes[seq.size()][i]);

        map.insert({seq, 1});
    }
}

