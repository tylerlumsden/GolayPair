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

void uncompressIndex(std::map<int, std::vector<std::vector<int>>>& permutations, std::array<int, LEN> orig, std::vector<int>& seq, int len, FILE * outfile, fftw_complex * in, fftw_complex * out, fftw_plan p, int flag, int newcompress) {

    if(len == 1) { 
        for(std::vector<int> permutation : permutations.at(orig[LEN - len])) {
            for(unsigned int i = 0; i < COMPRESS / newcompress; i++) {
                seq[LEN - len + (LEN * i)] = permutation[i];
            }

            for(unsigned int i = 0; i < seq.size(); i++) {
                in[i][0] = (double)seq[i];
                in[i][1] = 0;
            } 

            fftw_execute(p);

            if(dftfilter(out, seq.size())) { 

                if(flag == 0) {
                    for(unsigned int i = 0; i < seq.size() / 2; i++) {
                        fprintf(outfile, "%d",    (int)rint(norm(out[i])));
                    }
                    fprintf(outfile, " ");
                    for(int num : seq) {
                        fprintf(outfile, "%d ", num);
                    }
                    fprintf(outfile, "\n");
                }

                if(flag == 1) {
                    for(unsigned int i = 0; i < seq.size() / 2; i++) {
                        fprintf(outfile, "%d",   ORDER * 2 - (int)rint(norm(out[i])));
                    }
                    fprintf(outfile, " ");
                    for(int num : seq) {
                        fprintf(outfile, "%d ", num);
                    }
                    fprintf(outfile, "\n");
                }
            }
        }
        
        return;
    }

    for(std::vector<int> permutation : permutations.at(orig[LEN - len])) {
        for(int i = 0; i < COMPRESS / newcompress; i++) {
            seq[LEN - len + (LEN * i)] = permutation[i];
        }
        uncompressIndex(permutations, orig, seq, len - 1, outfile, in, out, p, flag, newcompress);
    }
}

int main(int argc, char ** argv) {

    int newcompress = stoi(argv[2]);

    fftw_complex *in, *out;
    fftw_plan plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (ORDER / newcompress));
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (ORDER / newcompress));
    plan = fftw_plan_dft_1d((ORDER) / newcompress, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    int linenumber = stoi(argv[1]);

    char fname[100];
    sprintf(fname, "results/%d-pairs-found", ORDER);
    std::ifstream file(fname);
    std::string line;
    std::string letter;

    if(!file) {
        printf("Bad file\n");
        return -1;
    }

    array<int, LEN> origa;
    array<int, LEN> origb;

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
    seq.resize(ORDER / newcompress);

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

    if(newcompress % 2 == 0) {
        for(int i = 0; i <= newcompress; i += 2) {
            newalphabet.insert(i);
            newalphabet.insert(-i);
        }
    } else {
        for(int i = 1; i <= newcompress; i += 2) {
            newalphabet.insert(i);
            newalphabet.insert(-i);
        }
    }




    std::vector<std::vector<int>> parts = getCombinations(COMPRESS / newcompress, newalphabet);
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

    sprintf(fname, "results/%d-unique-filtered-%d", ORDER, 0);
    FILE * outa = fopen(fname, "a");

    sprintf(fname, "results/%d-unique-filtered-%d", ORDER, 1);
    FILE * outb = fopen(fname, "a");

    uncompressIndex(partitions, origa, seq, LEN, outa, in, out, plan, 0, newcompress);
    uncompressIndex(partitions, origb, seq, LEN, outb, in, out, plan, 1, newcompress);

    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(plan);

    fclose(outa);
    fclose(outb);
}