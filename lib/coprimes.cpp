#include "coprimes.h"
#include <vector>
#include <iostream>
#include <numeric>

namespace {
    std::vector<std::vector<int>> coprimelists;
}

// Define the vector list
// Static initializer runs before main()
static int initCoprimes = []() {
    coprimelists.resize(MAX_COPRIME_N + 1);
    for (int k = 0; k <= MAX_COPRIME_N; ++k) {
        for (int i = 1; i < k; ++i) {
            if (std::gcd(i, k) == 1) {
                coprimelists[k].push_back(i);
            }
        }
    }
    return 0;
}();

const std::vector<int>& getcoprimes(int k) {
    if(k > MAX_COPRIME_N) {
        std::cerr << "ERROR: Tried to access coprimes to the integer " << k;
        std::cerr << "but coprime list only computed up to " + coprimelists.size() << "\n";
        std::cerr << "Raise MAX_COPRIME_N in header coprimes.h\n";

        std::abort();
    }
    return coprimelists[k];
}



