#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

int main (void)
{

int i, v = 72;

int Om6s[] = {0};

int Ozs[] = {0,1,2,3,4,6,7,8,9,10,12};

int Op6s[] = {0,5,11};

int xm6[1], xp6[3], xz[11], A[73];

float  PSD1, PSD2, PSD3, PSD4, PSD5, PSD6, PSD7, PSD8, PSD9, PSD10, PSD11, PSD12, PSD13, PSD14, PSD15, PSD16, PSD17, PSD18, PSD19, PSD20, PSD21, PSD22, PSD23, PSD24, PSD25, PSD26, PSD27, PSD28, PSD29, PSD30, PSD31, PSD32, PSD33, PSD34, PSD35, PSD36; 

complex omegaPowers[72], omega, dft;

omega = .9961946981+.8715574277e-1*I;

omegaPowers[0] = 1.0 + 0.0*I;

omegaPowers[1] = omega;

for(i=2; i < v; i++) { omegaPowers[i] = omegaPowers[i-1]*omega; }

A[5] = 1; A[17] = 1; A[29] = 1; A[41] = 1; A[53] = 1; A[65] = 1;
A[11] = 1; A[23] = 1; A[35] = 1; A[47] = 1; A[59] = 1; A[71] = 1;

for (xz[1] = 1; xz[1] <= 20; xz[1]++)
for (xz[2] = 1; xz[2] <= 20; xz[2]++)
for (xz[3] = 1; xz[3] <= 20; xz[3]++)
for (xz[4] = 1; xz[4] <= 20; xz[4]++)
for (xz[5] = 1; xz[5] <= 20; xz[5]++)
for (xz[6] = 1; xz[6] <= 20; xz[6]++)
for (xz[7] = 1; xz[7] <= 20; xz[7]++)
for (xz[8] = 1; xz[8] <= 20; xz[8]++)
for (xz[9] = 1; xz[9] <= 20; xz[9]++)
for (xz[10] = 1; xz[10] <= 20; xz[10]++)
        {



for(i=1; i<=10; i++)
   switch (xz[i]) {
case 1  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = 1 ; break;
case 2  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = 1 ; break;
case 3  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = 1 ; break;
case 4  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = -1 ; break;
case 5  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = 1 ; break;
case 6  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = 1 ; break;
case 7  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = -1 ; break;
case 8  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = 1 ; break;
case 9  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = -1 ; break;
case 10  : A[Ozs[i]] = -1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = -1 ; break;
case 11  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = 1 ; break;
case 12  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = 1 ; break;
case 13  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = -1 ; break;
case 14  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = 1 ; break;
case 15  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = -1 ; break;
case 16  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = -1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = -1 ; break;
case 17  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = 1 ; break;
case 18  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = 1 ; A[Ozs[i]+60] = -1 ; break;
case 19  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = -1 ; A[Ozs[i]+36] = 1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = -1 ; break;
case 20  : A[Ozs[i]] = 1 ; A[Ozs[i]+12] = 1 ; A[Ozs[i]+24] = 1 ; A[Ozs[i]+36] = -1 ; A[Ozs[i]+48] = -1 ; A[Ozs[i]+60] = -1 ; break;
  }


dft = (A[1]+A[4]+A[7]+A[10]+A[13]+A[16]+A[19]+A[22]+A[25]+A[28]+A[31]+A[34]+A[37]+A[40]+A[43]+A[46]+A[49]+A[52]+A[55]+A[58]+A[61]+A[64]+A[67]+A[70])*omegaPowers[0]+(A[2]+A[5]+A[8]+A[11]+A[14]+A[17]+A[20]+A[23]+A[26]+A[29]+A[32]+A[35]+A[38]+A[41]+A[44]+A[47]+A[50]+A[53]+A[56]+A[59]+A[62]+A[65]+A[68]+A[71])*omegaPowers[24]+(A[3]+A[6]+A[9]+A[12]+A[15]+A[18]+A[21]+A[24]+A[27]+A[30]+A[33]+A[36]+A[39]+A[42]+A[45]+A[48]+A[51]+A[54]+A[57]+A[60]+A[63]+A[66]+A[69]+A[72])*omegaPowers[48];

PSD24 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if ((int)rint(PSD24) != 144) continue;

dft = A[1]*omegaPowers[0]+A[2]*omegaPowers[1]+A[3]*omegaPowers[2]+A[4]*omegaPowers[3]+A[5]*omegaPowers[4]+A[6]*omegaPowers[5]+A[7]*omegaPowers[6]+A[8]*omegaPowers[7]+A[9]*omegaPowers[8]+A[10]*omegaPowers[9]+A[11]*omegaPowers[10]+A[12]*omegaPowers[11]+A[13]*omegaPowers[12]+A[14]*omegaPowers[13]+A[15]*omegaPowers[14]+A[16]*omegaPowers[15]+A[17]*omegaPowers[16]+A[18]*omegaPowers[17]+A[19]*omegaPowers[18]+A[20]*omegaPowers[19]+A[21]*omegaPowers[20]+A[22]*omegaPowers[21]+A[23]*omegaPowers[22]+A[24]*omegaPowers[23]+A[25]*omegaPowers[24]+A[26]*omegaPowers[25]+A[27]*omegaPowers[26]+A[28]*omegaPowers[27]+A[29]*omegaPowers[28]+A[30]*omegaPowers[29]+A[31]*omegaPowers[30]+A[32]*omegaPowers[31]+A[33]*omegaPowers[32]+A[34]*omegaPowers[33]+A[35]*omegaPowers[34]+A[36]*omegaPowers[35]+A[37]*omegaPowers[36]+A[38]*omegaPowers[37]+A[39]*omegaPowers[38]+A[40]*omegaPowers[39]+A[41]*omegaPowers[40]+A[42]*omegaPowers[41]+A[43]*omegaPowers[42]+A[44]*omegaPowers[43]+A[45]*omegaPowers[44]+A[46]*omegaPowers[45]+A[47]*omegaPowers[46]+A[48]*omegaPowers[47]+A[49]*omegaPowers[48]+A[50]*omegaPowers[49]+A[51]*omegaPowers[50]+A[52]*omegaPowers[51]+A[53]*omegaPowers[52]+A[54]*omegaPowers[53]+A[55]*omegaPowers[54]+A[56]*omegaPowers[55]+A[57]*omegaPowers[56]+A[58]*omegaPowers[57]+A[59]*omegaPowers[58]+A[60]*omegaPowers[59]+A[61]*omegaPowers[60]+A[62]*omegaPowers[61]+A[63]*omegaPowers[62]+A[64]*omegaPowers[63]+A[65]*omegaPowers[64]+A[66]*omegaPowers[65]+A[67]*omegaPowers[66]+A[68]*omegaPowers[67]+A[69]*omegaPowers[68]+A[70]*omegaPowers[69]+A[71]*omegaPowers[70]+A[72]*omegaPowers[71];

PSD1 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD1 > 144) continue;


dft = (A[1]+A[37])*omegaPowers[0]+(A[2]+A[38])*omegaPowers[2]+(A[3]+A[39])*omegaPowers[4]+(A[4]+A[40])*omegaPowers[6]+(A[5]+A[41])*omegaPowers[8]+(A[6]+A[42])*omegaPowers[10]+(A[7]+A[43])*omegaPowers[12]+(A[8]+A[44])*omegaPowers[14]+(A[9]+A[45])*omegaPowers[16]+(A[10]+A[46])*omegaPowers[18]+(A[11]+A[47])*omegaPowers[20]+(A[12]+A[48])*omegaPowers[22]+(A[13]+A[49])*omegaPowers[24]+(A[14]+A[50])*omegaPowers[26]+(A[15]+A[51])*omegaPowers[28]+(A[16]+A[52])*omegaPowers[30]+(A[17]+A[53])*omegaPowers[32]+(A[18]+A[54])*omegaPowers[34]+(A[19]+A[55])*omegaPowers[36]+(A[20]+A[56])*omegaPowers[38]+(A[21]+A[57])*omegaPowers[40]+(A[22]+A[58])*omegaPowers[42]+(A[23]+A[59])*omegaPowers[44]+(A[24]+A[60])*omegaPowers[46]+(A[25]+A[61])*omegaPowers[48]+(A[26]+A[62])*omegaPowers[50]+(A[27]+A[63])*omegaPowers[52]+(A[28]+A[64])*omegaPowers[54]+(A[29]+A[65])*omegaPowers[56]+(A[30]+A[66])*omegaPowers[58]+(A[31]+A[67])*omegaPowers[60]+(A[32]+A[68])*omegaPowers[62]+(A[33]+A[69])*omegaPowers[64]+(A[34]+A[70])*omegaPowers[66]+(A[35]+A[71])*omegaPowers[68]+(A[36]+A[72])*omegaPowers[70];

PSD2 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD2 > 144) continue;


