#include<algorithm>
#include<stdio.h>
#include<vector>
#include<array>
#include<time.h>
#include<set>
#include"lib/orderly_equivalence.h"

void printarray(std::array<int, 6> seq) {
    for(int i = 0; i < seq.size(); i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
}

void printvec(std::vector<int> vec) {
    for(unsigned int i = 0; i < vec.size(); i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

	/**
* @brief Calculates the binomial coefficient C(n, k) using dynamic programming.
*
* @param n The total number of items.
* @param k The number of items to be chosen.
* @return long long The value of C(n, k).
*/
long long calculateBinomialCoefficient(int n, int k) {
    // Create a 2D array to store the intermediate results.
    long long dp[n + 1][k + 1];
 
    // Fill the base cases.
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= std::min(i, k); j++) {
            if (j == 0 || j == i) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }
 
    // Return the calculated binomial coefficient.
    return dp[n][k];
}

std::array<int, 6> getPermutationK(int k, std::vector<int> seq) {

    std::array<int, 6> finalseq;
    finalseq[0] = -1;

    seq.erase(seq.begin());

    for(int i = 1; i < 6; i++) {
        int count = 0;

        for(int i = 1; i < seq.size() - 1; i++) {
            if(seq[i] == -1) {
                count++;
            }
        }

        printf("%d\n", count);

        long long binomial = calculateBinomialCoefficient(seq.size() - 1, count);

        printf("%lld\n", binomial);

        if(k > binomial) {
            finalseq[i] = *(seq.end() - 1);
            k = k - binomial;

            seq.erase(seq.end() - 1);
        } else {
            finalseq[i] = *seq.begin();

            seq.erase(seq.begin());
        }
    }
    return finalseq;
}   

std::vector<std::vector<int>> getCombinations(int len, std::set<int> alphabet) {
    std::vector<std::vector<int>> combinations;
    std::set<int> subalphabet = alphabet;
    
    int smallest;

    if(len == 1) {
        for(int letter : alphabet) {
            std::vector<int> part;
            part.push_back(letter);
            combinations.push_back(part);
        }
        return combinations;
    }

    for(int letter : alphabet) {
        std::vector<std::vector<int>> part;
        smallest = *std::min_element(subalphabet.begin(), subalphabet.end());

        std::vector<std::vector<int>> result = getCombinations(len - 1, subalphabet);
        part.insert(part.end(), result.begin(), result.end());

        for(std::vector<int>& combo : part) {
            combo.insert(combo.begin(), letter);
        }

        combinations.insert(combinations.end(), part.begin(), part.end());

        subalphabet.erase(letter);
    }

    return combinations;
} 

int main() {

    std::array<int, 12> seq = {-5, 3, -1, 3, 5, 1, 3, 3, -3, -1, 1, 3};

    printf("%d\n", isOrderly(seq, 0));


}

//{-3, -3, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3}