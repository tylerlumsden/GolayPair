#include<set>
#include<vector>
#include<math.h>
#include<stdio.h>
#include<fstream>

int getIndex(int element, std::set<int> alphabet);
std::vector<int> binaryReadSeq(std::ifstream& in, int len, std::set<int> alphabet);
void binaryWritePSD(std::ofstream& out, std::vector<double> psd, int bound);
void binaryWriteSeq(std::ofstream& out, std::vector<int> seq, std::set<int> alphabet);