dft = (A[1]+A[25]+A[49])*omegaPowers[0]+(A[2]+A[26]+A[50])*omegaPowers[3]+(A[3]+A[27]+A[51])*omegaPowers[6]+(A[4]+A[28]+A[52])*omegaPowers[9]+(A[5]+A[29]+A[53])*omegaPowers[12]+(A[6]+A[30]+A[54])*omegaPowers[15]+(A[7]+A[31]+A[55])*omegaPowers[18]+(A[8]+A[32]+A[56])*omegaPowers[21]+(A[9]+A[33]+A[57])*omegaPowers[24]+(A[10]+A[34]+A[58])*omegaPowers[27]+(A[11]+A[35]+A[59])*omegaPowers[30]+(A[12]+A[36]+A[60])*omegaPowers[33]+(A[13]+A[61]+A[37])*omegaPowers[36]+(A[14]+A[38]+A[62])*omegaPowers[39]+(A[15]+A[39]+A[63])*omegaPowers[42]+(A[16]+A[40]+A[64])*omegaPowers[45]+(A[17]+A[41]+A[65])*omegaPowers[48]+(A[18]+A[42]+A[66])*omegaPowers[51]+(A[19]+A[43]+A[67])*omegaPowers[54]+(A[20]+A[44]+A[68])*omegaPowers[57]+(A[21]+A[45]+A[69])*omegaPowers[60]+(A[22]+A[46]+A[70])*omegaPowers[63]+(A[23]+A[47]+A[71])*omegaPowers[66]+(A[24]+A[48]+A[72])*omegaPowers[69];

PSD3 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD3 > 144) continue;


dft = (A[1]+A[19]+A[37]+A[55])*omegaPowers[0]+(A[2]+A[20]+A[38]+A[56])*omegaPowers[4]+(A[3]+A[21]+A[39]+A[57])*omegaPowers[8]+(A[4]+A[22]+A[40]+A[58])*omegaPowers[12]+(A[5]+A[23]+A[41]+A[59])*omegaPowers[16]+(A[6]+A[24]+A[42]+A[60])*omegaPowers[20]+(A[7]+A[43]+A[61]+A[25])*omegaPowers[24]+(A[8]+A[26]+A[44]+A[62])*omegaPowers[28]+(A[9]+A[27]+A[45]+A[63])*omegaPowers[32]+(A[10]+A[28]+A[46]+A[64])*omegaPowers[36]+(A[11]+A[29]+A[47]+A[65])*omegaPowers[40]+(A[12]+A[30]+A[48]+A[66])*omegaPowers[44]+(A[13]+A[31]+A[49]+A[67])*omegaPowers[48]+(A[14]+A[32]+A[50]+A[68])*omegaPowers[52]+(A[15]+A[33]+A[51]+A[69])*omegaPowers[56]+(A[16]+A[34]+A[52]+A[70])*omegaPowers[60]+(A[17]+A[35]+A[53]+A[71])*omegaPowers[64]+(A[18]+A[36]+A[54]+A[72])*omegaPowers[68];

PSD4 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD4 > 144) continue;


dft = A[56]*omegaPowers[59]+A[57]*omegaPowers[64]+A[58]*omegaPowers[69]+A[59]*omegaPowers[2]+A[60]*omegaPowers[7]+A[61]*omegaPowers[12]+A[62]*omegaPowers[17]+A[63]*omegaPowers[22]+A[64]*omegaPowers[27]+A[65]*omegaPowers[32]+A[66]*omegaPowers[37]+A[67]*omegaPowers[42]+A[68]*omegaPowers[47]+A[69]*omegaPowers[52]+A[70]*omegaPowers[57]+A[71]*omegaPowers[62]+A[72]*omegaPowers[67]+A[2]*omegaPowers[5]+A[3]*omegaPowers[10]+A[4]*omegaPowers[15]+A[5]*omegaPowers[20]+A[6]*omegaPowers[25]+A[7]*omegaPowers[30]+A[8]*omegaPowers[35]+A[9]*omegaPowers[40]+A[10]*omegaPowers[45]+A[11]*omegaPowers[50]+A[12]*omegaPowers[55]+A[13]*omegaPowers[60]+A[14]*omegaPowers[65]+A[15]*omegaPowers[70]+A[16]*omegaPowers[3]+A[17]*omegaPowers[8]+A[18]*omegaPowers[13]+A[20]*omegaPowers[23]+A[21]*omegaPowers[28]+A[22]*omegaPowers[33]+A[23]*omegaPowers[38]+A[24]*omegaPowers[43]+A[26]*omegaPowers[53]+A[27]*omegaPowers[58]+A[28]*omegaPowers[63]+A[29]*omegaPowers[68]+A[30]*omegaPowers[1]+A[31]*omegaPowers[6]+A[32]*omegaPowers[11]+A[33]*omegaPowers[16]+A[34]*omegaPowers[21]+A[35]*omegaPowers[26]+A[36]*omegaPowers[31]+A[38]*omegaPowers[41]+A[39]*omegaPowers[46]+A[40]*omegaPowers[51]+A[41]*omegaPowers[56]+A[42]*omegaPowers[61]+A[43]*omegaPowers[66]+A[44]*omegaPowers[71]+A[45]*omegaPowers[4]+A[46]*omegaPowers[9]+A[47]*omegaPowers[14]+A[48]*omegaPowers[19]+A[50]*omegaPowers[29]+A[51]*omegaPowers[34]+A[52]*omegaPowers[39]+A[53]*omegaPowers[44]+A[54]*omegaPowers[49]+A[1]*omegaPowers[0]+A[19]*omegaPowers[18]+A[37]*omegaPowers[36]+A[55]*omegaPowers[54]+A[25]*omegaPowers[48]+A[49]*omegaPowers[24];

PSD5 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD5 > 144) continue;


dft = A[27]*omegaPowers[38]+A[28]*omegaPowers[45]+A[29]*omegaPowers[52]+A[30]*omegaPowers[59]+A[31]*omegaPowers[66]+A[32]*omegaPowers[1]+A[33]*omegaPowers[8]+A[34]*omegaPowers[15]+A[35]*omegaPowers[22]+A[36]*omegaPowers[29]+A[38]*omegaPowers[43]+A[39]*omegaPowers[50]+A[40]*omegaPowers[57]+A[41]*omegaPowers[64]+A[42]*omegaPowers[71]+A[43]*omegaPowers[6]+A[44]*omegaPowers[13]+A[45]*omegaPowers[20]+A[46]*omegaPowers[27]+A[47]*omegaPowers[34]+A[48]*omegaPowers[41]+A[50]*omegaPowers[55]+A[51]*omegaPowers[62]+A[52]*omegaPowers[69]+A[53]*omegaPowers[4]+A[54]*omegaPowers[11]+A[56]*omegaPowers[25]+A[57]*omegaPowers[32]+A[58]*omegaPowers[39]+A[59]*omegaPowers[46]+A[60]*omegaPowers[53]+A[62]*omegaPowers[67]+A[63]*omegaPowers[2]+A[64]*omegaPowers[9]+A[65]*omegaPowers[16]+A[66]*omegaPowers[23]+A[67]*omegaPowers[30]+A[68]*omegaPowers[37]+A[69]*omegaPowers[44]+A[70]*omegaPowers[51]+A[71]*omegaPowers[58]+A[72]*omegaPowers[65]+A[2]*omegaPowers[7]+A[3]*omegaPowers[14]+A[4]*omegaPowers[21]+A[5]*omegaPowers[28]+A[6]*omegaPowers[35]+A[7]*omegaPowers[42]+A[8]*omegaPowers[49]+A[9]*omegaPowers[56]+A[10]*omegaPowers[63]+A[11]*omegaPowers[70]+A[12]*omegaPowers[5]+A[14]*omegaPowers[19]+A[15]*omegaPowers[26]+A[16]*omegaPowers[33]+A[17]*omegaPowers[40]+A[18]*omegaPowers[47]+A[20]*omegaPowers[61]+A[21]*omegaPowers[68]+A[22]*omegaPowers[3]+A[23]*omegaPowers[10]+A[24]*omegaPowers[17]+A[26]*omegaPowers[31]+A[19]*omegaPowers[54]+A[55]*omegaPowers[18]+A[1]*omegaPowers[0]+A[13]*omegaPowers[12]+A[25]*omegaPowers[24]+A[37]*omegaPowers[36]+A[49]*omegaPowers[48]+A[61]*omegaPowers[60];

