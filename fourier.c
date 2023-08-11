#include<stdio.h>
#include"golay.h"
#include"fftw-3.3.5-dll64/fftw3.h"

int main() {

}

fftw_complex * dft(int seq[], int len) {
    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * len);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * len);

    for(int i = 0; i < len; i++) {
        in[i][0] = (double)seq[i];
    }

    p = fftw_plan_dft_1d(len, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p);

    fftw_destroy_plan(p);
    fftw_free(in);

    return out;
} 

int dftfilter(int seq[], int len) {
    fftw_complex * seqdft = dft(seq, len);
    for(int i = 0; i < len; i++) {
        if(seqdft[i][0] > len * 2) {
            fftw_free(seqdft);
            return 0;
        }
    }
    fftw_free(seqdft);
    return 1;

}

