#include<array>
#include"golay.h"


using namespace std;

int nextCombinationA(std::array<int, ORDER>& seq);
int nextCombinationB(std::array<int, ORDER>& seq);
int NextCombinationRowSums(array<int, ORDER>& arr, int length, int* currentSum);
int nextRowSums(array<int, 8>& seq, int start, int rowsum);