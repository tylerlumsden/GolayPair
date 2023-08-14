#include<stdio.h>

void WritePairToFile(FILE * out, int a[], int b[], int len) {
    for(int i = 0; i < len; i++) {
        if(a[i] == 1) {
            fprintf(out, "+");
        }
        if(a[i] == -1) {
            fprintf(out, "-");
        }
    }

    fprintf(out, " ");

    for(int i = 0; i < len; i++) {
        if(b[i] == 1) {
            fprintf(out, "+");
        }
        if(b[i] == -1) {
            fprintf(out, "-");
        }
    }
    
    fprintf(out, "\n");
}

void Reset(int arr[], int len) {
    for(int i = 0; i < len; i++) {
        arr[i] = 1;
    } 
}

int RowSums(int a[], int len) {
    int Asums = 0;

    for(int i = 0; i < len; i++) {
        Asums += a[i];
    }

    return Asums;
}

void CopyArray(int dest[], int source[], int len) {
    for(int i = 0; i < len; i++) {
        dest[i] = source[i];
    }
}

int NextCombination(int arr[], int length) {
    //if the value is -1, need to re-traverse the tree
    if(arr[length - 1] == -1) {

        //find next root node that is value of 1
        int i = length - 1;
        while(arr[i] == -1) {
            if(i == 0) {
                return 0;
            }
            i--;
        }
        arr[i] = -1;
        
        //every node after this root should be value of 1 (considering that we are finding the next combination)
        i++;
        while(i < length) {
            arr[i] = 1;
            i++;
        }

        return 1;
    }
    //if the value is 1, then the next combination has the value as -1.
    if(arr[length - 1] == 1) {
        arr[length - 1] = -1;
        return 1;
    }
}

int NextCombinationRowSums(int arr[], int length, int currentSum, int bound) {
    do {
        if(currentSum > length || currentSum < -length) {
            printf("Error. currentSum out of bounds: %d\n", currentSum);
            return length + 1;
        }
        //if the value is -1, need to re-traverse the tree
        if(arr[length - 1] == -1) {
            //find next root node that is value of 1
            int i = length - 1;
            while(arr[i] == -1) {
                if(i == 0) {
                    return length + 1;
                }
                i--;
                currentSum++;
            }
            arr[i] = -1;
            currentSum -= 2;
            
            //every node after this root should be value of 1 (considering that we are finding the next combination)
            i++;
            while(i < length) {
                arr[i] = 1;
                i++;
                currentSum++;
            }

            continue;
        }
        //if the value is 1, then the next combination has the value as -1.
        if(arr[length - 1] == 1) {
            arr[length - 1] = -1;
            currentSum -= 2;
            continue;
        }

    } while(currentSum != bound);

    return currentSum;
}