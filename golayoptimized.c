#define ORDER 18
#define SumsA 0
#define SumsB 6
#define PrintProg 100
//unoptimized: 27 hours for order 20 prog: 2500 time: 240 seconds
//optimized w/ Row Sums: approx. 3x faster prog: 2500 time: 106 seconds pairs found: 1154
//optimized w/ Power Representation 6 or 12: prog: 2500 time: 94 seconds (Found no pairs, which is probably why.)
//optimized row sums eliminating sequences of A that satisfy neither Power Representation: prog: 2500 time: 36 seconds pairs found: 1154

//ORDER 18 exhaustive w/seq b starting at combination a time:776 seconds pairs found: 0
//ORDER 18 exhaustive w/o seq b starting at combination a time: 1628 seconds pairs found: 0
//approx 2x increase


//next optimization: have the nested for loop that checks through B's start at the current combination of A,
//as well as eliminate every B s.t it satisfies neither power representation square.

//great potential optimization:
// find every candidate sequence and test all pairs between those instead

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"fftw-3.3.5-dll64/fftw3.h"

int PAF(int seq[], int s);
int CheckIfPair(int a[], int b[]);
int* CompressSequence(int a[]);
int NextCombination(int arr[], int length);
void PrintArray(int arr[], int length, FILE *fp);
void Reset(int arr[], int length);
int Power(int base, int exponent);
int RowSums(int a[]);
void CopyArray(int dest[], int source[], int length);
int dftfilter(int seq[], int len);

int main() {
    FILE *fp;

    fp = fopen("pairsfound.txt", "w+");

    int pairs = 0;
    int combinations = Power(2, ORDER);

    int a[ORDER];
    int b[ORDER];

    Reset(a, ORDER);
    Reset(b, ORDER);

    int progress = 0;

    clock_t start = clock();
    clock_t current;
    while(1) {
        current = clock();
            if(progress % PrintProg == 0) {
                printf("Progress: %d ... %d, time elapsed: %d seconds, Pairs found: %d\n", progress, combinations - 1, (current - start) / CLOCKS_PER_SEC, pairs);
                fflush(stdin);
            }
        if(dftfilter(a, ORDER) && (Power(RowSums(a), 2) == SumsA * SumsA || Power(RowSums(a), 2) == SumsB * SumsB)) {
            while(1) {
                if((Power(RowSums(a), 2) + Power(RowSums(b), 2) == ORDER * 2)) {
                    if(CheckIfPair(a,b)) {
                        PrintArray(a, ORDER, fp);
                        PrintArray(b, ORDER, fp);
                        pairs++;
                    }
                }
                if(!NextCombination(b,ORDER)) {
                    break;
                }
            }
        }
        if(!NextCombination(a,ORDER)) {
            break;
        }
        CopyArray(b, a, ORDER);
        progress++;
    }
    printf("Pairs Found: %d\n", pairs);
}

void CopyArray(int dest[], int source[], int length) {
    for(int i = 0; i < length; i++) {
        dest[i] = source[i];
    }
}

int RowSums(int a[]) {
    int Asums = 0;

    for(int i = 0; i < ORDER; i++) {
        Asums += a[i];
    }

    return Asums;
}

int Power(int base, int exponent) {
    int product = base;
    for(int i = 0; i < exponent - 1; i++) {
        product *= base;
    }
    return product;
}

void Reset(int arr[], int length) {
    for(int i = 0; i < length; i++) {
        arr[i] = 1;
    } 
}

//returns 0 if the array is already the last combination, returns 1 if the array was edited
int NextCombination(int arr[], int length) {
    //if the value is -1, need to re-traverse the tree
    if(arr[length - 1] == -1) {

        //find next root node that is value of 1
        int i = length - 1;
        while(arr[i] == -1) {
            if(i == 0) {
                return 0;
            }
            i--;
        }
        arr[i] = -1;
        
        //every node after this root should be value of 1 (considering that we are finding the next combination)
        i++;
        while(i < length) {
            arr[i] = 1;
            i++;
        }

        return 1;
    }
    //if the value is 1, then the next combination has the value as -1.
    if(arr[length - 1] == 1) {
        arr[length - 1] = -1;
        return 1;
    }
}

void PrintArray(int arr[], int length, FILE *fp) {
    fprintf(fp, "{");
    for(int i = 0; i < length - 1; i++) {
        fprintf(fp, "%d,", arr[i]);

    }
    
    fprintf(fp, "%d}\n", arr[length - 1]);
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



int * CompressSequence(int seq[]) {
    int * compression = (int*)malloc(ORDER / 2 * sizeof(int));
    for(int i = 0; i < ORDER / 2; i++) {
        compression[i] = seq[i] + seq[i + ORDER / 2];
        printf("%d", compression[i]);
    }

    printf("\n");
    
    return compression;
}

fftw_complex * dft(int seq[], int len) {
    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * len);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * len);

    for(int i = 0; i < len; i++) {
        in[i][0] = (double)seq[i];
    }

    p = fftw_plan_dft_1d(len, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p);

    fftw_destroy_plan(p);
    fftw_free(in);

    return out;
} 

int dftfilter(int seq[], int len) {
    fftw_complex * seqdft = dft(seq, len);
    for(int i = 0; i < len; i++) {
        if((seqdft[i][0] * seqdft[i][0] + seqdft[i][1] * seqdft[i][1]) > len * 2 + 0.001) {
            fftw_free(seqdft);
            return 0;
        }
    }
    fftw_free(seqdft);
    return 1;

}



