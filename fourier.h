#include"fftw-3.3.5-dll64/fftw3.h"

fftw_complex * dft(int seq[], fftw_complex * in, fftw_complex * out, fftw_plan p, int len);
int dftfilter(fftw_complex * seqdft, int len);
int dftfilterpair(fftw_complex *dftA, fftw_complex *dftB, int len);
fftw_complex * dftVec(vector<int> seq, fftw_complex * in, fftw_complex * out, fftw_plan p);