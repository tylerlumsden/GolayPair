#define ORDER 20

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int PAF(int seq[], int s);
int CheckIfPair(int a[], int b[]);
int* CompressSequence(int a[]);
int NextCombination(int arr[], int length);
void PrintArray(int arr[], int length);
void Reset(int arr[], int length);
int Power(int base, int exponent);

int main() {

    int pairs = 0;
    int combinations = Power(2, ORDER);

    int a[ORDER];
    int b[ORDER];

    Reset(a, ORDER);
    Reset(b, ORDER);

    int progress = 0;

    clock_t start = clock();
    clock_t current;
    while(1) {
        current = clock();
            printf("Progress: %d ... %d, time elapsed: %d seconds\n", progress, combinations - 1, (current - start) / CLOCKS_PER_SEC);
            fflush(stdin);
        while(1) {
            if(CheckIfPair(a,b)) {
                printf("Pair Found: ");
                PrintArray(a, ORDER);
                PrintArray(b, ORDER);
                printf("\n");
                pairs++;
            }
            if(!NextCombination(b,ORDER)) {
                break;
            }
        }
        Reset(b, 3);
        if(!NextCombination(a,ORDER)) {
            break;
        }
        progress++;
    }
    printf("Pairs Found: %d\n", pairs);
}

int Power(int base, int exponent) {
    int product = base;
    for(int i = 0; i < exponent - 1; i++) {
        product *= base;
    }
    return product;
}

void Reset(int arr[], int length) {
    for(int i = 0; i < length; i++) {
        arr[i] = 1;
    } 
}

//returns 0 if the array is already the last combination, returns 1 if the array was edited
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

void PrintArray(int arr[], int length) {
    printf("{");
    for(int i = 0; i < length - 1; i++) {
        printf("%d, ", arr[i]);
    } 
    
    printf("%d} ", arr[length - 1]);
}

int PAF(int seq[], int s) { 

    int result = 0;
    for(int i = 0; i < ORDER; i++) {
        result = result + (seq[i] * seq[(i + s) % ORDER]);
    }
    return result;
}

int CheckIfPair(int a[], int b[]) {
    for(int i = 1; i <= ORDER / 2; i++) {
        if(PAF(a, i) + PAF(b, i) != 0) {
            return 0;
        }
    }

    return 1;
}



int * CompressSequence(int seq[]) {
    int * compression = (int*)malloc(ORDER / 2 * sizeof(int));
    for(int i = 0; i < ORDER / 2; i++) {
        compression[i] = seq[i] + seq[i + ORDER / 2];
        printf("%d", compression[i]);
    }

    printf("\n");
    
    return compression;
}

