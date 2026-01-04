#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<map>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"fftw3.h"
#include"array.h"
#include"decomps.h"
#include"fourier.h"
#include"equivalence.h"
#include<tgmath.h>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<format>

#include"constants.h"
#include"match_pairs.h"
#include"sort.h"
#include <thread>


double norm(fftw_complex dft) {
    return dft[0] * dft[0] + dft[1] * dft[1];
}

int uncompress(std::vector<int> orig, const int COMPRESS, const int NEWCOMPRESS, std::ofstream& outfile, bool seqflag);

int uncompression_pipeline(const int ORDER, const int COMPRESS, const int NEWCOMPRESS, const std::string& TEMP_DIR) {
    std::string inputfile = std::format("{}/order-{}/{}-pairs-found_{}", TEMP_DIR, ORDER, ORDER, 1);

    std::ifstream input(inputfile);
    std::string line;

    std::string file_a = Constants::get_file_path_a(ORDER, TEMP_DIR);
    std::string file_b = Constants::get_file_path_b(ORDER, TEMP_DIR);
    std::ofstream outa(file_a);
    std::ofstream outb(file_b);

    while(std::getline(input, line)) {
        std::vector<int> seq;
        std::istringstream iss(line);
        std::string val;
        
        while(iss >> val) {
            seq.push_back(std::stoi(val));
        }

        std::vector<int> seqa;
        for(size_t i = 0; i < seq.size() / 2; i++) {
            seqa.push_back(seq[i]);
        }

        std::vector<int> seqb;
        for(size_t i = seq.size() / 2; i < seq.size(); i++) {
            seqb.push_back(seq[i]);
        }

        uncompress(seqa, 2, 1, outa, 1);
        uncompress(seqb, 2, 1, outb, 0);
    }
    
    return 0;
}

int uncompress(std::vector<int> orig, const int COMPRESS, const int NEWCOMPRESS, std::ofstream& outfile, bool seqflag) {
    const int ORDER = orig.size() * COMPRESS; 
    const int LEN = ORDER / COMPRESS;

    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (ORDER / NEWCOMPRESS));
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (ORDER / NEWCOMPRESS));
    p = fftw_plan_dft_1d((ORDER) / NEWCOMPRESS, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

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
    
    //shift original sequence such that the element with the largest number of permutations is in the front
    set<int> seta;
    for(int element : orig) {
        seta.insert(element);
    }

    size_t max = 0;
    int best;
    for(int element : seta) {
        if(partitions.at(element).size() > max) {
            max = partitions.at(element).size();
            best = element;
        }
    }
    for(size_t i = 0; i < orig.size(); i++) {
        if(orig[i] == best) {
            rotate(orig.begin(), orig.begin() + i, orig.end());
        }
    }

    set<vector<int>> perma;
    for(vector<int> perm : partitions.at(orig[0])) {
        set<vector<int>> equiv = generateUncompress(perm);
        perma.insert(*equiv.begin());
    }

    vector<vector<int>> newfirsta;
    for(vector<int> perm : perma) {
        newfirsta.push_back(perm);
    }

    vector<int> seq;
    seq.resize(ORDER / NEWCOMPRESS);

    unsigned long long int count = 0;
    int curr = 0;
    vector<int> stack(LEN, 0);

    while(curr != -1) {

        while(curr != LEN - 1) {

            std::vector<int> permutation = partitions.at(orig[curr])[stack[curr]];

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

            for(std::vector<int> permutation : partitions.at(orig[curr])) {

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
                    for(int i = 0; i < LEN / 2; i++) {
                        if(seqflag) {
                            outfile << (int)rint(norm(out[i]));
                        } else {
                            outfile << ORDER * 2 - (int)rint(norm(out[i]));
                        }
                    }
                    outfile << " ";
                    for(int val : seq) {
                        outfile << val << " ";
                    }
                    outfile << "\n";
                }
            }
            
            curr--;

            while((unsigned int)stack[curr] == partitions.at(orig[curr]).size() || (curr == 0 && (size_t)stack[curr] == newfirsta.size())) {
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

    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);
    return 0;
}