        current = clock();
            if(progress % PrintProg == 0) {
                printf("Progress: %d ... %d, time elapsed: %d seconds, Pairs found: %d\n", progress, combinations - 1, (current - start) / CLOCKS_PER_SEC, pairs);
                fflush(stdin);
            }