.PHONY = all clean

DIR = ../
CC = g++
all: $(DIR)fourier.o $(DIR)equivalence.o $(DIR)array.o compressions_a compressions_b

equivalence.o: $(DIR)equivalence.cpp $(DIR)golay.h $(DIR)coprimes.h
	$(CC) -Wall -g -c $(DIR)equivalence.cpp -o $(DIR)equivalence.o

array.o: $(DIR)array.cpp $(DIR)golay.h
	$(CC) -Wall -g -c $(DIR)array.cpp -o $(DIR)array.o

fourier.o: $(DIR)fourier.cpp $(DIR)golay.h
	$(CC) -Wall -Wextra -g -c $(DIR)fourier.cpp -o $(DIR)fourier.o -L../fftw-3.3.5-dll64 -llibfftw3-3

compressions_a: compressions_a.cpp $(DIR)golay.h $(DIR)array.o $(DIR)fourier.o $(DIR)equivalence.o
	$(CC) -Wall -g compressions_a.cpp $(DIR)equivalence.o $(DIR)array.o $(DIR)fourier.o -o compressions_a -L../fftw-3.3.5-dll64 -llibfftw3-3

compressions_b: compressions_b.cpp $(DIR)golay.h $(DIR)array.o $(DIR)fourier.o $(DIR)equivalence.o
	$(CC) -Wall -g compressions_b.cpp $(DIR)equivalence.o $(DIR)array.o $(DIR)fourier.o -o compressions_b -L../fftw-3.3.5-dll64 -llibfftw3-3


clean:
	@echo "Cleaning up..."
	rm -f equivalence.o array.o fourier.o compressions_a compressions_b