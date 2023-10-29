#include<algorithm>
#include<stdio.h>
#include<vector>
#include<array>
#include<time.h>

void printvec(std::vector<int> vec) {
    for(unsigned int i = 0; i < vec.size(); i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

int main() {

    std::array<int, 30> vec = {-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

    printf("%d\n", vec.size());

    unsigned long long int count = 1;

    clock_t start = clock();

    while(std::next_permutation(vec.begin(), vec.end())) {
        count++;
    }

    printf("%lld, time: %f\n", count, float(clock() - start) / CLOCKS_PER_SEC);
}

//{-3, -3, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3}