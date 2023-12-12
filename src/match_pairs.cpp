#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<array>
#include<time.h>
#include<iostream>
#include<vector>
#include<fstream>
#include"../lib/golay.h"
#include<limits>

int main() {
    

        char fname[100];
        sprintf(fname, "results/%d-pairs-found", ORDER);
        FILE * out = fopen(fname, "w");

        std::ifstream res(fname);
        std::string a;
        std::string b;
        std::string arrayA;
        std::string arrayB;
        std::string temp;

        sprintf(fname, "results/%d-candidates-a.sorted", ORDER);
        std::ifstream filea(fname);
        sprintf(fname, "results/%d-candidates-b.sorted", ORDER);
        std::ifstream fileb(fname);

        array<int, LEN> seqa;
        array<int, LEN> seqb;

        vector<array<int, LEN>> matchA;
        vector<array<int, LEN>> matchB;

        filea >> a;
        fileb >> b;

        for(int i = 0; i < LEN; i++) {
            filea >> arrayA;
            seqa[i] = stoi(arrayA);
        }

        for(int i = 0; i < LEN; i++) {
            fileb >> arrayB;
            seqb[i] = stoi(arrayB);
        }


        while(filea.good() && fileb.good()) {

            //if a == b
            //get all sequences of a and b of those psd's in separate vectors
            //match all combinations of these vectors

            if(a == b) {
                //match the pairs
                    temp = a;

                    while(filea.good() && a == temp) {
                        matchA.push_back(seqa);
                        filea.ignore(std::numeric_limits<streamsize>::max(), '\n');
                        filea >> a;
                        for(int i = 0; i < LEN; i++) {
                            filea >> arrayA;
                            seqa[i] = stoi(arrayA);
                        }
                    }

                    while(fileb.good() && b == temp) {
                        matchB.push_back(seqb);
                        fileb.ignore(std::numeric_limits<streamsize>::max(), '\n');
                        fileb >> b;
                        for(int i = 0; i < LEN; i++) {
                            fileb >> arrayB;
                            seqb[i] = stoi(arrayB);
                        }
                    }

                    for(array<int, LEN> sequenceA : matchA) {
                        for(array<int, LEN> sequenceB : matchB) {
                            if(check_if_pair(sequenceA, sequenceB)) {
                                write_seq(out, sequenceA);
                                fprintf(out, " ");
                                write_seq(out, sequenceB);
                                fprintf(out, "\n");
                            }
                        }
                    }

                    matchA.clear();
                    matchB.clear();
            }

            else if(a < b) {
                //go to next line
                filea.ignore(std::numeric_limits<streamsize>::max(), '\n');
                filea >> a;
                for(int i = 0; i < LEN; i++) {
                    filea >> arrayA;
                    seqa[i] = stoi(arrayA);
                }
            }

            else if(b < a) {
                //go to next line
                fileb.ignore(std::numeric_limits<streamsize>::max(), '\n');
                fileb >> b;
                for(int i = 0; i < LEN; i++) {
                    fileb >> arrayB;
                    seqb[i] = stoi(arrayB);
                }
            }
        }
}