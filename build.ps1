echo "Compiling equivalence.c"
g++ -Wall -g -c equivalence.cpp -o equivalence.o
echo "Compiling array.c"
g++ -Wall -g -c array.cpp -o array.o
echo "Compiling golay.c"
<<<<<<< HEAD
g++ -Wall -g -c golay.cpp -o golay.o -LC://Users/turtl/OneDrive/Desktop/proj/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3
=======
gcc -Wall -g -c golay.c -o golay.o -LC://Users/turtl/Desktop/proj/GolayPair4/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3
>>>>>>> 7599bda0501d8ebf1614ebc5132b31219890673a
echo "Compiling main.c"
g++ -Wall -g -c main.cpp -o main.o
echo "Compiling fourier.c"
<<<<<<< HEAD
g++ -Wall -Wextra -g -c fourier.cpp -o fourier.o -LC://Users/turtl/OneDrive/Desktop/proj/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3

echo "Converting to executable"
g++ -g main.o golay.o array.o fourier.o equivalence.o -o find -LC://Users/turtl/OneDrive/Desktop/proj/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3
=======
gcc -Wall -Wextra -g -c fourier.c -o fourier.o -LC://Users/turtl/Desktop/proj/GolayPair4/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3

echo "Converting to executable"
gcc -g main.o golay.o array.o fourier.o -o find -LC://Users/turtl/Desktop/proj/GolayPair4/GolayPair/fftw-3.3.5-dll64 -llibfftw3-3
>>>>>>> 7599bda0501d8ebf1614ebc5132b31219890673a

echo "Running program"
.\find
