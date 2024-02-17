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

int main(int argc, char ** argv) {

    int ORDER = stoi(argv[1]);
    int LEN = stoi(argv[2]);
    int procnum = stoi(argv[3]);
    

        char fname[100];
        sprintf(fname, "results/%d/%d-pairs-found_%d", ORDER, ORDER, procnum);
        FILE * out = fopen(fname, "w");

        std::ifstream res(fname);
        std::string a;
        std::string b;
        std::string arrayA;
        std::string arrayB;
        std::string temp;

        sprintf(fname, "results/%d/%d-candidates-a.sorted_%d", ORDER, ORDER, procnum);
        std::ifstream filea(fname);
        sprintf(fname, "results/%d/%d-candidates-b.sorted_%d", ORDER, ORDER, procnum);
        std::ifstream fileb(fname);

        vector<int> seqa;
        seqa.resize(LEN);
        vector<int> seqb;
        seqb.resize(LEN);

        vector<vector<int>> matchA;
        vector<vector<int>> matchB;

        if(filea.peek() == EOF) {
            printf("A file is empty.\n");
            return 1;
        }

        if(fileb.peek() == EOF) {
            printf("B file is empty.\n");
            return 1;
        }

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

                    for(vector<int> sequenceA : matchA) {
                        for(vector<int> sequenceB : matchB) {
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