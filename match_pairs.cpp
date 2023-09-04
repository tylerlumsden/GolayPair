#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<array>
#include<time.h>
#include"decomps.h"
#include"golay.h"

using namespace std;

int main() {

    char fname[100];
    sprintf(fname, "results/%d-pairs-found", ORDER);
    FILE * out = fopen(fname, "w");
    
    for(int i = 0; i < decomps_len[ORDER]; i++) {

        sprintf(fname, "results/%d-unique-filtered-a-%d", ORDER, i);
        FILE * a = fopen(fname, "r");
        sprintf(fname, "results/%d-unique-filtered-b-%d", ORDER, i);
        FILE * b = fopen(fname, "r");

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
                }
            }
            rewind(b);
        }
        fclose(a);
        fclose(b);
    }
}