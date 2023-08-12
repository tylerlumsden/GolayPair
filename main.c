#include<stdio.h>
#include"golay.h"

#define CHOICE 1

int main() {    

    switch(CHOICE) {
        case 1:
            find_psd();
            break;
        case 2:
            //run find function
            break;
        default:
            //error
            break;
    }

}