#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

int isOrderly(vector<int> base, set<vector<int>> generators);
set<vector<int>> constructGenerators(int flag);