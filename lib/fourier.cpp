#include"fftw3.h"
#include"decomps.h"
#include"golay.h"
#include<array>
#include<math.h>
#include<vector>
#include<set>

#define BOUND ORDER * 2


using namespace std;

std::set<std::vector<int>> sumofthreesquares(int sum) {
    std::set<std::vector<int>> solutions;

    for(int i = 0; i < sum; i++) {
        for(int j = i; j < sum; j++) {
            for(int k = j; k < sum; k++) {
                if(i * i + j * j + k * k == sum) {
                    std::vector<int> solution = {i, j, k};
                    solutions.insert(solution);
                }
            }
        }
    }

    return solutions;
} 


std::set<int> spectrumthree(int len, int ORDER) {
    std::set<int> spectrum;

    if(len % 3 != 0) {
        return spectrum;
    }

    for(int s = 0; s <= ORDER * 2; s++) {

        if(s % 3 != 0) {
            continue;
        }

        int a = (2 * (s) + decomps[ORDER][0][0] * decomps[ORDER][0][0]) / 3;
        int b = (2 * ((2 * ORDER) - s) + decomps[ORDER][0][1] * decomps[ORDER][0][1]) / 3;

        printf("%d %d\n", a, b);

        std::set<std::vector<int>> solutionsa = sumofthreesquares(a);

        std::set<std::vector<int>> solutionsb = sumofthreesquares(b);

        for(std::vector<int> solution : solutionsa) {

            for(int i = 0; i < 2; i++) {
                int sum = 0;
                if(i == 1) {
                    sum += -solution[0];
                } else {
                    sum += solution[0];
                }

                for(int j = 0; j < 2; j++) {
                    if(j == 1) {
                        sum += -solution[1];
                    } else {
                        sum += solution[1];
                    }
                    for(int k = 0; k < 2; k++) {
                        if(k == 1) {
                            sum += -solution[2];
                        } else {
                            sum += solution[2];
                        }
                        if(sum == decomps[ORDER][0][0]) {
                            spectrum.insert(a);
                        }
                    }
                }
            }
        }

        for(std::vector<int> solution : solutionsb) {

            for(int i = 0; i < 2; i++) {
                int sum = 0;
                if(i == 1) {
                    sum += -solution[0];
                } else {
                    sum += solution[0];
                }

                for(int j = 0; j < 2; j++) {
                    if(j == 1) {
                        sum += -solution[1];
                    } else {
                        sum += solution[1];
                    }
                    for(int k = 0; k < 2; k++) {
                        if(k == 1) {
                            sum += -solution[2];
                        } else {
                            sum += solution[2];
                        }
                        if(sum == decomps[ORDER][0][1]) {
                            spectrum.insert(b);
                        }
                    }
                }
            }
        }
    }

    return spectrum;
}

fftw_complex * dft(vector<int> seq, fftw_complex * in, fftw_complex * out, fftw_plan p) {
    for(size_t i = 0; i < seq.size(); i++) {
        in[i][0] = (double)seq[i];
        in[i][1] = 0;
    } 

    fftw_execute(p);
    
    return out;
} 

int floatEqual(float a, int b) {
    if(a == b) {
        return 1;
    }
    return 0;
}

int dftfilter(fftw_complex * seqdft, int len, int ORDER, int PAF_CONSTANT) {

    if(len % 2 == 0) {
        int j = len / 2;
        float complex = seqdft[j][0] * seqdft[j][0] + seqdft[j][1] * seqdft[j][1];
        if(!floatEqual(complex, decomps[ORDER][0][1] * decomps[ORDER][0][1]) && !floatEqual(complex, decomps[ORDER][0][0] * decomps[ORDER][0][0]) ) {
            return 0;
        }
    }
    
    for(int i = 1; i < len / 2; i++) {
        if((seqdft[i][0] * seqdft[i][0] + seqdft[i][1] * seqdft[i][1]) > 2 * ORDER - PAF_CONSTANT + 0.001) {
            return 0;
        }
    }
    return 1;
}

int dftfilterpair(fftw_complex *dftA, fftw_complex *dftB, int len) {
    for(int i = 0; i < len / 2; i++) {
        if(((dftA[i][0] * dftA[i][0] + dftA[i][1] * dftA[i][1]) + (dftB[i][0] * dftB[i][0] + dftB[i][1] * dftB[i][1])) > len * 2 + 0.001) {
            return 0;
        }
    }
    return 1;
}