PSD7 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD7 > 144) continue;


dft = (A[10]+A[19]+A[28]+A[37]+A[46]+A[55]+A[64]+A[1])*omegaPowers[0]+(A[2]+A[11]+A[20]+A[29]+A[38]+A[47]+A[56]+A[65])*omegaPowers[8]+(A[3]+A[12]+A[21]+A[30]+A[39]+A[48]+A[57]+A[66])*omegaPowers[16]+(A[4]+A[13]+A[22]+A[31]+A[40]+A[58]+A[67]+A[49])*omegaPowers[24]+(A[5]+A[14]+A[23]+A[32]+A[41]+A[50]+A[59]+A[68])*omegaPowers[32]+(A[6]+A[15]+A[24]+A[33]+A[42]+A[51]+A[60]+A[69])*omegaPowers[40]+(A[7]+A[16]+A[25]+A[34]+A[43]+A[52]+A[61]+A[70])*omegaPowers[48]+(A[8]+A[17]+A[26]+A[35]+A[44]+A[53]+A[62]+A[71])*omegaPowers[56]+(A[9]+A[18]+A[27]+A[36]+A[45]+A[54]+A[63]+A[72])*omegaPowers[64];

PSD8 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD8 > 144) continue;


dft = (A[41]+A[49]+A[57]+A[65]+A[9]+A[17]+A[25]+A[33]+A[1])*omegaPowers[0]+(A[42]+A[50]+A[58]+A[66]+A[2]+A[18]+A[26]+A[34]+A[10])*omegaPowers[9]+(A[35]+A[43]+A[51]+A[59]+A[67]+A[3]+A[11]+A[27]+A[19])*omegaPowers[18]+(A[36]+A[44]+A[52]+A[60]+A[68]+A[4]+A[12]+A[20]+A[28])*omegaPowers[27]+(A[45]+A[53]+A[61]+A[69]+A[5]+A[13]+A[21]+A[29]+A[37])*omegaPowers[36]+(A[6]+A[14]+A[22]+A[30]+A[38]+A[46]+A[54]+A[62]+A[70])*omegaPowers[45]+(A[7]+A[15]+A[23]+A[31]+A[39]+A[47]+A[55]+A[63]+A[71])*omegaPowers[54]+(A[8]+A[16]+A[24]+A[32]+A[40]+A[48]+A[56]+A[64]+A[72])*omegaPowers[63];

PSD9 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD9 > 144) continue;


dft = (A[29]+A[65])*omegaPowers[64]+(A[22]+A[58])*omegaPowers[66]+(A[15]+A[51])*omegaPowers[68]+(A[8]+A[44])*omegaPowers[70]+(A[20]+A[56])*omegaPowers[46]+(A[13]+A[49])*omegaPowers[48]+(A[6]+A[42])*omegaPowers[50]+(A[35]+A[71])*omegaPowers[52]+(A[28]+A[64])*omegaPowers[54]+(A[21]+A[57])*omegaPowers[56]+(A[14]+A[50])*omegaPowers[58]+(A[7]+A[43])*omegaPowers[60]+(A[36]+A[72])*omegaPowers[62]+(A[37]+A[1])*omegaPowers[0]+(A[30]+A[66])*omegaPowers[2]+(A[23]+A[59])*omegaPowers[4]+(A[16]+A[52])*omegaPowers[6]+(A[45]+A[9])*omegaPowers[8]+(A[2]+A[38])*omegaPowers[10]+(A[31]+A[67])*omegaPowers[12]+(A[24]+A[60])*omegaPowers[14]+(A[53]+A[17])*omegaPowers[16]+(A[10]+A[46])*omegaPowers[18]+(A[3]+A[39])*omegaPowers[20]+(A[32]+A[68])*omegaPowers[22]+(A[61]+A[25])*omegaPowers[24]+(A[18]+A[54])*omegaPowers[26]+(A[11]+A[47])*omegaPowers[28]+(A[4]+A[40])*omegaPowers[30]+(A[69]+A[33])*omegaPowers[32]+(A[26]+A[62])*omegaPowers[34]+(A[19]+A[55])*omegaPowers[36]+(A[12]+A[48])*omegaPowers[38]+(A[5]+A[41])*omegaPowers[40]+(A[34]+A[70])*omegaPowers[42]+(A[27]+A[63])*omegaPowers[44];

PSD10 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD10 > 144) continue;


dft = A[61]*omegaPowers[12]+A[13]*omegaPowers[60]+A[42]*omegaPowers[19]+A[43]*omegaPowers[30]+A[44]*omegaPowers[41]+A[45]*omegaPowers[52]+A[46]*omegaPowers[63]+A[47]*omegaPowers[2]+A[48]*omegaPowers[13]+A[50]*omegaPowers[35]+A[51]*omegaPowers[46]+A[52]*omegaPowers[57]+A[53]*omegaPowers[68]+A[54]*omegaPowers[7]+A[56]*omegaPowers[29]+A[57]*omegaPowers[40]+A[58]*omegaPowers[51]+A[59]*omegaPowers[62]+A[60]*omegaPowers[1]+A[62]*omegaPowers[23]+A[63]*omegaPowers[34]+A[64]*omegaPowers[45]+A[65]*omegaPowers[56]+A[66]*omegaPowers[67]+A[67]*omegaPowers[6]+A[68]*omegaPowers[17]+A[69]*omegaPowers[28]+A[70]*omegaPowers[39]+A[71]*omegaPowers[50]+A[72]*omegaPowers[61]+A[2]*omegaPowers[11]+A[3]*omegaPowers[22]+A[4]*omegaPowers[33]+A[5]*omegaPowers[44]+A[6]*omegaPowers[55]+A[7]*omegaPowers[66]+A[8]*omegaPowers[5]+A[9]*omegaPowers[16]+A[10]*omegaPowers[27]+A[11]*omegaPowers[38]+A[12]*omegaPowers[49]+A[14]*omegaPowers[71]+A[15]*omegaPowers[10]+A[16]*omegaPowers[21]+A[17]*omegaPowers[32]+A[18]*omegaPowers[43]+A[20]*omegaPowers[65]+A[21]*omegaPowers[4]+A[22]*omegaPowers[15]+A[23]*omegaPowers[26]+A[24]*omegaPowers[37]+A[26]*omegaPowers[59]+A[27]*omegaPowers[70]+A[28]*omegaPowers[9]+A[29]*omegaPowers[20]+A[30]*omegaPowers[31]+A[31]*omegaPowers[42]+A[32]*omegaPowers[53]+A[33]*omegaPowers[64]+A[34]*omegaPowers[3]+A[35]*omegaPowers[14]+A[36]*omegaPowers[25]+A[38]*omegaPowers[47]+A[39]*omegaPowers[58]+A[40]*omegaPowers[69]+A[41]*omegaPowers[8]+A[19]*omegaPowers[54]+A[55]*omegaPowers[18]+A[1]*omegaPowers[0]+A[37]*omegaPowers[36]+A[25]*omegaPowers[48]+A[49]*omegaPowers[24];

PSD11 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD11 > 144) continue;


