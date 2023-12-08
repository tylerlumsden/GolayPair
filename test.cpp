#include<algorithm>
#include<stdio.h>
#include<vector>
#include<array>
#include<time.h>
#include<set>
#include"lib/orderly_equivalence.h"
#include"lib/equivalence.h"
#include"lib/golay.h"

int main() {

    std::set<GolayPair> generators = constructGenerators();

    GolayPair seq;

    for(int i = 0; i < 15; i++) {
        seq.a[i] = -1;
        seq.b[i] = -1;
    }

    for(int i = 15; i < 30; i++) {
        seq.a[i] = 1;
        seq.b[i] = 1;
    }

    printf("Generating test equivalence class.\n");

    std::set<GolayPair> equiv;

    for(GolayPair item : generators) {
        GolayPair newseq;

        for(int i = 0; i < LEN; i++) {
            printf("%d ", item.a[i]);
        }
        printf("\n");
        for(int i = 0; i < LEN; i++) {
            printf("%d ", item.b[i]);
        }
        printf("\n");

        for(int i = 0; i < LEN; i++) {
            if(item.a[i] < 0) {
                newseq.a[i] = -seq.a[-item.a[i]];
            } else {
                newseq.a[i] = seq.a[item.a[i]];
            }

            if(item.b[i] < 0) {
                newseq.b[i] = -seq.b[-item.b[i]];
            } else {
                newseq.b[i] = seq.b[item.b[i]];
            }
        }

        equiv.insert(newseq);
    }

    printf("Done, size: %d\n", equiv.size());
}

//{-3, -3, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3}