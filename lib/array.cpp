#include<stdio.h>
#include<array>
#include<algorithm>
#include<set>
#include<vector>
#include"golay.h"

using namespace std;

int NextCombinationRowSums(array<int, LEN>& arr, int length, int* currentSum) {
        if((*currentSum) > length || (*currentSum) < -length) {
            printf("Error. currentSum out of bounds: %d\n", *currentSum);
            return 0;
        }
        //if the value is -1, need to re-traverse the tree
        if(arr[length - 1] == 1) {
            //find next root node that is value of 1
            int i = length - 1;
            while(arr[i] == 1) {
                if(i == 0) {
                    return 0;
                }
                i--;
                (*currentSum)--;
            }
            arr[i] = 1;
            (*currentSum) += 2;
            
            //every node after this root should be value of 1 (considering that we are finding the next combination)
            i++;
            while(i < length) {
                arr[i] = -1;
                i++;
                (*currentSum)--;
            }

            return 1;
        }
        //if the value is 1, then the next combination has the value as -1.
        if(arr[length - 1] == -1) {
            arr[length - 1] = 1;
            (*currentSum) += 2;
            return 1;
        }


    return 1;
}

int seqIsLargest(array<int, 8> seq, int start, int rowsum) {
    for(int i = start; i < start + rowsum; i++) {
        if(seq[i] == -1) {
            return 0;
        }
    }
    return 1;
}

//---+++++

void resetSeq(array<int, 8>& seq, int start, unsigned int rowsum) {
    for(unsigned int i = start; i < seq.size(); i++) {
        if((seq.size() - i) < rowsum) {
            seq[i] = 1;
        } else {
            seq[i] = -1;
        }
    }
}

int nextRowSums(array<int, 8>& seq, int start, int rowsum) {

    if(seqIsLargest(seq, start, rowsum)) {
        //printf("Largest\n");
        return 0;
    }

    //find first plus
    int first;
    for(unsigned int i = start; i < seq.size(); i++) {
        if(seq[i] == 1) {
            first = i;
            break;
        }
    }

    //printf("first: %d\n", first);

    //find next seq of subarray after this plus
    //probably wont work due to indexxing issues
    if(!nextRowSums(seq, first + 1, rowsum - 1)) {
        seq[first] = -1;
        seq[first - 1] = 1;
        //reset rest of sequence
        resetSeq(seq, first + 1, rowsum);
        return 1;
    } else {
        return 1;
    }
}

//assumes that there are 7 +/- 3's and 23 +/- 1's in the sequence, the smallest is the sequence with only negative values.
int nextCombinationA(std::array<int, LEN>& seq) {
    int countThree = 0;
    int countOne = 0;
    for(int i = 0; i < LEN; i++) {
        if(seq[i] == 3) {
            countThree++;
        }
        if(seq[i] == 1) {
            countOne++;
        }
    }
    
    if(countOne == 23 && countThree == 7) {
        return 0;
    } 
    
    else if(countOne == 23) {
        for(int i = 0; i < LEN; i++) {
            if(seq[i] == 1) {
                seq[i] = -1;
            }
        }

        for(int i = 0; i < LEN; i++) {
            if(seq[i] == -3) {
                seq[i] = 3;
                break;
            }
        }
    } 
    

    else {
        for(int i = 0; i < LEN; i++) {
            if(seq[i] == -1) {
                seq[i] = 1;
                break;
            }
        }
    }

    std::sort(seq.begin(), seq.end());

    return 1;
}

int nextCombinationB(std::array<int, LEN>& seq) {
    int countThree = 0;
    int countOne = 0;
    for(int i = 0; i < LEN; i++) {
        if(seq[i] == 3) {
            countThree++;
        }
        if(seq[i] == 1) {
            countOne++;
        }
    }
    
    if(countOne == 22 && countThree == 8) {
        return 0;
    } 
    
    else if(countOne == 22) {
        for(int i = 0; i < LEN; i++) {
            if(seq[i] == 1) {
                seq[i] = -1;
            }
        }

        for(int i = 0; i < LEN; i++) {
            if(seq[i] == -3) {
                seq[i] = 3;
                break;
            }
        }
    } 
    

    else {
        for(int i = 0; i < LEN; i++) {
            if(seq[i] == -1) {
                seq[i] = 1;
                break;
            }
        }
    }

    std::sort(seq.begin(), seq.end());

    return 1;
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

//Assumes that k is within the bounds of the permutation count
//Assumes that seq is a sorted sequence consisting of {-1, 1}
array<int, LEN> getPermutationK(int k, vector<int> seq) {

    array<int, LEN> finalseq;
    finalseq[0] = -1;

    seq.erase(seq.begin());

    for(int i = 1; i < LEN; i++) {
        int count = 0;

        for(unsigned int i = 1; i < seq.size() - 1; i++) {
            if(seq[i] == -1) {
                count++;
            }
        }

        long long binomial = calculateBinomialCoefficient(seq.size() - 1, count);

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