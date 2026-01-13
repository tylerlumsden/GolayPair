#include <vector>
#include <iostream>
#include <numeric>
#include "decomps.h"

const std::vector<std::pair<int, int>> getdecomps(int k) {
    std::vector<std::pair<int, int>> solutions;

    for(int x = 0; x <= k; x++) {
        for(int y = x; y <= k; y++) {
            if(x * x + y * y == k) {
                solutions.push_back(std::make_pair(x, y));
            }
        }
    }
    return solutions;
}



