#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"array.h"
#include"fftw-3.3.5-dll64/fftw3.h"
#include"decomps.h"
#include"golay.h"
#include"fourier.h"
#include"equivalence.h"

using namespace std;

void write_seq(FILE * out, array<int, ORDER> seq);
void write_unique_seq(FILE * out, int rowsum, int flag);
int check_if_pair(array<int, ORDER> a, array<int, ORDER> b);
void fill_from_string(array<int, ORDER>& seq, char str[]);
void match_pairs(FILE * a, FILE * b, FILE * out);

void find_unique(int argc, char** argv) {

    clock_t start = clock();

    if(decomps_len[ORDER] == 0) {
        printf("decomps_len == 0. There will be no pairs found.\n");
        return;
    } 
    FILE * out;
    char fname[100];

    for(int i = 0; i < decomps_len[ORDER]; i++) {
        printf("Running on decomps %d, %d\n", decomps[ORDER][i][0], decomps[ORDER][i][1]);

        printf("Generating classesA\n");

        sprintf(fname, "results/%d-unique-filtered-a-%d", ORDER, i);
        out = fopen(fname, "w+");
        write_unique_seq(out, decomps[ORDER][i][0], 0);

        printf("Time elapsed: %ld seconds\n", (clock() - start) / CLOCKS_PER_SEC);

        printf("Generating classesB\n");

        sprintf(fname, "results/%d-unique-filtered-b-%d", ORDER, i);
        out = fopen(fname, "w+");
        write_unique_seq(out, decomps[ORDER][i][1], 1);

        printf("Time elapsed: %ld seconds\n", (clock() - start) / CLOCKS_PER_SEC);

    }

    printf("Matching pairs\n");

    FILE * a;
    FILE * b;

    sprintf(fname, "results/%d-pairs-found", ORDER);
    out = fopen(fname, "w+");

    for(int i = 0; i < decomps_len[ORDER]; i++) {
        sprintf(fname, "results/%d-unique-filtered-a-%d", ORDER, i);
        a = fopen(fname, "r+");
        sprintf(fname, "results/%d-unique-filtered-b-%d", ORDER, i);
        b = fopen(fname, "r+");

        match_pairs(a, b, out);
    }

    sprintf(fname, "timings/total");
    out = fopen(fname, "w");

    fprintf(out, "%.1f", (clock() - start) / (float)CLOCKS_PER_SEC);

    fclose(out);

    printf("Time elapsed: %ld seconds\n", (clock() - start) / CLOCKS_PER_SEC);
}

void match_pairs(FILE * a, FILE * b, FILE * out) {
    int pairs = 0;

    char fname[100];
    sprintf(fname, "timings/matching");
    FILE * timing = fopen(fname, "w");  
    sprintf(fname, "timings/pairs");
    FILE * pair = fopen(fname, "w");

    clock_t start = clock();

    array<int, ORDER> seqa;
    array<int, ORDER> seqb;

    char stringa[ORDER + 2];
    char stringb[ORDER + 2];
    
    while(fgets(stringa, ORDER + 2, a)) {
        fill_from_string(seqa, stringa);

        while(fgets(stringb, ORDER + 2, b)) {
            fill_from_string(seqb, stringb);
            if(check_if_pair(seqa, seqb)) {
                write_seq(out, seqa);
                fprintf(out, " ");
                write_seq(out, seqb);
                fprintf(out, "\n");
                pairs++;
            }
        }
        rewind(b);
    }


    fprintf(pair, "%d", pairs);

    fclose(pair);
    fclose(a);
    fclose(b);
    fclose(out);

    fprintf(timing, "%.1f", (clock() - start) / (float)CLOCKS_PER_SEC);
}

int PAF(array<int, ORDER> seq, int s) { 
    int result = 0;
    for(int i = 0; i < ORDER; i++) {
        result = result + (seq[i] * seq[(i + s) % ORDER]);
    }
    return result;
}

int check_if_pair(array<int, ORDER> a, array<int, ORDER> b) {
    for(int i = 1; i <= ORDER / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != 0) {
            return 0;
        }
    }

    return 1;
}

void fill_from_string(array<int, ORDER>& seq, char str[]) {
    for(int i = 0; i < ORDER; i++) {
        if(str[i] == '+') {
            seq[i] = 1;
            continue;
        } 
        if(str[i] == '-') {
            seq[i] = -1;
            continue;
        }
    }
}

vector<set<array<int, ORDER>>> get_unique_classes(int rowsum, int flag) {
    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ORDER);
    plan = fftw_plan_dft_1d(ORDER, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    //generate sequences, return them
    vector<set<array<int,ORDER>>> classes;

    array<int, ORDER> seq;
    seq.fill(1);
    int currentSum = ORDER;

    do {
        out = dft(seq, in, out, plan);  
        if(dftfilter(out, ORDER)) {
            generate_equivalence_class(classes, seq);
        }
    } while(NextCombinationRowSums(seq, ORDER, &currentSum, rowsum));

    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(plan);

    return classes;
}

void write_unique_seq(FILE * out, int rowsum, int flag) {
    vector<set<array<int,ORDER>>> classes;

    char fname[100];
    sprintf(fname, "timings/classgeneration-%d", flag);
    FILE * timing = fopen(fname, "w");
    clock_t start = clock();

    classes = get_unique_classes(rowsum, flag);

    fprintf(timing, "%.1f", (clock() - start) / (float)CLOCKS_PER_SEC);
    fclose(timing);

    for(set<array<int,ORDER>> set : classes) {
        //write to file
        write_seq(out, *(set.begin()));
        fprintf(out, "\n");
    }
    fclose(out);
}

void write_seq(FILE * out, array<int, ORDER> seq) {
    for(int i = 0; i < ORDER; i++) {
        if(seq[i] == 1) {
            fprintf(out, "+");
            continue;
        }
        if(seq[i] == -1) {
            fprintf(out, "-");
            continue;
        }
    }
}
