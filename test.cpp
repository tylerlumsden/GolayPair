#include<algorithm>
#include<stdio.h>
#include<vector>
#include<array>
#include<time.h>
#include<set>
#include"lib/orderly_equivalence.h"
#include"lib/equivalence.h"
#include"lib/golay.h"
#include<ctime>
#include<stack>

template<class BidirIt>
bool nextPermutation(BidirIt first, BidirIt last, set<int> alphabet) {
    int min = *std::min_element(alphabet.begin(), alphabet.end());
    int max = *std::max_element(alphabet.begin(), alphabet.end());

    last = last - 1;

    auto curr = last;

    if(*curr != max) {

        *curr = *curr + 2;
        return true;

    } else if(*curr == max) {

        while(curr != first - 1) {
            if(*curr != max) {
                *curr = *curr + 2;
                curr++;
                while(curr != last + 1) {
                    *curr = min;
                    curr++;
                }
                return true;
            }
            curr--;
        }
        return false;
        
    }
}

bool searchTree(vector<int> seq, int num, int len) {
    if(seq.size() == len) {
        return true;
    }

    seq.push_back(num);

    searchTree(seq, 1, len);
    searchTree(seq, -1, len);

    return false;
}

bool nextBranch(vector<int>& seq, int len) {

        if(seq.size() == len) {
            while(seq.size() != 0 && seq[seq.size() - 1] == 1) {
                seq.pop_back();
            }
            if(seq.size() == 0) {
                return false;
            }
            seq.pop_back();
            seq.push_back(1);
        } else {
            seq.push_back(-1);
        }
    
    return true;

}

int main() {


    unsigned long long count = 0;

    clock_t start = clock();

    stack<int> stack;

    vector<int> seq;

    printf("%d\n", seq.size());


    while(nextBranch(seq, 26)) {
         if(seq.size() == 26) {
            count++;
         }
    }

    printf("test\n");

    printf("Done %ld seconds, %llu\n", (clock() - start) / CLOCKS_PER_SEC, count);


    return 0;
}

//{-3, -3, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3}