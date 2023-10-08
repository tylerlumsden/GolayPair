#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

set<array<int, ORDER>> generateClass(array<int, ORDER> seq, int flag);
vector<GolayPair> generateClassPairs(GolayPair seq);