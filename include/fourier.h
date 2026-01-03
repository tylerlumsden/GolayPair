#include"fftw3.h"
#include"golay.h"
#include<array>
#include<set>
using namespace std;

fftw_complex * dft(vector<int> seq, fftw_complex * in, fftw_complex * out, fftw_plan p);
int dftfilter(fftw_complex * seqdft, int len, int ORDER);
int dftfilterpair(fftw_complex *dftA, fftw_complex *dftB, int len);
std::set<int> spectrumthree(int len, int ORDER);
