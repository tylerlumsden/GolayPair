#include<vector>
#include<set>
#include<array>
#include"golay.h"
#include<unordered_set>

using namespace std;

set<array<int, ORDER>> generateClass(array<int, ORDER> seq, int flag);
unordered_set<GolayPair> generateClassPairs(GolayPair seq);