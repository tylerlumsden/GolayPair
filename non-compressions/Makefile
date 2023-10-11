.PHONY = all clean

DIR = ../
CC = g++
all: golay.o fourier.o equivalence.o orderly_equivalence.o array.o generate_classes generate_orderly filter_equivalent match_pairs

orderly_equivalence.o: $(DIR)orderly_equivalence.cpp $(DIR)golay.h $(DIR)coprimes.h
	$(CC) -Wall -g -c $(DIR)orderly_equivalence.cpp -o $(DIR)orderly_equivalence.o	

equivalence.o: $(DIR)equivalence.cpp $(DIR)golay.h $(DIR)coprimes.h
	$(CC) -Wall -g -c $(DIR)equivalence.cpp -o $(DIR)equivalence.o

array.o: $(DIR)array.cpp $(DIR)golay.h
	$(CC) -Wall -g -c $(DIR)array.cpp -o $(DIR)array.o

fourier.o: $(DIR)fourier.cpp $(DIR)golay.h
	$(CC) -Wall -Wextra -g -c $(DIR)fourier.cpp -o $(DIR)fourier.o -L../fftw-3.3.10/.libs -l:libfftw3.a

golay.o: $(DIR)golay.h
	$(CC) -Wall -g -c $(DIR)golay.cpp -o $(DIR)golay.o

match_pairs: match_pairs.cpp $(DIR)golay.h $(DIR)golay.o
	$(CC) -Wall -g match_pairs.cpp $(DIR)golay.o -o match_pairs

generate_classes: generate_classes.cpp $(DIR)golay.h $(DIR)array.o $(DIR)fourier.o $(DIR)equivalence.o
	$(CC) -Wall -g -O3 generate_classes.cpp $(DIR)equivalence.o $(DIR)array.o $(DIR)fourier.o -o generate_classes -fopenmp -L../fftw-3.3.10 -l:libfftw3.a -l:libfftw3_omp.a -lm

generate_orderly: generate_orderly.cpp $(DIR)golay.h $(DIR)array.o $(DIR)fourier.o $(DIR)orderly_equivalence.o
	$(CC) -Wall -g -O3 generate_orderly.cpp $(DIR)orderly_equivalence.o $(DIR)array.o $(DIR)fourier.o -o generate_orderly -fopenmp -L../fftw-3.3.10 -l:libfftw3.a -l:libfftw3_omp.a -lm



filter_equivalent: filter_equivalent.cpp $(DIR)golay.h $(DIR)equivalence.o
	$(CC) -Wall -g -O3 filter_equivalent.cpp $(DIR)equivalence.o -o filter_equivalent


clean:
	@echo "Cleaning up..."
	rm -f $(DIR)equivalence.o $(DIR)array.o $(DIR)fourier.o $(DIR)golay.o generate_classes generate_classesMPI filter_equivalent match_pairs