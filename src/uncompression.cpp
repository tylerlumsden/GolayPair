#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<map>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"fftw3.h"
#include"../lib/array.h"
#include"../lib/decomps.h"
#include"../lib/fourier.h"
#include"../lib/equivalence.h"
#include<tgmath.h>
#include<algorithm>
#include<fstream>
#include"../lib/binary.h"

double norm(fftw_complex dft) {
    return dft[0] * dft[0] + dft[1] * dft[1];
}

int main(int argc, char ** argv) {

    int ORDER = stoi(argv[3]);
    int COMPRESS = stoi(argv[4]);
    int NEWCOMPRESS = stoi(argv[5]);

    int LEN = ORDER / COMPRESS;

    printf("Uncompressing sequence of length %d\n", LEN);

    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (ORDER / NEWCOMPRESS));
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (ORDER / NEWCOMPRESS));
    p = fftw_plan_dft_1d((ORDER) / NEWCOMPRESS, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    int linenumber = stoi(argv[1]);

    int procnum = stoi(argv[2]);

    char fname[100];

    if(procnum == 0) {
        sprintf(fname, "results/%d-pairs-found", ORDER);
    } else {
        sprintf(fname, "results/%d-pairs-found-%d", ORDER, procnum);
    }

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
    
    sprintf(fname, "results/%d/%d-unique-filtered-a_%d", ORDER, ORDER, procnum);
    std::ofstream outa(fname);
    
    sprintf(fname, "results/%d/%d-unique-filtered-b_%d", ORDER, ORDER, procnum);
    std::ofstream outb(fname);
    
    //shift original sequence such that the element with the largest number of permutations is in the front
    set<int> seta;
    for(int element : origa) {
        seta.insert(element);
    }

    set<int> setb;
    for(int element : origb) {
        setb.insert(element);
    }
    

    int max = 0;
    int best;
    for(int element : seta) {
        if(partitions.at(element).size() > max) {
            max = partitions.at(element).size();
            best = element;
        }
    }
    for(int i = 0; i < origa.size(); i++) {
        if(origa[i] == best) {
            rotate(origa.begin(), origa.begin() + i, origa.end());
        }
    }

    max = 0;
    for(int element : setb) {
        if(partitions.at(element).size() > max) {
            max = partitions.at(element).size();
            best = element;
        }
    }
    for(int i = 0; i < origb.size(); i++) {
        if(origb[i] == best) {
            rotate(origb.begin(), origb.begin() + i, origb.end());
        }
    }

    set<vector<int>> perma;
    for(vector<int> perm : partitions.at(origa[0])) {
        set<vector<int>> equiv = generateUncompress(perm);
        perma.insert(*equiv.begin());
    }

    vector<vector<int>> newfirsta;
    for(vector<int> perm : perma) {
        newfirsta.push_back(perm);
    }

    set<vector<int>> permb;
    for(vector<int> perm : partitions.at(origb[0])) {
        set<vector<int>> equiv = generateUncompress(perm);
        permb.insert(*equiv.begin());
    }

    vector<vector<int>> newfirstb;
    for(vector<int> perm : permb) {
        newfirstb.push_back(perm);
    }

    //partitions = partitionsA;

    unsigned long long int count = 0;
    int curr = 0;
    vector<int> stack(LEN, 0);
    
    printf("Uncompressing A\n");

    while(curr != -1) {

        while(curr != LEN - 1) {

            std::vector<int> permutation = partitions.at(origa[curr])[stack[curr]];

            if(curr == 0) {
                permutation = newfirsta[stack[curr]];
            }

            for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                seq[curr + (LEN * i)] = permutation[i];
            }
            stack[curr]++;
            curr++;
        }

        //if curr is final element of original sequence, base case
        if(curr == LEN - 1) {

            for(std::vector<int> permutation : partitions.at(origa[curr])) {

                count++;

                for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                    seq[curr + (LEN * i)] = permutation[i];
                }

                for(unsigned int i = 0; i < seq.size(); i++) {
                    in[i][0] = (double)seq[i];
                    in[i][1] = 0;
                } 

                fftw_execute(p);

                if(dftfilter(out, seq.size(), ORDER)) {

                    std::vector<double> psd;
                    psd.reserve(seq.size());
                    for(size_t i = 0; i < seq.size(); i++) {
                         psd.push_back(norm(out[i]));
                    }

                    binaryWritePSD(outa, psd, 2 * ORDER);
                    binaryWriteSeq(outa, seq, newalphabet);
                }
            }
            
            curr--;

            while((unsigned int)stack[curr] == partitions.at(origa[curr]).size() || (curr == 0 && stack[curr] == newfirsta.size())) {
                stack[curr] = 0;
                curr--;
                if(curr == -1) {
                    curr = -1;
                    break;
                }
            }
            //printf("curr: %d, stack: %d\n", curr, stack[curr]);
        }
    }

    printf("%llu A sequences checked\n", count);
    count = 0;
    
    curr = 0;
    vector<int> stackb(LEN, 0);
    stack = stackb;

    //partitions = partitionsB;


    
    while(curr != -1) {

        while(curr != LEN - 1) {
            std::vector<int> permutation = partitions.at(origb[curr])[stack[curr]];

            if(curr == 0) {
                permutation = newfirstb[stack[curr]];
            }

            for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                seq[curr + (LEN * i)] = permutation[i];
            }
            stack[curr]++;
            curr++;
        }

        if(curr == LEN - 1) {

            for(std::vector<int> permutation : partitions.at(origb[curr])) {

                count++;

                for(int i = 0; i < COMPRESS / NEWCOMPRESS; i++) {
                    seq[curr + (LEN * i)] = permutation[i];
                }

                for(unsigned int i = 0; i < seq.size(); i++) {
                    in[i][0] = (double)seq[i];
                    in[i][1] = 0;
                } 

                fftw_execute(p);

                if(dftfilter(out, seq.size(), ORDER)) { 
                    std::vector<double> psd;
                    psd.reserve(seq.size());
                    for(size_t i = 0; i < seq.size(); i++) {
                         psd.push_back(ORDER * 2 - norm(out[i]));
                    }

                    binaryWritePSD(outb, psd, 2 * ORDER);
                    binaryWriteSeq(outb, seq, newalphabet);
                }
            }
            
            curr--;

            while((unsigned int)stack[curr] == partitions.at(origb[curr]).size() || (curr == 0 && stack[curr] == newfirstb.size())) {
                stack[curr] = 0;
                curr--;
                if(curr == -1) {
                    curr = -1;
                    break;
                }
            }
        }
    }

    printf("%llu B sequences checked\n", count);
    count = 0;
    
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);
}