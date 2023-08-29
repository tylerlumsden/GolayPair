.PHONY = all clean

CC = g++
all: golay.o fourier.o equivalence.o array.o find

equivalence.o: equivalence.cpp golay.h coprimes.h
	$(CC) -Wall -g -c equivalence.cpp -o equivalence.o

array.o: array.cpp golay.h
	$(CC) -Wall -g -c array.cpp -o array.o

fourier.o: fourier.cpp golay.h
	$(CC) -Wall -Wextra -g -c fourier.cpp -o fourier.o -L./fftw-3.3.5-dll64 -llibfftw3-3

golay.o: golay.cpp golay.h array.o fourier.o equivalence.o
	$(CC) -Wall -g -c golay.cpp -o golay.o -L./fftw-3.3.5-dll64 -llibfftw3-3

find: main.cpp golay.o array.o fourier.o equivalence.o
	$(CC) -g main.cpp golay.o array.o fourier.o equivalence.o -o find -L./fftw-3.3.5-dll64 -llibfftw3-3


clean:
	@echo "Cleaning up..."
	rm -f equivalence.o array.o fourier.o golay.o find