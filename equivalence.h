#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

void shift_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void negative_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void altnegative_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void unishift_equivalence(set<array<int,ORDER>>& map, array<int,ORDER> seq);
void generate_equivalence_class(vector<set<array<int, ORDER>>>& classes, array<int, ORDER> seq);