#include<vector>
#include<set>
#include<array>
#include<functional>
#include"golay.h"

using namespace std;

set<vector<int>> generateUncompress(vector<int> seq);
set<GolayPair> generateClassPairs(set<GolayPair> generators, GolayPair seq);
set<GolayPair> constructGenerators(int LEN, const std::vector<std::function<set<GolayPair>(set<GolayPair>&)>>& equivalences);
set<GolayPair> generateExhaust(GolayPair seq, const std::vector<std::function<set<GolayPair>(set<GolayPair>&)>>& equivalences);
set<GolayPair> shift_pair(set<GolayPair>& map);
set<GolayPair> decimate_pair(set<GolayPair>& map, const std::vector<int>& coprimes);
set<GolayPair> reverse_pair(set<GolayPair>& map);
set<GolayPair> altnegative_pair(set<GolayPair>& map);
set<GolayPair> negate_pair(set<GolayPair>& map);
set<GolayPair> swap_pair(set<GolayPair>& map);