dft = A[20]*omegaPowers[31]+A[21]*omegaPowers[44]+A[22]*omegaPowers[57]+A[23]*omegaPowers[70]+A[24]*omegaPowers[11]+A[26]*omegaPowers[37]+A[27]*omegaPowers[50]+A[29]*omegaPowers[4]+A[30]*omegaPowers[17]+A[32]*omegaPowers[43]+A[33]*omegaPowers[56]+A[34]*omegaPowers[69]+A[35]*omegaPowers[10]+A[36]*omegaPowers[23]+A[38]*omegaPowers[49]+A[39]*omegaPowers[62]+A[40]*omegaPowers[3]+A[41]*omegaPowers[16]+A[42]*omegaPowers[29]+A[44]*omegaPowers[55]+A[45]*omegaPowers[68]+A[47]*omegaPowers[22]+A[48]*omegaPowers[35]+A[50]*omegaPowers[61]+A[51]*omegaPowers[2]+A[52]*omegaPowers[15]+A[53]*omegaPowers[28]+A[54]*omegaPowers[41]+A[56]*omegaPowers[67]+A[57]*omegaPowers[8]+A[58]*omegaPowers[21]+A[59]*omegaPowers[34]+A[60]*omegaPowers[47]+A[62]*omegaPowers[1]+A[63]*omegaPowers[14]+A[65]*omegaPowers[40]+A[66]*omegaPowers[53]+A[68]*omegaPowers[7]+A[69]*omegaPowers[20]+A[70]*omegaPowers[33]+A[71]*omegaPowers[46]+A[72]*omegaPowers[59]+A[14]*omegaPowers[25]+A[15]*omegaPowers[38]+A[16]*omegaPowers[51]+A[17]*omegaPowers[64]+A[18]*omegaPowers[5]+A[2]*omegaPowers[13]+A[3]*omegaPowers[26]+A[4]*omegaPowers[39]+A[5]*omegaPowers[52]+A[6]*omegaPowers[65]+A[8]*omegaPowers[19]+A[9]*omegaPowers[32]+A[11]*omegaPowers[58]+A[12]*omegaPowers[71]+A[64]*omegaPowers[27]+A[10]*omegaPowers[45]+A[28]*omegaPowers[63]+A[46]*omegaPowers[9]+A[1]*omegaPowers[0]+A[7]*omegaPowers[6]+A[13]*omegaPowers[12]+A[19]*omegaPowers[18]+A[25]*omegaPowers[24]+A[31]*omegaPowers[30]+A[37]*omegaPowers[36]+A[43]*omegaPowers[42]+A[49]*omegaPowers[48]+A[55]*omegaPowers[54]+A[61]*omegaPowers[60]+A[67]*omegaPowers[66];

PSD13 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD13 > 144) continue;


dft = (A[36]+A[72])*omegaPowers[58]+(A[31]+A[67])*omegaPowers[60]+(A[26]+A[62])*omegaPowers[62]+(A[21]+A[57])*omegaPowers[64]+(A[16]+A[52])*omegaPowers[66]+(A[11]+A[47])*omegaPowers[68]+(A[6]+A[42])*omegaPowers[70]+(A[35]+A[71])*omegaPowers[44]+(A[30]+A[66])*omegaPowers[46]+(A[61]+A[25])*omegaPowers[48]+(A[20]+A[56])*omegaPowers[50]+(A[15]+A[51])*omegaPowers[52]+(A[10]+A[46])*omegaPowers[54]+(A[5]+A[41])*omegaPowers[56]+(A[24]+A[60])*omegaPowers[34]+(A[14]+A[50])*omegaPowers[38]+(A[45]+A[9])*omegaPowers[40]+(A[4]+A[40])*omegaPowers[42]+(A[13]+A[49])*omegaPowers[24]+(A[8]+A[44])*omegaPowers[26]+(A[3]+A[39])*omegaPowers[28]+(A[34]+A[70])*omegaPowers[30]+(A[29]+A[65])*omegaPowers[32]+(A[28]+A[64])*omegaPowers[18]+(A[23]+A[59])*omegaPowers[20]+(A[18]+A[54])*omegaPowers[22]+(A[7]+A[43])*omegaPowers[12]+(A[2]+A[38])*omegaPowers[14]+(A[69]+A[33])*omegaPowers[16]+(A[22]+A[58])*omegaPowers[6]+(A[53]+A[17])*omegaPowers[8]+(A[12]+A[48])*omegaPowers[10]+(A[32]+A[68])*omegaPowers[2]+(A[27]+A[63])*omegaPowers[4]+(A[37]+A[1])*omegaPowers[0]+(A[19]+A[55])*omegaPowers[36];

PSD14 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD14 > 144) continue;


dft = (A[1]+A[25]+A[49])*omegaPowers[0]+(A[6]+A[30]+A[54])*omegaPowers[3]+(A[11]+A[35]+A[59])*omegaPowers[6]+(A[16]+A[40]+A[64])*omegaPowers[9]+(A[21]+A[45]+A[69])*omegaPowers[12]+(A[2]+A[26]+A[50])*omegaPowers[15]+(A[7]+A[31]+A[55])*omegaPowers[18]+(A[12]+A[36]+A[60])*omegaPowers[21]+(A[17]+A[41]+A[65])*omegaPowers[24]+(A[22]+A[46]+A[70])*omegaPowers[27]+(A[3]+A[27]+A[51])*omegaPowers[30]+(A[8]+A[32]+A[56])*omegaPowers[33]+(A[13]+A[61]+A[37])*omegaPowers[36]+(A[18]+A[42]+A[66])*omegaPowers[39]+(A[23]+A[47]+A[71])*omegaPowers[42]+(A[4]+A[28]+A[52])*omegaPowers[45]+(A[9]+A[33]+A[57])*omegaPowers[48]+(A[14]+A[38]+A[62])*omegaPowers[51]+(A[19]+A[43]+A[67])*omegaPowers[54]+(A[24]+A[48]+A[72])*omegaPowers[57]+(A[5]+A[29]+A[53])*omegaPowers[60]+(A[10]+A[34]+A[58])*omegaPowers[63]+(A[15]+A[39]+A[63])*omegaPowers[66]+(A[20]+A[44]+A[68])*omegaPowers[69];

PSD15 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD15 > 144) continue;


dft = (A[10]+A[19]+A[28]+A[37]+A[46]+A[55]+A[64]+A[1])*omegaPowers[0]+(A[6]+A[15]+A[24]+A[33]+A[42]+A[51]+A[60]+A[69])*omegaPowers[8]+(A[2]+A[11]+A[20]+A[29]+A[38]+A[47]+A[56]+A[65])*omegaPowers[16]+(A[7]+A[16]+A[25]+A[34]+A[43]+A[52]+A[61]+A[70])*omegaPowers[24]+(A[3]+A[12]+A[21]+A[30]+A[39]+A[48]+A[57]+A[66])*omegaPowers[32]+(A[8]+A[17]+A[26]+A[35]+A[44]+A[53]+A[62]+A[71])*omegaPowers[40]+(A[4]+A[13]+A[22]+A[31]+A[40]+A[58]+A[67]+A[49])*omegaPowers[48]+(A[9]+A[18]+A[27]+A[36]+A[45]+A[54]+A[63]+A[72])*omegaPowers[56]+(A[5]+A[14]+A[23]+A[32]+A[41]+A[50]+A[59]+A[68])*omegaPowers[64];

PSD16 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD16 > 144) continue;


dft = A[62]*omegaPowers[29]+A[63]*omegaPowers[46]+A[66]*omegaPowers[25]+A[68]*omegaPowers[59]+A[69]*omegaPowers[4]+A[70]*omegaPowers[21]+A[71]*omegaPowers[38]+A[72]*omegaPowers[55]+A[2]*omegaPowers[17]+A[3]*omegaPowers[34]+A[4]*omegaPowers[51]+A[5]*omegaPowers[68]+A[6]*omegaPowers[13]+A[8]*omegaPowers[47]+A[11]*omegaPowers[26]+A[12]*omegaPowers[43]+A[14]*omegaPowers[5]+A[15]*omegaPowers[22]+A[16]*omegaPowers[39]+A[18]*omegaPowers[1]+A[20]*omegaPowers[35]+A[21]*omegaPowers[52]+A[22]*omegaPowers[69]+A[23]*omegaPowers[14]+A[24]*omegaPowers[31]+A[26]*omegaPowers[65]+A[27]*omegaPowers[10]+A[29]*omegaPowers[44]+A[30]*omegaPowers[61]+A[32]*omegaPowers[23]+A[34]*omegaPowers[57]+A[35]*omegaPowers[2]+A[36]*omegaPowers[19]+A[38]*omegaPowers[53]+A[39]*omegaPowers[70]+A[40]*omegaPowers[15]+A[42]*omegaPowers[49]+A[44]*omegaPowers[11]+A[45]*omegaPowers[28]+A[47]*omegaPowers[62]+A[48]*omegaPowers[7]+A[50]*omegaPowers[41]+A[51]*omegaPowers[58]+A[52]*omegaPowers[3]+A[53]*omegaPowers[20]+A[54]*omegaPowers[37]+A[56]*omegaPowers[71]+A[58]*omegaPowers[33]+A[59]*omegaPowers[50]+A[60]*omegaPowers[67]+A[9]*omegaPowers[64]+A[17]*omegaPowers[56]+A[33]*omegaPowers[40]+A[41]*omegaPowers[32]+A[57]*omegaPowers[16]+A[65]*omegaPowers[8]+A[61]*omegaPowers[12]+A[67]*omegaPowers[42]+A[7]*omegaPowers[30]+A[13]*omegaPowers[60]+A[31]*omegaPowers[6]+A[43]*omegaPowers[66]+A[1]*omegaPowers[0]+A[10]*omegaPowers[9]+A[19]*omegaPowers[18]+A[28]*omegaPowers[27]+A[37]*omegaPowers[36]+A[46]*omegaPowers[45]+A[55]*omegaPowers[54]+A[64]*omegaPowers[63]+A[25]*omegaPowers[48]+A[49]*omegaPowers[24];

