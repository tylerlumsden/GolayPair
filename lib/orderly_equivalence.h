#include<vector>
#include<set>
#include<array>
#include"golay.h"

using namespace std;

int isOrderly(array<int, LEN> base, set<array<int, LEN>> generators);
set<array<int, LEN>> constructGenerators(int flag);