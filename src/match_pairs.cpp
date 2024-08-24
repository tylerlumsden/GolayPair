#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<array>
#include<time.h>
#include<iostream>
#include<vector>
#include<fstream>
#include"../lib/golay.h"
#include"../lib/binary.h"
#include<limits>
#include<set>
#include<stdlib.h>

int main(int argc, char ** argv) {

    int ORDER = stoi(argv[1]);
    int LEN = stoi(argv[2]);
    int procnum = stoi(argv[3]);

    int COMPRESS = ORDER / LEN;
    
    std::set<int> alphabet;

    for(int i = -COMPRESS; i <= COMPRESS; i = i + 2) {
        alphabet.insert(i);
    }   

    const int bits_per_element = (int)ceil(log(alphabet.size()));
    const int bytes = (int)ceil(LEN * bits_per_element / 8.0) + LEN / 2;

    char command[100];
    int returnval;

    sprintf(command, "bsort -k %d -r %d results/%d/%d-unique-filtered-a_%d", bytes, bytes, ORDER, ORDER, procnum);
    if(!system(NULL)) {
        printf("ERROR: No command processor available for sorting A\n"); 
        return 0;
    }
    returnval = system(command);
    printf("%d\n", returnval);

    sprintf(command, "bsort -k %d -r %d results/%d/%d-unique-filtered-b_%d", bytes, bytes, ORDER, ORDER, procnum);
    if(!system(NULL)) {
        printf("ERROR: No command processor available for sorting B\n"); 
        return 0;
    }
    returnval = system(command);
    printf("%d\n", returnval);

    printf("Matching\n");           

        char fname[100];
        sprintf(fname, "results/%d/%d-pairs-found_%d", ORDER, ORDER, procnum);
        FILE * out = fopen(fname, "w");

        std::ifstream res(fname);
        std::string arrayA;
        std::string arrayB;

        sprintf(fname, "results/%d/%d-unique-filtered-a_%d", ORDER, ORDER, procnum);
        std::ifstream filea(fname);
        sprintf(fname, "results/%d/%d-unique-filtered-b_%d", ORDER, ORDER, procnum);
        std::ifstream fileb(fname);


        vector<int> a;
        vector<int> b;
        vector<int> temp;

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

        a = binaryReadPSD(filea, LEN / 2);
        b = binaryReadPSD(fileb, LEN / 2);

        seqa = binaryReadSeq(filea, LEN, alphabet);
        seqb = binaryReadSeq(fileb, LEN, alphabet);

        while(filea.good() && fileb.good()) {

            //if a == b
            //get all sequences of a and b of those psd's in separate vectors
            //match all combinations of these vectors

            if(a == b) {
                //match the pairs
                    temp = a;

                    while(filea.good() && a == temp) {
                        matchA.push_back(seqa);
                        a = binaryReadPSD(filea, LEN / 2);
                        seqa = binaryReadSeq(filea, LEN, alphabet);
                    }

                    temp = b;

                    while(fileb.good() && b == temp) {
                        matchB.push_back(seqb);
                        b = binaryReadPSD(fileb, LEN / 2);
                        seqb = binaryReadSeq(fileb, LEN, alphabet);
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
                a = binaryReadPSD(filea, LEN / 2);
                seqa = binaryReadSeq(filea, LEN, alphabet);
            }

            else if(b < a) {
                //go to next line
                b = binaryReadPSD(fileb, LEN / 2);
                seqb = binaryReadSeq(fileb, LEN, alphabet);
            }
        }
}