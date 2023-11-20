#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

vector<array<int, LEN>> generateClass(array<int, LEN> seq, int flag);
set<GolayPair> generateClassPairs(GolayPair seq);