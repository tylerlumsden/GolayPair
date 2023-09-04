.PHONY = all clean

CC = g++
all: fourier.o equivalence.o array.o golay.o generate_classes match_pairs

equivalence.o: equivalence.cpp golay.h coprimes.h
	$(CC) -Wall -g -c equivalence.cpp -o equivalence.o

array.o: array.cpp golay.h
	$(CC) -Wall -g -c array.cpp -o array.o

fourier.o: fourier.cpp golay.h
	$(CC) -Wall -Wextra -g -c fourier.cpp -o fourier.o -L./fftw-3.3.5-dll64 -llibfftw3-3

golay.o: golay.h
	$(CC) -Wall -g -c golay.cpp -o golay.o

match_pairs: match_pairs.cpp golay.h golay.o
	$(CC) -Wall -g match_pairs.cpp golay.o -o match_pairs

generate_classes: generate_classes.cpp golay.h array.o fourier.o equivalence.o
	$(CC) -Wall -g generate_classes.cpp equivalence.o array.o fourier.o -o generate_classes -L./fftw-3.3.5-dll64 -llibfftw3-3


clean:
	@echo "Cleaning up..."
	rm -f equivalence.o array.o fourier.o golay.o find