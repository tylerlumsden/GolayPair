#include"fftw-3.3.5-dll64/fftw3.h"
#include"golay.h"
#include<array>


using namespace std;


fftw_complex * dft(array<int, ORDER> seq, fftw_complex * in, fftw_complex * out, fftw_plan p) {
    for(int i = 0; i < ORDER; i++) {
        in[i][0] = (double)seq[i];
        in[i][1] = 0;
    } 

    fftw_execute(p);

    return out;
} 

int dftfilter(fftw_complex * seqdft, int len) {
    for(int i = 0; i < len / 2; i++) {
        if((seqdft[i][0] * seqdft[i][0] + seqdft[i][1] * seqdft[i][1]) > len * 2 + 0.001) {
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
