#include<algorithm>
#include<stdio.h>
#include<vector>
#include<array>
#include<time.h>


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

int main() {



    std::vector<int> guy = {-1, -1, -1, 1, 1, 1};

    std::array<int, 6> seq = getPermutationK(7, guy);

    printarray(seq);
    /*

    std::vector<int> vec = {-1, -1, -1, 1, 1};

    printf("%d\n", vec.size());

    unsigned long long int count = 1;

    clock_t start = clock();

    while(std::next_permutation(vec.begin(), vec.end())) {
        /*
        if(count % 1000000000 == 0) {
            printf("count: %llu, %d\n", count, (clock() - start) / CLOCKS_PER_SEC);
        }
        

       printvec(vec);
        count++;
    }

    printf("%lld, time: %f\n", count, float(clock() - start) / CLOCKS_PER_SEC);
    */
}

//{-3, -3, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3}