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

    std::array<int, 50> vec = {-1, -1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    printf("%d\n", vec.size());

    unsigned long long int count = 1;

    clock_t start = clock();

    while(std::next_permutation(vec.begin(), vec.end())) {
        if(count % 1000000000 == 0) {
            printf("count: %llu, %d\n", count, (clock() - start) / CLOCKS_PER_SEC);
        }
        count++;
    }

    printf("%lld, time: %f\n", count, float(clock() - start) / CLOCKS_PER_SEC);
}

//{-3, -3, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3}