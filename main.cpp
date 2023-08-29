#include<stdio.h>
#include"golay.h"

#define CHOICE 1

int main(int argc, char** argv) {    

    FILE * out = fopen("timings/order", "w");
    fprintf(out, "%d", ORDER);
    fclose(out);

    switch(CHOICE) {
        case 1:
            find_unique(argc, argv);
            break;
        default:
            //error
            break;
    }

}

void write_results_to_table() {
    char timing[200];

    FILE * classA = fopen("timings/classgeneration-0", "r");
    FILE * classB = fopen("timings/classgeneration-1", "r");
    FILE * matching = fopen("timings/matching", "r");
    FILE * total = fopen("timings/total", "r");

    //read each type into timing, then print it to a table

}