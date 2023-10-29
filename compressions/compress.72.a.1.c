#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include<time.h>

int main (void)
{

  printf("test\n");

  unsigned long long int count = 0;

int i, v = 72;

int Om6s[] = {0,12};

int Ozs[] = {0,1,2,3,4,5,7,8,9,10,11};

int Op6s[] = {0,6};

int xm6[2], xp6[2], xz[11], A[73];

float  PSD1, PSD2, PSD3, PSD4, PSD5, PSD6, PSD7, PSD8, PSD9, PSD10, PSD11, PSD12, PSD13, PSD14, PSD15, PSD16, PSD17, PSD18, PSD19, PSD20, PSD21, PSD22, PSD23, PSD24, PSD25, PSD26, PSD27, PSD28, PSD29, PSD30, PSD31, PSD32, PSD33, PSD34, PSD35, PSD36; 

complex omegaPowers[72], omega, dft;

omega = .9961946981+.8715574277e-1*I;

omegaPowers[0] = 1.0 + 0.0*I;

omegaPowers[1] = omega;

for(i=2; i < v; i++) { omegaPowers[i] = omegaPowers[i-1]*omega; }

A[6] = 1; A[18] = 1; A[30] = 1; A[42] = 1; A[54] = 1; A[66] = 1;
A[12] = -1; A[24] = -1; A[36] = -1; A[48] = -1; A[60] = -1; A[72] = -1;


clock_t start = clock();


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

    count++;

    if(count % 1000000000 == 0) {
      printf("%lld, time:%d\n", count, (clock() - start) / CLOCKS_PER_SEC);
    }


	}
  printf("%lld, time:%d\n", count, (clock() - start) / CLOCKS_PER_SEC);
  return(0);
}

//114914600000 
//10240000000000

//193000000000
//110000000000, time:60s

//==> implies that *just* the 20 loops takes over an hour (~1h40m)