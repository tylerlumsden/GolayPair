#include<stdio.h>
#include<array>

using namespace std;

/*
{- - - - + + + -}
-->
{- - - + - + + -}

recursive approach 
--> take the largest degree +, find the next largest row sums - 1 of the sub array below that plus.
*/

int seqIsLargest(array<int, 8> seq, int start, int rowsum) {
    for(int i = start; i < start + rowsum; i++) {
        if(seq[i] == -1) {
            return 0;
        }
    }
    return 1;
}

//---+++++

void resetSeq(array<int, 8>& seq, int start, int rowsum) {
    for(int i = start; i < seq.size(); i++) {
        if((seq.size() - i) < rowsum) {
            seq[i] = 1;
        } else {
            seq[i] = -1;
        }
    }
}

int nextRowSums(array<int, 8>& seq, int start, int rowsum) {

    if(seqIsLargest(seq, start, rowsum)) {
        //printf("Largest\n");
        return 0;
    }

    //find first plus
    int first;
    for(int i = start; i < seq.size(); i++) {
        if(seq[i] == 1) {
            first = i;
            break;
        }
    }

    //printf("first: %d\n", first);

    //find next seq of subarray after this plus
    //probably wont work due to indexxing issues
    if(!nextRowSums(seq, first + 1, rowsum - 1)) {
        seq[first] = -1;
        seq[first - 1] = 1;
        //reset rest of sequence
        resetSeq(seq, first + 1, rowsum);
        return 1;
    } else {
        return 1;
    }
}

void printArray(array<int, 8> seq) {
    for(int i = 0; i < seq.size(); i++) {
        if(seq[i] == 1) {
            printf("+");
        }
        if(seq[i] == -1) {
            printf("-");
        }
    }
}

int main() {
    array<int, 8> seq = {-1, -1, 1, 1, 1, 1, 1, 1};

    do {
        printArray(seq);
        printf("\n");
        
    } while(nextRowSums(seq, 0, 6));

}