#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<array>
#include<time.h>
#include<iostream>
#include<fstream>
#include"../decomps.h"
#include"../golay.h"
#include<limits>

int main() {
    
    for(int i = 0; i < decomps_len[ORDER]; i++) {

        char fname[100];
        sprintf(fname, "results/%d-pairs-found", ORDER);
        FILE * out = fopen(fname, "w");

        std::ifstream res(fname);
        std::string a;
        std::string b;
        std::string arrayA;
        std::string arrayB;

        sprintf(fname, "results/%d-unique-filtered-a-%d", ORDER, i);
        std::ifstream filea(fname);
        sprintf(fname, "results/%d-unique-filtered-b-%d", ORDER, i);
        std::ifstream fileb(fname);

        array<int, ORDER> seqa;
        array<int, ORDER> seqb;

        while(filea.good()) {

            filea >> a;

            for(int i = 0; i < ORDER; i++) {
                filea >> arrayA;
                
                seqa[i] = stoi(arrayA);
            }


            while(fileb.good()) {

                fileb >> b; 

                if(a == b) {
                    for(int i = 0; i < ORDER; i++) {

                        fileb >> arrayB;

                        seqb[i] = stoi(arrayB);
                    }

                    if(check_if_pair(seqa, seqb)) {
                        write_seq(out, seqa);
                        fprintf(out, " ");
                        write_seq(out, seqb);
                        fprintf(out, "\n");
                    }
                }

                fileb.ignore(std::numeric_limits<streamsize>::max(), '\n');
        
            }
            fileb.clear();
            fileb.seekg(0);
        }
        filea.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }
}