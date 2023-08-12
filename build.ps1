echo "Compiling array.c"
gcc -Wall -g -c array.c -o array.o
echo "Compiling golay.c"
gcc -Wall -g -c golay.c -o golay.o -LC://Users/turtl/OneDrive/Desktop/proj/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3
echo "Compiling main.c"
gcc -Wall -g -c main.c -o main.o
echo "Compiling fourier.c"
gcc -Wall -Wextra -g -c fourier.c -o fourier.o -LC://Users/turtl/OneDrive/Desktop/proj/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3

echo "Converting to executable"
gcc -g main.o golay.o array.o fourier.o -o find -LC://Users/turtl/OneDrive/Desktop/proj/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3

.\find