PSD17 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD17 > 144) continue;


dft = A[34]*omegaPowers[51]+A[35]*omegaPowers[70]+A[36]*omegaPowers[17]+A[38]*omegaPowers[55]+A[39]*omegaPowers[2]+A[40]*omegaPowers[21]+A[42]*omegaPowers[59]+A[44]*omegaPowers[25]+A[47]*omegaPowers[10]+A[48]*omegaPowers[29]+A[50]*omegaPowers[67]+A[51]*omegaPowers[14]+A[52]*omegaPowers[33]+A[54]*omegaPowers[71]+A[56]*omegaPowers[37]+A[58]*omegaPowers[3]+A[59]*omegaPowers[22]+A[60]*omegaPowers[41]+A[62]*omegaPowers[7]+A[63]*omegaPowers[26]+A[66]*omegaPowers[11]+A[68]*omegaPowers[49]+A[70]*omegaPowers[15]+A[71]*omegaPowers[34]+A[72]*omegaPowers[53]+A[2]*omegaPowers[19]+A[3]*omegaPowers[38]+A[4]*omegaPowers[57]+A[6]*omegaPowers[23]+A[8]*omegaPowers[61]+A[11]*omegaPowers[46]+A[12]*omegaPowers[65]+A[14]*omegaPowers[31]+A[15]*omegaPowers[50]+A[16]*omegaPowers[69]+A[18]*omegaPowers[35]+A[20]*omegaPowers[1]+A[22]*omegaPowers[39]+A[23]*omegaPowers[58]+A[24]*omegaPowers[5]+A[26]*omegaPowers[43]+A[27]*omegaPowers[62]+A[30]*omegaPowers[47]+A[32]*omegaPowers[13]+A[31]*omegaPowers[66]+A[43]*omegaPowers[6]+A[67]*omegaPowers[30]+A[7]*omegaPowers[42]+A[46]*omegaPowers[63]+A[64]*omegaPowers[45]+A[10]*omegaPowers[27]+A[28]*omegaPowers[9]+A[19]*omegaPowers[54]+A[55]*omegaPowers[18]+A[1]*omegaPowers[0]+A[5]*omegaPowers[4]+A[9]*omegaPowers[8]+A[13]*omegaPowers[12]+A[17]*omegaPowers[16]+A[21]*omegaPowers[20]+A[25]*omegaPowers[24]+A[29]*omegaPowers[28]+A[33]*omegaPowers[32]+A[37]*omegaPowers[36]+A[41]*omegaPowers[40]+A[45]*omegaPowers[44]+A[49]*omegaPowers[48]+A[53]*omegaPowers[52]+A[57]*omegaPowers[56]+A[61]*omegaPowers[60]+A[65]*omegaPowers[64]+A[69]*omegaPowers[68];

PSD19 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD19 > 144) continue;


dft = (A[1]+A[19]+A[37]+A[55])*omegaPowers[0]+(A[12]+A[30]+A[48]+A[66])*omegaPowers[4]+(A[5]+A[23]+A[41]+A[59])*omegaPowers[8]+(A[16]+A[34]+A[52]+A[70])*omegaPowers[12]+(A[9]+A[27]+A[45]+A[63])*omegaPowers[16]+(A[2]+A[20]+A[38]+A[56])*omegaPowers[20]+(A[13]+A[31]+A[49]+A[67])*omegaPowers[24]+(A[6]+A[24]+A[42]+A[60])*omegaPowers[28]+(A[17]+A[35]+A[53]+A[71])*omegaPowers[32]+(A[10]+A[28]+A[46]+A[64])*omegaPowers[36]+(A[3]+A[21]+A[39]+A[57])*omegaPowers[40]+(A[14]+A[32]+A[50]+A[68])*omegaPowers[44]+(A[7]+A[43]+A[61]+A[25])*omegaPowers[48]+(A[18]+A[36]+A[54]+A[72])*omegaPowers[52]+(A[11]+A[29]+A[47]+A[65])*omegaPowers[56]+(A[4]+A[22]+A[40]+A[58])*omegaPowers[60]+(A[15]+A[33]+A[51]+A[69])*omegaPowers[64]+(A[8]+A[26]+A[44]+A[62])*omegaPowers[68];

PSD20 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD20 > 144) continue;


dft = (A[1]+A[25]+A[49])*omegaPowers[0]+(A[8]+A[32]+A[56])*omegaPowers[3]+(A[15]+A[39]+A[63])*omegaPowers[6]+(A[22]+A[46]+A[70])*omegaPowers[9]+(A[5]+A[29]+A[53])*omegaPowers[12]+(A[12]+A[36]+A[60])*omegaPowers[15]+(A[19]+A[43]+A[67])*omegaPowers[18]+(A[2]+A[26]+A[50])*omegaPowers[21]+(A[9]+A[33]+A[57])*omegaPowers[24]+(A[16]+A[40]+A[64])*omegaPowers[27]+(A[23]+A[47]+A[71])*omegaPowers[30]+(A[6]+A[30]+A[54])*omegaPowers[33]+(A[13]+A[61]+A[37])*omegaPowers[36]+(A[20]+A[44]+A[68])*omegaPowers[39]+(A[3]+A[27]+A[51])*omegaPowers[42]+(A[10]+A[34]+A[58])*omegaPowers[45]+(A[17]+A[41]+A[65])*omegaPowers[48]+(A[24]+A[48]+A[72])*omegaPowers[51]+(A[7]+A[31]+A[55])*omegaPowers[54]+(A[14]+A[38]+A[62])*omegaPowers[57]+(A[21]+A[45]+A[69])*omegaPowers[60]+(A[4]+A[28]+A[52])*omegaPowers[63]+(A[11]+A[35]+A[59])*omegaPowers[66]+(A[18]+A[42]+A[66])*omegaPowers[69];

PSD21 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD21 > 144) continue;


dft = (A[23]+A[59])*omegaPowers[52]+(A[69]+A[33])*omegaPowers[56]+(A[20]+A[56])*omegaPowers[58]+(A[30]+A[66])*omegaPowers[62]+(A[53]+A[17])*omegaPowers[64]+(A[4]+A[40])*omegaPowers[66]+(A[27]+A[63])*omegaPowers[68]+(A[14]+A[50])*omegaPowers[70]+(A[29]+A[65])*omegaPowers[40]+(A[16]+A[52])*omegaPowers[42]+(A[3]+A[39])*omegaPowers[44]+(A[26]+A[62])*omegaPowers[46]+(A[36]+A[72])*omegaPowers[50]+(A[22]+A[58])*omegaPowers[30]+(A[45]+A[9])*omegaPowers[32]+(A[32]+A[68])*omegaPowers[34]+(A[6]+A[42])*omegaPowers[38]+(A[2]+A[38])*omegaPowers[22]+(A[12]+A[48])*omegaPowers[26]+(A[35]+A[71])*omegaPowers[28]+(A[5]+A[41])*omegaPowers[16]+(A[15]+A[51])*omegaPowers[20]+(A[8]+A[44])*omegaPowers[10]+(A[18]+A[54])*omegaPowers[14]+(A[11]+A[47])*omegaPowers[4]+(A[34]+A[70])*omegaPowers[6]+(A[21]+A[57])*omegaPowers[8]+(A[24]+A[60])*omegaPowers[2]+(A[10]+A[46])*omegaPowers[54]+(A[28]+A[64])*omegaPowers[18]+(A[13]+A[49])*omegaPowers[48]+(A[7]+A[43])*omegaPowers[60]+(A[37]+A[1])*omegaPowers[0]+(A[31]+A[67])*omegaPowers[12]+(A[61]+A[25])*omegaPowers[24]+(A[19]+A[55])*omegaPowers[36];

PSD22 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD22 > 144) continue;


