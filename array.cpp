#include<stdio.h>
#include<array>
#include<algorithm>
#include"golay.h"

using namespace std;

int NextCombinationRowSums(array<int, ORDER>& arr, int length, int* currentSum) {
        if((*currentSum) > length || (*currentSum) < -length) {
            printf("Error. currentSum out of bounds: %d\n", *currentSum);
            return 0;
        }
        //if the value is -1, need to re-traverse the tree
        if(arr[length - 1] == 1) {
            //find next root node that is value of 1
            int i = length - 1;
            while(arr[i] == 1) {
                if(i == 0) {
                    return 0;
                }
                i--;
                (*currentSum)--;
            }
            arr[i] = 1;
            (*currentSum) += 2;
            
            //every node after this root should be value of 1 (considering that we are finding the next combination)
            i++;
            while(i < length) {
                arr[i] = -1;
                i++;
                (*currentSum)--;
            }

            return 1;
        }
        //if the value is 1, then the next combination has the value as -1.
        if(arr[length - 1] == -1) {
            arr[length - 1] = 1;
            (*currentSum) += 2;
            return 1;
        }


    return 1;
}

int seqIsLargest(array<int, 8> seq, int start, int rowsum) {
    for(int i = start; i < start + rowsum; i++) {
        if(seq[i] == -1) {
            return 0;
        }
    }
    return 1;
}

//---+++++

void resetSeq(array<int, 8>& seq, int start, unsigned int rowsum) {
    for(unsigned int i = start; i < seq.size(); i++) {
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
    for(unsigned int i = start; i < seq.size(); i++) {
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

//assumes that there are 7 +/- 3's and 23 +/- 1's in the sequence, the smallest is the sequence with only negative values.
int nextCombinationA(std::array<int, ORDER>& seq) {
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

int nextCombinationB(std::array<int, ORDER>& seq) {
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
    
    if(countOne == 22 && countThree == 8) {
        return 0;
    } 
    
    else if(countOne == 22) {
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