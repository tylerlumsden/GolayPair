#include<stdio.h>
#include<vector>
using namespace std;

//array helper functions
void WritePairToFile(FILE * out, int a[], int b[], int len);
void Reset(int arr[], int len);
int RowSums(int a[], int len);
void CopyArray(int dest[], int source[], int len);
int NextCombination(int arr[], int length);
int NextCombinationRowSums(int arr[], int length, int currentSum, int bound);
int VecNextCombinationRowSums(vector<int>& arr, int currentSum, int bound);
void resetVec(vector<int>& seq);
void printVec(const vector<int>& vec);
void WriteVecPairToFile(FILE * out, vector<int> a, vector<int> b);