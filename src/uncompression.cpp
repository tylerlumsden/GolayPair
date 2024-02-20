#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<map>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"../lib/fftw-3.3.10/api/fftw3.h"
#include"../lib/array.h"
#include"../lib/decomps.h"
#include"../lib/fourier.h"
#include<tgmath.h>
#include<algorithm>
#include<fstream>

double norm(fftw_complex dft) {
    return dft[0] * dft[0] + dft[1] * dft[1];
}

int main(int argc, char ** argv) {

    int ORDER = stoi(argv[3]);
    int COMPRESS = stoi(argv[4]);
    int NEWCOMPRESS = stoi(argv[5]);

    int LEN = ORDER / COMPRESS;

    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (ORDER / NEWCOMPRESS));
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (ORDER / NEWCOMPRESS));
    p = fftw_plan_dft_1d((ORDER) / NEWCOMPRESS, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    int linenumber = stoi(argv[1]);

    int procnum = stoi(argv[2]);

    char fname[100];
    sprintf(fname, "results/%d-pairs-found-%d", ORDER, procnum);
    std::ifstream file(fname);
    std::string line;
    std::string letter;

    if(!file) {
        printf("Bad file\n");
        return -1;
    }

    vector<int> origa;
    origa.resize(LEN);
    vector<int> origb;
    origb.resize(LEN);
    

    int i = 1;
    while(i < linenumber && getline(file, line)) {
        i++;
    }

    i = 0;
    while(file.good() && i < LEN) {
        file >> letter;
        origa[i] = stoi(letter);
        i++;
    }

    i = 0;
    while(file.good() && i < LEN) {
        file >> letter;
        origb[i] = stoi(letter);
        i++;
    }
    
    vector<int> seq;
    seq.resize(ORDER / NEWCOMPRESS);

    std::set<int> alphabet;

    if(COMPRESS % 2 == 0) {
        for(int i = 0; i <= COMPRESS; i += 2) {
            alphabet.insert(i);
            alphabet.insert(-i);
        }
    } else {
        for(int i = 1; i <= COMPRESS; i += 2) {
            alphabet.insert(i);
            alphabet.insert(-i);
        }
    }

    std::set<int> newalphabet;

    if(NEWCOMPRESS % 2 == 0) {
        for(int i = 0; i <= NEWCOMPRESS; i += 2) {
            newalphabet.insert(i);
            newalphabet.insert(-i);
        }
    } else {
        for(int i = 1; i <= NEWCOMPRESS; i += 2) {
            newalphabet.insert(i);
            newalphabet.insert(-i);
        }
    }


    std::vector<std::vector<int>> parts = getCombinations(COMPRESS / NEWCOMPRESS, newalphabet);
    std::vector<std::vector<int>> partition;

    std::map<int, std::vector<std::vector<int>>> partitions;

    //generate all permutations of possible decompositions for each letter in the alphabet
    for(int letter : alphabet) {
        partition.clear();
        for(std::vector<int> part : parts) {
            int sum = 0;
            for(long unsigned int i = 0; i < part.size(); i++) {
                sum += part[i];
            }
            if(sum == letter) {
                do {
                    partition.push_back(part);
                } while(next_permutation(part.begin(), part.end()));
            }
        }
        partitions.insert(make_pair(letter, partition));
    }
    
    sprintf(fname, "results/%d/%d-candidates-%d_%d", ORDER, ORDER, 0, procnum);
    FILE * outa = fopen(fname, "w");

    sprintf(fname, "results/%d/%d-candidates-%d_%d", ORDER, ORDER, 1, procnum);
    FILE * outb = fopen(fname, "w");

    int curr = 0;
    vector<int> stack(LEN, 0);

    while(curr != -1) {

        while(curr != LEN - 1) {
            std::vector<int> permutation = partitions.at(origa[curr])[stack[curr]];

            for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                seq[curr + (LEN * i)] = permutation[i];
            }
            stack[curr]++;
            curr++;
        }

        //if curr is final element of original sequence, base case
        if(curr == LEN - 1) {

            for(std::vector<int> permutation : partitions.at(origa[curr])) {

                for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                    seq[curr + (LEN * i)] = permutation[i];
                }

                for(unsigned int i = 0; i < seq.size(); i++) {
                    in[i][0] = (double)seq[i];
                    in[i][1] = 0;
                } 

                fftw_execute(p);

                if(dftfilter(out, seq.size(), ORDER)) { 
                    for(unsigned int i = 0; i < seq.size() / 2; i++) {
                        fprintf(outa, "%d",    (int)rint(norm(out[i])));
                    }
                    fprintf(outa, " ");
                    for(int num : seq) {
                            fprintf(outa, "%d ", num);
                    }
                    fprintf(outa, "\n");
                }
            }
            
            curr--;

            while(stack[curr] == partitions.at(origa[curr]).size()) {
                stack[curr] = 0;
                curr--;
                if(curr == -1) {
                    break;
                }
            }
        }
    }

    curr = 0;
    vector<int> stackb(LEN, 0);
    stack = stackb;

    while(curr != -1) {

        while(curr != LEN - 1) {
            std::vector<int> permutation = partitions.at(origb[curr])[stack[curr]];

            for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                seq[curr + (LEN * i)] = permutation[i];
            }
            stack[curr]++;
            curr++;
        }

        if(curr == LEN - 1) {

            for(std::vector<int> permutation : partitions.at(origb[curr])) {

                for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                    seq[curr + (LEN * i)] = permutation[i];
                }

                for(unsigned int i = 0; i < seq.size(); i++) {
                    in[i][0] = (double)seq[i];
                    in[i][1] = 0;
                } 

                fftw_execute(p);

                if(dftfilter(out, seq.size(), ORDER)) { 
                    for(unsigned int i = 0; i < seq.size() / 2; i++) {
                        fprintf(outb, "%d",    ORDER * 2 - (int)rint(norm(out[i])));
                    }
                    fprintf(outb, " ");
                    for(int num : seq) {
                            fprintf(outb, "%d ", num);
                    }
                    fprintf(outb, "\n");
                }
            }
            
            curr--;

            while(stack[curr] == partitions.at(origb[curr]).size()) {
                stack[curr] = 0;
                curr--;
                if(curr == -1) {
                    break;
                }
            }
        }
    }

    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);

    fclose(outa);
    fclose(outb);
}