#include<fstream>
#include<stdio.h>
#include"lib/fourier.h"
#include<set>
#include"lib/decomps.h"
#include"lib/golay.h"

int main() {

    auto solutions = sumoftwosquares(2 * 50);

    for(auto object : solutions) {
        printf("A: %d B:%d\n", object.first, object.second);
    }
}