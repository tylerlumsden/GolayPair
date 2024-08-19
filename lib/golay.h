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
bool double_equal(double a, int b);

class Runtime {

    private:
        fftw_complex *in, *out;
        fftw_plan plan;

    public: 
        const int paf_bound;
        const int psd_bound;
        const int order;
        const int len;
        const std::set<std::pair<int, int>> twosquares_solutions;
    
        Runtime(int paf_bound, int order, int len) : 
        paf_bound(paf_bound), 
        psd_bound(2 * order - paf_bound), 
        order(order), 
        len(len), 
        twosquares_solutions(sumoftwosquares(psd_bound)) {


            in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * len);
            out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * len);
            plan = fftw_plan_dft_1d(len, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

        }

        std::vector<double> PSD(std::vector<int> seq) {
            for(size_t i = 0; i < seq.size(); i++) {
                in[i][0] = (double)seq[i];
                in[i][1] = 0;
            } 

            fftw_execute(plan);

            std::vector<double> psd_vals;
            for(size_t i = 0; i < seq.size(); i++) {
                double val = out[i][1] * out[i][1] + out[i][0] * out[i][0];
                psd_vals.push_back(val);
            }

            return psd_vals;
        }

        bool PSD_filter(std::vector<double> psd_vals) {

            if(psd_vals.size() % 2 == 0) {
                size_t j = psd_vals.size() / 2;

                for(std::pair<int, int> solution : twosquares_solutions) {
                    if(!double_equal(psd_vals[j], solution.first * solution.first) && !double_equal(psd_vals[j], solution.second * solution.second)) {
                        return 0;
                    }
                }
            }
            
            for(size_t i = 0; i < psd_vals.size() / 2; i++) {
                if((int)rint(psd_vals[i]) > psd_bound + 0.001) {
                    return 0;
                }
            }
            return 1;
        }

        bool a_is_solution(int a) {
            for(auto solution : twosquares_solutions) {
                if(solution.first == a) {
                    return true;
                }
            }
            return false;
        }

        bool b_is_solution(int b) {
            for(auto solution : twosquares_solutions) {
                if(solution.second == b) {
                    return true;
                }
            }
            return false;
        }

};

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