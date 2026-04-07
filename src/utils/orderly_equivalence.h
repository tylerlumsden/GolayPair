#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

int isCanonical(const std::vector<int>& seq, const set<vector<int>>& generators); 
bool partialCanonical(vector<int> base);
set<vector<int>> constructGenerators(int flag, int LEN);