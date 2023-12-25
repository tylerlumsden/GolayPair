#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

int isCanonical(vector<int> seq, set<vector<int>> generators); 
bool partialCanonical(vector<int> base);
set<vector<int>> constructGenerators(int flag);