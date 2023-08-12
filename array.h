#include<stdio.h>

//array helper functions
void WritePairToFile(FILE * out, int a[], int b[], int len);
void Reset(int arr[], int len);
int RowSums(int a[], int len);
void CopyArray(int dest[], int source[], int len);
int NextCombination(int arr[], int length);