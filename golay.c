#include<stdio.h>
#include<time.h>
#include"array.h"
#include<string.h>
#include"fftw-3.3.5-dll64/fftw3.h"
#include"fourier.h"

#define ORDER 20
#define SumsA 2
#define SumsB 6
#define PrintProg 100

int CheckIfPair(int a[], int b[]);
int Power(int base, int exponent);
void Log(int pairs, int order, int time, char * lognote);

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

int Power(int base, int exponent) {
    int product = base;
    for(int i = 0; i < exponent - 1; i++) {
        product *= base;
    }
    return product;
}

void Log(int pairs, int order, int time, char * lognote) {
    char fname[100];
    sprintf(fname, "results/log-%d.txt", order);
    FILE * out = fopen(fname, "a");

    fprintf(out, "%s:\n %d pairs found\n time elapsed: %d seconds\n", lognote, pairs, time);
}