dft = A[2]*omegaPowers[23]+A[3]*omegaPowers[46]+A[4]*omegaPowers[69]+A[6]*omegaPowers[43]+A[8]*omegaPowers[17]+A[11]*omegaPowers[14]+A[12]*omegaPowers[37]+A[14]*omegaPowers[11]+A[15]*omegaPowers[34]+A[16]*omegaPowers[57]+A[18]*omegaPowers[31]+A[20]*omegaPowers[5]+A[22]*omegaPowers[51]+A[23]*omegaPowers[2]+A[24]*omegaPowers[25]+A[26]*omegaPowers[71]+A[27]*omegaPowers[22]+A[30]*omegaPowers[19]+A[32]*omegaPowers[65]+A[34]*omegaPowers[39]+A[35]*omegaPowers[62]+A[36]*omegaPowers[13]+A[38]*omegaPowers[59]+A[39]*omegaPowers[10]+A[40]*omegaPowers[33]+A[42]*omegaPowers[7]+A[44]*omegaPowers[53]+A[47]*omegaPowers[50]+A[48]*omegaPowers[1]+A[50]*omegaPowers[47]+A[51]*omegaPowers[70]+A[52]*omegaPowers[21]+A[54]*omegaPowers[67]+A[56]*omegaPowers[41]+A[58]*omegaPowers[15]+A[59]*omegaPowers[38]+A[60]*omegaPowers[61]+A[62]*omegaPowers[35]+A[63]*omegaPowers[58]+A[66]*omegaPowers[55]+A[68]*omegaPowers[29]+A[70]*omegaPowers[3]+A[71]*omegaPowers[26]+A[72]*omegaPowers[49]+A[28]*omegaPowers[45]+A[46]*omegaPowers[27]+A[64]*omegaPowers[9]+A[10]*omegaPowers[63]+A[57]*omegaPowers[64]+A[61]*omegaPowers[12]+A[65]*omegaPowers[32]+A[69]*omegaPowers[52]+A[5]*omegaPowers[20]+A[9]*omegaPowers[40]+A[13]*omegaPowers[60]+A[17]*omegaPowers[8]+A[21]*omegaPowers[28]+A[29]*omegaPowers[68]+A[33]*omegaPowers[16]+A[41]*omegaPowers[56]+A[45]*omegaPowers[4]+A[53]*omegaPowers[44]+A[43]*omegaPowers[30]+A[67]*omegaPowers[6]+A[7]*omegaPowers[66]+A[31]*omegaPowers[42]+A[19]*omegaPowers[54]+A[55]*omegaPowers[18]+A[1]*omegaPowers[0]+A[37]*omegaPowers[36]+A[25]*omegaPowers[48]+A[49]*omegaPowers[24];

PSD23 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD23 > 144) continue;


dft = A[71]*omegaPowers[22]+A[72]*omegaPowers[47]+A[2]*omegaPowers[25]+A[3]*omegaPowers[50]+A[6]*omegaPowers[53]+A[8]*omegaPowers[31]+A[11]*omegaPowers[34]+A[12]*omegaPowers[59]+A[14]*omegaPowers[37]+A[15]*omegaPowers[62]+A[18]*omegaPowers[65]+A[20]*omegaPowers[43]+A[23]*omegaPowers[46]+A[24]*omegaPowers[71]+A[26]*omegaPowers[49]+A[27]*omegaPowers[2]+A[30]*omegaPowers[5]+A[32]*omegaPowers[55]+A[35]*omegaPowers[58]+A[36]*omegaPowers[11]+A[38]*omegaPowers[61]+A[39]*omegaPowers[14]+A[42]*omegaPowers[17]+A[44]*omegaPowers[67]+A[47]*omegaPowers[70]+A[48]*omegaPowers[23]+A[50]*omegaPowers[1]+A[51]*omegaPowers[26]+A[54]*omegaPowers[29]+A[56]*omegaPowers[7]+A[59]*omegaPowers[10]+A[60]*omegaPowers[35]+A[62]*omegaPowers[13]+A[63]*omegaPowers[38]+A[66]*omegaPowers[41]+A[68]*omegaPowers[19]+A[29]*omegaPowers[52]+A[33]*omegaPowers[8]+A[41]*omegaPowers[64]+A[45]*omegaPowers[20]+A[53]*omegaPowers[4]+A[57]*omegaPowers[32]+A[65]*omegaPowers[16]+A[69]*omegaPowers[44]+A[5]*omegaPowers[28]+A[9]*omegaPowers[56]+A[17]*omegaPowers[40]+A[21]*omegaPowers[68]+A[1]*omegaPowers[0]+A[4]*omegaPowers[3]+A[7]*omegaPowers[6]+A[10]*omegaPowers[9]+A[13]*omegaPowers[12]+A[16]*omegaPowers[15]+A[19]*omegaPowers[18]+A[22]*omegaPowers[21]+A[25]*omegaPowers[24]+A[28]*omegaPowers[27]+A[31]*omegaPowers[30]+A[34]*omegaPowers[33]+A[37]*omegaPowers[36]+A[40]*omegaPowers[39]+A[43]*omegaPowers[42]+A[46]*omegaPowers[45]+A[49]*omegaPowers[48]+A[52]*omegaPowers[51]+A[55]*omegaPowers[54]+A[58]*omegaPowers[57]+A[61]*omegaPowers[60]+A[64]*omegaPowers[63]+A[67]*omegaPowers[66]+A[70]*omegaPowers[69];

PSD25 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD25 > 144) continue;


dft = (A[14]+A[50])*omegaPowers[50]+(A[3]+A[39])*omegaPowers[52]+(A[53]+A[17])*omegaPowers[56]+(A[6]+A[42])*omegaPowers[58]+(A[20]+A[56])*omegaPowers[62]+(A[45]+A[9])*omegaPowers[64]+(A[34]+A[70])*omegaPowers[66]+(A[23]+A[59])*omegaPowers[68]+(A[12]+A[48])*omegaPowers[70]+(A[8]+A[44])*omegaPowers[38]+(A[69]+A[33])*omegaPowers[40]+(A[22]+A[58])*omegaPowers[42]+(A[11]+A[47])*omegaPowers[44]+(A[36]+A[72])*omegaPowers[46]+(A[27]+A[63])*omegaPowers[28]+(A[16]+A[52])*omegaPowers[30]+(A[5]+A[41])*omegaPowers[32]+(A[30]+A[66])*omegaPowers[34]+(A[35]+A[71])*omegaPowers[20]+(A[24]+A[60])*omegaPowers[22]+(A[2]+A[38])*omegaPowers[26]+(A[32]+A[68])*omegaPowers[14]+(A[21]+A[57])*omegaPowers[16]+(A[29]+A[65])*omegaPowers[8]+(A[18]+A[54])*omegaPowers[10]+(A[26]+A[62])*omegaPowers[2]+(A[15]+A[51])*omegaPowers[4]+(A[4]+A[40])*omegaPowers[6]+(A[31]+A[67])*omegaPowers[60]+(A[61]+A[25])*omegaPowers[48]+(A[13]+A[49])*omegaPowers[24]+(A[7]+A[43])*omegaPowers[12]+(A[28]+A[64])*omegaPowers[54]+(A[37]+A[1])*omegaPowers[0]+(A[10]+A[46])*omegaPowers[18]+(A[19]+A[55])*omegaPowers[36];

PSD26 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD26 > 144) continue;


dft = (A[41]+A[49]+A[57]+A[65]+A[9]+A[17]+A[25]+A[33]+A[1])*omegaPowers[0]+(A[36]+A[44]+A[52]+A[60]+A[68]+A[4]+A[12]+A[20]+A[28])*omegaPowers[9]+(A[7]+A[15]+A[23]+A[31]+A[39]+A[47]+A[55]+A[63]+A[71])*omegaPowers[18]+(A[42]+A[50]+A[58]+A[66]+A[2]+A[18]+A[26]+A[34]+A[10])*omegaPowers[27]+(A[45]+A[53]+A[61]+A[69]+A[5]+A[13]+A[21]+A[29]+A[37])*omegaPowers[36]+(A[8]+A[16]+A[24]+A[32]+A[40]+A[48]+A[56]+A[64]+A[72])*omegaPowers[45]+(A[35]+A[43]+A[51]+A[59]+A[67]+A[3]+A[11]+A[27]+A[19])*omegaPowers[54]+(A[6]+A[14]+A[22]+A[30]+A[38]+A[46]+A[54]+A[62]+A[70])*omegaPowers[63];

PSD27 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD27 > 144) continue;


