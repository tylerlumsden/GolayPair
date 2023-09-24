#include<algorithm>
#include<stdio.h>
#include<array>
#include<time.h>

#define ORDER 30

void printseq(std::array<int, ORDER> seq) {
    for(unsigned int i = 0; i < ORDER; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
}

//assumes that there are 7 +/- 3's and 23 +/- 1's in the sequence, the smallest is the sequence with only negative values.
int nextCombination(std::array<int, ORDER>& seq) {
    int countThree = 0;
    int countOne = 0;
    for(int i = 0; i < ORDER; i++) {
        if(seq[i] == 3) {
            countThree++;
        }
        if(seq[i] == 1) {
            countOne++;
        }
    }
    
    if(countOne == 23 && countThree == 7) {
        return 0;
    } 
    
    else if(countOne == 23) {
        for(int i = 0; i < ORDER; i++) {
            if(seq[i] == 1) {
                seq[i] = -1;
            }
        }

        for(int i = 0; i < ORDER; i++) {
            if(seq[i] == -3) {
                seq[i] = 3;
                break;
            }
        }
    } 
    

    else {
        for(int i = 0; i < ORDER; i++) {
            if(seq[i] == -1) {
                seq[i] = 1;
                break;
            }
        }
    }

    std::sort(seq.begin(), seq.end());

    return 1;
}

int main() {

    std::array<int, ORDER> seq;

    seq.fill(-1);

    for(int i = 0; i < 7; i++) {
        seq[i] = -3;
    }

    do {
        printseq(seq);
    } while(nextCombination(seq));

    /*

    int count = 1;

    std::sort(seq.begin(), seq.end());

    do {
        count++;
    } while(std::next_permutation(seq.begin(), seq.end()));


    printf("%d, %ld seconds", count, (clock() - start) / CLOCKS_PER_SEC);
    */

}

//1
//4
//6
//4
//1
// = 16