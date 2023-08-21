#include<stdio.h>
#include"golay.h"

#define CHOICE 2

int main() {    

    switch(CHOICE) {
        case 1:
            find_psd();
            break;
        case 2:
            find_unique();
            break;
        default:
            //error
            break;
    }

}