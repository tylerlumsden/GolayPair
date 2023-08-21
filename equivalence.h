#include<stdio.h>
#include<unordered_map>
#include<vector>

using namespace std;

void generate_equivalence_class(vector<unordered_map<vector<int>, int>>& map, vector<int> seq);
void shift_equivalence(unordered_map<vector<int>, int>& map, vector<int> seq);