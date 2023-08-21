#include<stdio.h>
#include<time.h>
#include"array.h"
#include<string.h>
#include"fftw-3.3.5-dll64/fftw3.h"
#include"fourier.h"
#include<unordered_map>
#include<vector>
#include"equivalence.h"

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

#define ORDER 18
#define SumsA 0
#define SumsB 6
#define PrintProg 10000

int VecCheckIfPair(vector<int> a, vector<int> b);
int CheckIfPair(int a[], int b[]);
int Power(int base, int exponent);
void Log(int pairs, int order, int time, const char * lognote);

void find_psd() {

    fftw_complex *in, *dftA, *dftB;
    fftw_plan planA, planB;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    dftA = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    dftB = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);

    planA = fftw_plan_dft_1d(ORDER, in, dftA, FFTW_FORWARD, FFTW_ESTIMATE);
    planB = fftw_plan_dft_1d(ORDER, in, dftB, FFTW_FORWARD, FFTW_ESTIMATE);

    int pairs = 0;
    int progress = 0;
    int combinations = Power(2, ORDER);

    char fname[100];
    sprintf(fname, "results/pairs-%d.txt", ORDER);
    FILE * out = fopen(fname, "w+");

    int a[ORDER];
    int currentA = ORDER;
    int b[ORDER];
    int currentB = ORDER;



    Reset(a, ORDER);
    Reset(b, ORDER);

    clock_t start = clock();
    clock_t current;

    do {

        current = clock();
        if(progress % PrintProg == 0) {
            printf("Progress: %d ... %d, time elapsed: %d seconds, Pairs found: %d\n", progress, combinations - 1, (current - start) / CLOCKS_PER_SEC, pairs);
            fflush(stdin);
        }

        Reset(b, ORDER);
        currentB = ORDER;

        //start filtering here
        dftA = dft(a, in, dftA, planA, ORDER);
        if(dftfilter(dftA, ORDER)) {
            do {
                dftB = dft(b, in, dftB, planB, ORDER);
                if(dftfilterpair(dftA, dftB, ORDER) && CheckIfPair(a,b)) {
                    //record pair to file
                    WritePairToFile(out, a, b, ORDER);
                    pairs++;
                }
            } while((currentB = NextCombinationRowSums(b, ORDER, currentB, SumsB)) != ORDER + 1);
        }
        progress++;
    } while((currentA = NextCombinationRowSums(a, ORDER, currentA, SumsA)) != ORDER + 1);

    current = clock();
    Log(pairs, ORDER, (current - start) / CLOCKS_PER_SEC, "PSD filtering with generating from row sums");

    printf("Pairs Found: %d\n", pairs);

    fftw_free(dftA);
    fftw_free(dftB);
    fftw_free(in);

    fftw_destroy_plan(planA);
    fftw_destroy_plan(planB);
}

void find_unique() {

    int pairs = 0;

    char fname[100];
    sprintf(fname, "results/pairs-%d.txt", ORDER);
    FILE * out = fopen(fname, "w+");


    clock_t start = clock();
    clock_t current;

    fftw_complex *in, *dftA, *dftB;
    fftw_plan planA, planB;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    dftA = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    dftB = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);

    planA = fftw_plan_dft_1d(ORDER, in, dftA, FFTW_FORWARD, FFTW_ESTIMATE);
    planB = fftw_plan_dft_1d(ORDER, in, dftB, FFTW_FORWARD, FFTW_ESTIMATE);


    //generate an equivalence class for all sequences
    //if a sequence is already in an equivalence class, then skip
    //check through all combinations of a single representative of an equivalence class

    vector<int> a(ORDER, 1);
    int currentSum = ORDER;

    //create an equivalence class for every permutation of sequence
    vector<unordered_map<vector<int>, int>> classesA;
    
    printf("Generating classesA\n");
    do {
        dftA = dftVec(a, in, dftA, planA);
        if(dftfilter(dftA, ORDER)) {
            generate_equivalence_class(classesA, a);
        }
    } while((currentSum = VecNextCombinationRowSums(a, currentSum, SumsA)) != ORDER + 1);

    //every permutation of b
    vector<int> b(ORDER, 1);

    currentSum = ORDER;

    //create an equivalence class for every permutation of sequence
    vector<unordered_map<vector<int>, int>> classesB;

    printf("Generating classesB\n");    
    do {
        dftB = dftVec(b, in, dftA, planA);
        if(dftfilter(dftB, ORDER)) {
            generate_equivalence_class(classesB, b);
        }
    } while((currentSum = VecNextCombinationRowSums(b, currentSum, SumsB)) != ORDER + 1);

    for(unordered_map<vector<int>, int> mapA : classesA) {
        for(unordered_map<vector<int>, int> mapB : classesB) {
            if(VecCheckIfPair((*mapA.begin()).first, (*mapB.begin()).first)) {
                WriteVecPairToFile(out, (*mapA.begin()).first, (*mapB.begin()).first);
                pairs++;
            }
        }
    }


    current = clock();
    Log(pairs, ORDER, (current - start) / CLOCKS_PER_SEC, "Equivalence generating with sequences only from row sums, only equivalence is uniform shift");

    printf("Pairs Found: %d\n", pairs);

    fftw_free(dftA);
    fftw_free(dftB);
    fftw_free(in);

    fftw_destroy_plan(planA);
    fftw_destroy_plan(planB);
}

int PAF(int seq[], int s) { 

    int result = 0;
    for(int i = 0; i < ORDER; i++) {
        result = result + (seq[i] * seq[(i + s) % ORDER]);
    }
    return result;
}

int CheckIfPair(int a[], int b[]) {
    for(int i = 1; i <= ORDER / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != 0) {
            return 0;
        }
    }

    return 1;
}

int VecPAF(vector<int> seq, int s) { 

    int result = 0;
    for(int i = 0; i < ORDER; i++) {
        result = result + (seq[i] * seq[(i + s) % ORDER]);
    }
    return result;
}

int VecCheckIfPair(vector<int> a, vector<int> b) {
    for(int i = 1; i <= ORDER / 2; i++) {
        if(VecPAF(a, i) + VecPAF(b, i) != 0) {
            return 0;
        }
    }

    return 1;
}

int Power(int base, int exponent) {
    int product = base;
    for(int i = 0; i < exponent - 1; i++) {
        product *= base;
    }
    return product;
}

void Log(int pairs, int order, int time, const char * lognote) {
    char fname[100];
    sprintf(fname, "results/log-%d.txt", order);
    FILE * out = fopen(fname, "a");

    fprintf(out, "%s:\n %d pairs found\n time elapsed: %d seconds\n", lognote, pairs, time);

    fclose(out);
}


