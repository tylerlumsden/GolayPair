#include<stdio.h>
#include"array.h"
#include"fourier.h"
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<iterator>

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

void generate_equivalence_class(vector<unordered_map<vector<int>, int>>& classes, vector<int> seq) {
    unordered_map<vector<int>, int> map;

    for(unordered_map<vector<int>, int> map : classes) {
        if(map.find(seq) != map.end()) {
            return;
        }
    }

    map.insert({seq, 1});
    shift_equivalence(map, seq); 
    classes.push_back(map);
}

void shift_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq) {
    for(unsigned int i = 0; i < seq.size(); i++) {
        rotate(seq.begin(), seq.begin() + 1, seq.end());

        if(map.find(seq) != map.end()) {
            break;
        }
        map.insert({seq, 1});
    }
}
