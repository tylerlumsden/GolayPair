#include<stdio.h>
#include<array>
#include"golay.h"

using namespace std;

int NextCombinationRowSums(array<int, ORDER>& arr, int length, int* currentSum, int bound) {
    do {
        if((*currentSum) > length || (*currentSum) < -length) {
            printf("Error. currentSum out of bounds: %d\n", *currentSum);
            return 0;
        }
        //if the value is -1, need to re-traverse the tree
        if(arr[length - 1] == -1) {
            //find next root node that is value of 1
            int i = length - 1;
            while(arr[i] == -1) {
                if(i == 0) {
                    return 0;
                }
                i--;
                (*currentSum)++;
            }
            arr[i] = -1;
            (*currentSum) -= 2;
            
            //every node after this root should be value of 1 (considering that we are finding the next combination)
            i++;
            while(i < length) {
                arr[i] = 1;
                i++;
                (*currentSum)++;
            }

            continue;
        }
        //if the value is 1, then the next combination has the value as -1.
        if(arr[length - 1] == 1) {
            arr[length - 1] = -1;
            (*currentSum) -= 2;
            continue;
        }

    } while((*currentSum) != bound);

    return 1;
}