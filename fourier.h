#include"fftw-3.3.10/api/fftw3.h"
#include"golay.h"
#include<array>

using namespace std;

fftw_complex * dft(array<int, ORDER> seq, fftw_complex * in, fftw_complex * out, fftw_plan p);
int dftfilter(fftw_complex * seqdft, int len);
int dftfilterpair(fftw_complex *dftA, fftw_complex *dftB, int len);
