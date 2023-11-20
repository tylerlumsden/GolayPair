#include<array>
#include<vector>
#include"golay.h"


using namespace std;


int NextCombination(array<int, LEN>& arr, int length);
int nextCombinationA(std::array<int, LEN>& seq);
int nextCombinationB(std::array<int, LEN>& seq);
int NextCombinationRowSums(array<int, LEN>& arr, int length, int* currentSum);
int nextRowSums(array<int, 8>& seq, int start, int rowsum);
array<int, LEN> getPermutationK(int k, vector<int> seq);
long long calculateBinomialCoefficient(int n, int k);
std::vector<std::vector<int>> getCombinations(int len, std::set<int> alphabet);