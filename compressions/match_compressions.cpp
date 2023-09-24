#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>

int main() {

    FILE * out = fopen("compressions.pairs", "w");

    std::ifstream filea("compressions.a");
    std::ifstream fileb("compressions.b");

    std::string a;
    std::string b;

    int count = 0;
    

    if(filea.is_open() && fileb.is_open()) {

        while(filea.good()) {

            filea >> a;

            count++;

            while(fileb.good()) {


                fileb >> b;

                if(a == b) {
                    std::cout << a + "\n" + b + "\n";

                    for(int i = 0; i < 30; i++) {
                        filea >> a;
                        fprintf(out, "%d ", stoi(a));
                    }

                    fprintf(out, "\n");

                    for(int i = 0; i < 30; i++) {
                        fileb >> b;
                        fprintf(out, "%d ", stoi(b));
                    }
                }
                getline(fileb, b);
            }

            getline(filea, a);

            fileb.clear();
            fileb.seekg(0);
        }
    }
}