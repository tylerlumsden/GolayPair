#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

set<vector<int>> generateUncompress(vector<int> seq);
set<GolayPair> generateClassPairs(set<GolayPair> generators, GolayPair seq);
set<GolayPair> constructGenerators(int LEN);