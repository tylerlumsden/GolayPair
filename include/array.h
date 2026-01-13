#include<array>
#include<vector>
#include"golay.h"


using namespace std;


int NextCombination(vector<int>& arr, int length);
int nextCombinationA(std::vector<int>& seq);
int nextCombinationB(std::vector<int>& seq);
int NextCombinationRowSums(vector<int>& arr, int length, int* currentSum);
vector<int> getPermutationK(int k, vector<int> seq);
long long calculateBinomialCoefficient(int n, int k);
std::vector<std::vector<int>> getCombinations(int len, std::set<int> alphabet);