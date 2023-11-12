#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

vector<array<int, ORDER>> generateClass(array<int, ORDER> seq, int flag);
set<GolayPair> generateClassPairs(GolayPair seq);