dft = (A[1]+A[19]+A[37]+A[55])*omegaPowers[0]+(A[14]+A[32]+A[50]+A[68])*omegaPowers[4]+(A[9]+A[27]+A[45]+A[63])*omegaPowers[8]+(A[4]+A[22]+A[40]+A[58])*omegaPowers[12]+(A[17]+A[35]+A[53]+A[71])*omegaPowers[16]+(A[12]+A[30]+A[48]+A[66])*omegaPowers[20]+(A[7]+A[43]+A[61]+A[25])*omegaPowers[24]+(A[2]+A[20]+A[38]+A[56])*omegaPowers[28]+(A[15]+A[33]+A[51]+A[69])*omegaPowers[32]+(A[10]+A[28]+A[46]+A[64])*omegaPowers[36]+(A[5]+A[23]+A[41]+A[59])*omegaPowers[40]+(A[18]+A[36]+A[54]+A[72])*omegaPowers[44]+(A[13]+A[31]+A[49]+A[67])*omegaPowers[48]+(A[8]+A[26]+A[44]+A[62])*omegaPowers[52]+(A[3]+A[21]+A[39]+A[57])*omegaPowers[56]+(A[16]+A[34]+A[52]+A[70])*omegaPowers[60]+(A[11]+A[29]+A[47]+A[65])*omegaPowers[64]+(A[6]+A[24]+A[42]+A[60])*omegaPowers[68];

PSD28 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD28 > 144) continue;


dft = A[2]*omegaPowers[29]+A[3]*omegaPowers[58]+A[6]*omegaPowers[1]+A[8]*omegaPowers[59]+A[11]*omegaPowers[2]+A[12]*omegaPowers[31]+A[14]*omegaPowers[17]+A[15]*omegaPowers[46]+A[18]*omegaPowers[61]+A[20]*omegaPowers[47]+A[23]*omegaPowers[62]+A[24]*omegaPowers[19]+A[26]*omegaPowers[5]+A[27]*omegaPowers[34]+A[30]*omegaPowers[49]+A[32]*omegaPowers[35]+A[35]*omegaPowers[50]+A[36]*omegaPowers[7]+A[38]*omegaPowers[65]+A[39]*omegaPowers[22]+A[42]*omegaPowers[37]+A[44]*omegaPowers[23]+A[47]*omegaPowers[38]+A[48]*omegaPowers[67]+A[50]*omegaPowers[53]+A[51]*omegaPowers[10]+A[54]*omegaPowers[25]+A[56]*omegaPowers[11]+A[59]*omegaPowers[26]+A[60]*omegaPowers[55]+A[62]*omegaPowers[41]+A[63]*omegaPowers[70]+A[66]*omegaPowers[13]+A[68]*omegaPowers[71]+A[71]*omegaPowers[14]+A[72]*omegaPowers[43]+A[58]*omegaPowers[69]+A[61]*omegaPowers[12]+A[64]*omegaPowers[27]+A[67]*omegaPowers[42]+A[70]*omegaPowers[57]+A[4]*omegaPowers[15]+A[7]*omegaPowers[30]+A[10]*omegaPowers[45]+A[13]*omegaPowers[60]+A[16]*omegaPowers[3]+A[22]*omegaPowers[33]+A[28]*omegaPowers[63]+A[31]*omegaPowers[6]+A[34]*omegaPowers[21]+A[40]*omegaPowers[51]+A[43]*omegaPowers[66]+A[46]*omegaPowers[9]+A[52]*omegaPowers[39]+A[45]*omegaPowers[52]+A[53]*omegaPowers[68]+A[57]*omegaPowers[40]+A[65]*omegaPowers[56]+A[69]*omegaPowers[28]+A[5]*omegaPowers[44]+A[9]*omegaPowers[16]+A[17]*omegaPowers[32]+A[21]*omegaPowers[4]+A[29]*omegaPowers[20]+A[33]*omegaPowers[64]+A[41]*omegaPowers[8]+A[1]*omegaPowers[0]+A[19]*omegaPowers[18]+A[37]*omegaPowers[36]+A[55]*omegaPowers[54]+A[25]*omegaPowers[48]+A[49]*omegaPowers[24];

PSD29 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD29 > 144) continue;


dft = A[59]*omegaPowers[70]+A[60]*omegaPowers[29]+A[62]*omegaPowers[19]+A[63]*omegaPowers[50]+A[66]*omegaPowers[71]+A[68]*omegaPowers[61]+A[71]*omegaPowers[10]+A[72]*omegaPowers[41]+A[2]*omegaPowers[31]+A[3]*omegaPowers[62]+A[6]*omegaPowers[11]+A[8]*omegaPowers[1]+A[11]*omegaPowers[22]+A[12]*omegaPowers[53]+A[14]*omegaPowers[43]+A[15]*omegaPowers[2]+A[18]*omegaPowers[23]+A[20]*omegaPowers[13]+A[23]*omegaPowers[34]+A[24]*omegaPowers[65]+A[26]*omegaPowers[55]+A[27]*omegaPowers[14]+A[30]*omegaPowers[35]+A[32]*omegaPowers[25]+A[35]*omegaPowers[46]+A[36]*omegaPowers[5]+A[38]*omegaPowers[67]+A[39]*omegaPowers[26]+A[42]*omegaPowers[47]+A[44]*omegaPowers[37]+A[47]*omegaPowers[58]+A[48]*omegaPowers[17]+A[50]*omegaPowers[7]+A[51]*omegaPowers[38]+A[54]*omegaPowers[59]+A[56]*omegaPowers[49]+A[21]*omegaPowers[44]+A[29]*omegaPowers[4]+A[33]*omegaPowers[56]+A[41]*omegaPowers[16]+A[45]*omegaPowers[68]+A[53]*omegaPowers[28]+A[57]*omegaPowers[8]+A[65]*omegaPowers[40]+A[69]*omegaPowers[20]+A[28]*omegaPowers[45]+A[31]*omegaPowers[66]+A[34]*omegaPowers[15]+A[40]*omegaPowers[57]+A[43]*omegaPowers[6]+A[46]*omegaPowers[27]+A[52]*omegaPowers[69]+A[58]*omegaPowers[39]+A[17]*omegaPowers[64]+A[64]*omegaPowers[9]+A[67]*omegaPowers[30]+A[70]*omegaPowers[51]+A[5]*omegaPowers[52]+A[9]*omegaPowers[32]+A[4]*omegaPowers[21]+A[7]*omegaPowers[42]+A[10]*omegaPowers[63]+A[16]*omegaPowers[33]+A[22]*omegaPowers[3]+A[19]*omegaPowers[54]+A[55]*omegaPowers[18]+A[1]*omegaPowers[0]+A[13]*omegaPowers[12]+A[25]*omegaPowers[24]+A[37]*omegaPowers[36]+A[49]*omegaPowers[48]+A[61]*omegaPowers[60];

PSD31 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD31 > 144) continue;


dft = (A[10]+A[19]+A[28]+A[37]+A[46]+A[55]+A[64]+A[1])*omegaPowers[0]+(A[8]+A[17]+A[26]+A[35]+A[44]+A[53]+A[62]+A[71])*omegaPowers[8]+(A[6]+A[15]+A[24]+A[33]+A[42]+A[51]+A[60]+A[69])*omegaPowers[16]+(A[4]+A[13]+A[22]+A[31]+A[40]+A[58]+A[67]+A[49])*omegaPowers[24]+(A[2]+A[11]+A[20]+A[29]+A[38]+A[47]+A[56]+A[65])*omegaPowers[32]+(A[9]+A[18]+A[27]+A[36]+A[45]+A[54]+A[63]+A[72])*omegaPowers[40]+(A[7]+A[16]+A[25]+A[34]+A[43]+A[52]+A[61]+A[70])*omegaPowers[48]+(A[5]+A[14]+A[23]+A[32]+A[41]+A[50]+A[59]+A[68])*omegaPowers[56]+(A[3]+A[12]+A[21]+A[30]+A[39]+A[48]+A[57]+A[66])*omegaPowers[64];

PSD32 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD32 > 144) continue;


