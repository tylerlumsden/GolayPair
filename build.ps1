echo "Compiling equivalence.c"
g++ -Wall -g -c equivalence.cpp -o equivalence.o
echo "Compiling array.c"
g++ -Wall -g -c array.cpp -o array.o
echo "Compiling golay.c"
g++ -Wall -g -c golay.cpp -o golay.o -LC://Users/turtl/Desktop/proj/GolayPair5/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3
echo "Compiling main.c"
g++ -Wall -g -c main.cpp -o main.o
echo "Compiling fourier.c"
g++ -Wall -Wextra -g -c fourier.cpp -o fourier.o -LC://Users/turtl/Desktop/proj/GolayPair5/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3

echo "Converting to executable"
g++ -g main.o golay.o array.o fourier.o equivalence.o -o find -LC://Users/turtl/Desktop/proj/GolayPair5/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3

echo "Running program"
.\find | Tee-Object -a results/runtime.log
