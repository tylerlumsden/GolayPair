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
#include"output.h"
#include <thread>
#include <filesystem>

int uncompress(std::vector<int> orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, std::ofstream& outfile, bool seqflag);

int uncompression_pipeline(const int ORDER, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, std::ifstream& IN_PAIRS, std::ofstream& OUT_PAIRS, const std::string& WORK_DIR) {
    unsigned long long count = 1;

    const std::string FILE_A = std::format("{}/{}-uncompressed-a", WORK_DIR, ORDER);
    const std::string FILE_B = std::format("{}/{}-uncompressed-b", WORK_DIR, ORDER);
    const std::string FILE_A_SORTED = FILE_A + ".sorted";
    const std::string FILE_B_SORTED = FILE_B + ".sorted";

    std::string line;

    while(std::getline(IN_PAIRS, line)) {
        std::cout << "Uncompressing line: " << count << "\n";

        std::ofstream outa(FILE_A);
        std::ofstream outb(FILE_B);

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

        uncompress(seqa, COMPRESS, NEWCOMPRESS, PAF_CONSTANT, outa, 1);
        uncompress(seqb, COMPRESS, NEWCOMPRESS, PAF_CONSTANT, outb, 0);
        outa.close();
        outb.close();

        GNU_sort(FILE_A, FILE_A_SORTED);
        GNU_sort(FILE_B, FILE_B_SORTED);
        std::ifstream ina(FILE_A_SORTED);
        std::ifstream inb(FILE_B_SORTED);
        match_pairs(ORDER, NEWCOMPRESS, PAF_CONSTANT, ina, inb, OUT_PAIRS);

        count++;
    }

    return 0;
}

int uncompress(std::vector<int> orig, const int COMPRESS, const int NEWCOMPRESS, const int PAF_CONSTANT, std::ofstream& outfile, bool seqflag) {
    const int ORDER = orig.size() * COMPRESS; 
    const int LEN = ORDER / COMPRESS;

    Fourier FourierManager = Fourier(ORDER / NEWCOMPRESS);

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
    int best = orig[0];
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
    unsigned long long int written = 0;
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

                std::vector<double> psd = FourierManager.calculate_psd(seq);

                if(FourierManager.psd_filter(psd, ORDER, PAF_CONSTANT)) { 
                    written++;
                    if(seqflag) {
                        write_seq_psd(seq, psd, outfile);
                    } else {
                        write_seq_psd_invert(seq, psd, outfile, ORDER * 2 - PAF_CONSTANT);
                    }
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

    return 0;
}