dft = (A[1]+A[25]+A[49])*omegaPowers[0]+(A[12]+A[36]+A[60])*omegaPowers[3]+(A[23]+A[47]+A[71])*omegaPowers[6]+(A[10]+A[34]+A[58])*omegaPowers[9]+(A[21]+A[45]+A[69])*omegaPowers[12]+(A[8]+A[32]+A[56])*omegaPowers[15]+(A[19]+A[43]+A[67])*omegaPowers[18]+(A[6]+A[30]+A[54])*omegaPowers[21]+(A[17]+A[41]+A[65])*omegaPowers[24]+(A[4]+A[28]+A[52])*omegaPowers[27]+(A[15]+A[39]+A[63])*omegaPowers[30]+(A[2]+A[26]+A[50])*omegaPowers[33]+(A[13]+A[61]+A[37])*omegaPowers[36]+(A[24]+A[48]+A[72])*omegaPowers[39]+(A[11]+A[35]+A[59])*omegaPowers[42]+(A[22]+A[46]+A[70])*omegaPowers[45]+(A[9]+A[33]+A[57])*omegaPowers[48]+(A[20]+A[44]+A[68])*omegaPowers[51]+(A[7]+A[31]+A[55])*omegaPowers[54]+(A[18]+A[42]+A[66])*omegaPowers[57]+(A[5]+A[29]+A[53])*omegaPowers[60]+(A[16]+A[40]+A[64])*omegaPowers[63]+(A[3]+A[27]+A[51])*omegaPowers[66]+(A[14]+A[38]+A[62])*omegaPowers[69];

PSD33 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD33 > 144) continue;


dft = (A[45]+A[9])*omegaPowers[56]+(A[26]+A[62])*omegaPowers[58]+(A[24]+A[60])*omegaPowers[62]+(A[5]+A[41])*omegaPowers[64]+(A[3]+A[39])*omegaPowers[68]+(A[20]+A[56])*omegaPowers[70]+(A[53]+A[17])*omegaPowers[40]+(A[15]+A[51])*omegaPowers[44]+(A[32]+A[68])*omegaPowers[46]+(A[30]+A[66])*omegaPowers[50]+(A[11]+A[47])*omegaPowers[52]+(A[21]+A[57])*omegaPowers[32]+(A[2]+A[38])*omegaPowers[34]+(A[36]+A[72])*omegaPowers[38]+(A[8]+A[44])*omegaPowers[22]+(A[6]+A[42])*omegaPowers[26]+(A[23]+A[59])*omegaPowers[28]+(A[29]+A[65])*omegaPowers[16]+(A[27]+A[63])*omegaPowers[20]+(A[14]+A[50])*omegaPowers[10]+(A[12]+A[48])*omegaPowers[14]+(A[35]+A[71])*omegaPowers[4]+(A[69]+A[33])*omegaPowers[8]+(A[18]+A[54])*omegaPowers[2]+(A[22]+A[58])*omegaPowers[66]+(A[13]+A[49])*omegaPowers[48]+(A[28]+A[64])*omegaPowers[54]+(A[7]+A[43])*omegaPowers[60]+(A[37]+A[1])*omegaPowers[0]+(A[16]+A[52])*omegaPowers[6]+(A[31]+A[67])*omegaPowers[12]+(A[10]+A[46])*omegaPowers[18]+(A[61]+A[25])*omegaPowers[24]+(A[4]+A[40])*omegaPowers[30]+(A[19]+A[55])*omegaPowers[36]+(A[34]+A[70])*omegaPowers[42];

PSD34 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD34 > 144) continue;


dft = A[2]*omegaPowers[35]+A[3]*omegaPowers[70]+A[6]*omegaPowers[31]+A[8]*omegaPowers[29]+A[11]*omegaPowers[62]+A[12]*omegaPowers[25]+A[14]*omegaPowers[23]+A[15]*omegaPowers[58]+A[18]*omegaPowers[19]+A[20]*omegaPowers[17]+A[23]*omegaPowers[50]+A[24]*omegaPowers[13]+A[26]*omegaPowers[11]+A[27]*omegaPowers[46]+A[30]*omegaPowers[7]+A[32]*omegaPowers[5]+A[35]*omegaPowers[38]+A[36]*omegaPowers[1]+A[38]*omegaPowers[71]+A[39]*omegaPowers[34]+A[42]*omegaPowers[67]+A[44]*omegaPowers[65]+A[47]*omegaPowers[26]+A[48]*omegaPowers[61]+A[50]*omegaPowers[59]+A[51]*omegaPowers[22]+A[54]*omegaPowers[55]+A[56]*omegaPowers[53]+A[59]*omegaPowers[14]+A[60]*omegaPowers[49]+A[62]*omegaPowers[47]+A[63]*omegaPowers[10]+A[66]*omegaPowers[43]+A[68]*omegaPowers[41]+A[71]*omegaPowers[2]+A[72]*omegaPowers[37]+A[69]*omegaPowers[4]+A[5]*omegaPowers[68]+A[21]*omegaPowers[52]+A[29]*omegaPowers[44]+A[45]*omegaPowers[28]+A[53]*omegaPowers[20]+A[9]*omegaPowers[64]+A[17]*omegaPowers[56]+A[33]*omegaPowers[40]+A[41]*omegaPowers[32]+A[57]*omegaPowers[16]+A[65]*omegaPowers[8]+A[61]*omegaPowers[12]+A[13]*omegaPowers[60]+A[43]*omegaPowers[30]+A[46]*omegaPowers[63]+A[52]*omegaPowers[57]+A[58]*omegaPowers[51]+A[64]*omegaPowers[45]+A[67]*omegaPowers[6]+A[70]*omegaPowers[39]+A[4]*omegaPowers[33]+A[7]*omegaPowers[66]+A[10]*omegaPowers[27]+A[16]*omegaPowers[21]+A[22]*omegaPowers[15]+A[28]*omegaPowers[9]+A[31]*omegaPowers[42]+A[34]*omegaPowers[3]+A[40]*omegaPowers[69]+A[19]*omegaPowers[54]+A[55]*omegaPowers[18]+A[1]*omegaPowers[0]+A[37]*omegaPowers[36]+A[25]*omegaPowers[48]+A[49]*omegaPowers[24];

PSD35 = creal(dft)*creal(dft) + cimag(dft)*cimag(dft);

if (PSD35 > 144) continue;


//orderly check here


int x[10];

x[0] = 4; x[1] = 3; x[2] = 2; x[3] = 1; x[4] = 0; x[5] = 9; x[6] = 8; x[7] = 7; x[8] = 6; x[9] = 5;

int  ld1, ld2, ld3, ld4, ld5, ld6, ld7, ld8, ld9, ld10, ld11, ld12, ld13, ld14, ld15, ld16, ld17, ld18, ld19, ld20, ld21, ld22, ld23, ld24, ld25, ld26, ld27, ld28, ld29, ld30, ld31, ld32, ld33, ld34, ld35, ld36; 

ld1 = x[(int)rint(PSD1) % 10];
ld2 = x[(int)rint(PSD2) % 10];
ld3 = x[(int)rint(PSD3) % 10];
ld4 = x[(int)rint(PSD4) % 10];
ld5 = x[(int)rint(PSD5) % 10];
ld7 = x[(int)rint(PSD7) % 10];
ld8 = x[(int)rint(PSD8) % 10];
ld9 = x[(int)rint(PSD9) % 10];
ld10 = x[(int)rint(PSD10) % 10];
ld11 = x[(int)rint(PSD11) % 10];
ld13 = x[(int)rint(PSD13) % 10];
ld14 = x[(int)rint(PSD14) % 10];
ld15 = x[(int)rint(PSD15) % 10];
ld16 = x[(int)rint(PSD16) % 10];
ld17 = x[(int)rint(PSD17) % 10];
ld19 = x[(int)rint(PSD19) % 10];
ld20 = x[(int)rint(PSD20) % 10];
ld21 = x[(int)rint(PSD21) % 10];
ld22 = x[(int)rint(PSD22) % 10];
ld23 = x[(int)rint(PSD23) % 10];
ld25 = x[(int)rint(PSD25) % 10];
ld26 = x[(int)rint(PSD26) % 10];
ld27 = x[(int)rint(PSD27) % 10];
ld28 = x[(int)rint(PSD28) % 10];
ld29 = x[(int)rint(PSD29) % 10];
ld31 = x[(int)rint(PSD31) % 10];
ld32 = x[(int)rint(PSD32) % 10];
ld33 = x[(int)rint(PSD33) % 10];
ld34 = x[(int)rint(PSD34) % 10];
ld35 = x[(int)rint(PSD35) % 10];

printf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", ld1, ld2, ld3, ld4, ld5, ld7, ld8, ld9, ld10, ld11, ld13, ld14, ld15, ld16, ld17, ld19, ld20, ld21, ld22, ld23, ld25, ld26, ld27, ld28, ld29, ld31, ld32, ld33, ld34, ld35);


	}
  return(0);
}
