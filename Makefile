.PHONY = all clean

DIR = lib/
BIN = bin/
SRC = src/
CC = g++
FFTW = -I/usr/local/include -L/usr/local/lib -lfftw3 -lm
all: bin/golay.o bin/fourier.o bin/orderly_equivalence.o bin/equivalence.o bin/array.o bin/generate_orderly bin/filter_equivalent bin/match_pairs bin/uncompression bin/compress

$(BIN)orderly_equivalence.o: $(DIR)orderly_equivalence.cpp $(DIR)golay.h $(DIR)coprimes.h
	$(CC) -Wall -g -c -O3 $(DIR)orderly_equivalence.cpp -o $(BIN)orderly_equivalence.o 

$(BIN)array.o: $(DIR)array.cpp $(DIR)golay.h
	$(CC) -Wall -g -c $(DIR)array.cpp -o $(BIN)array.o

$(BIN)fourier.o: $(DIR)fourier.cpp $(DIR)golay.h
	$(CC) -Wall -Wextra -O3 -g -c $(DIR)fourier.cpp -o $(BIN)fourier.o $(FFTW)

$(BIN)golay.o: $(DIR)golay.h
	$(CC) -Wall -g -c $(DIR)golay.cpp -o $(BIN)golay.o

$(BIN)match_pairs: $(SRC)match_pairs.cpp $(DIR)golay.h $(BIN)golay.o
	$(CC) -Wall -g -O3 $(SRC)match_pairs.cpp $(BIN)golay.o -o $(BIN)match_pairs 

$(BIN)generate_orderly: $(SRC)generate_orderly.cpp $(DIR)golay.h $(BIN)array.o $(BIN)fourier.o $(BIN)orderly_equivalence.o
	$(CC) -Wall -g -O3 $(SRC)generate_orderly.cpp $(BIN)orderly_equivalence.o $(BIN)array.o $(BIN)fourier.o -o $(BIN)generate_orderly $(FFTW)

$(BIN)filter_equivalent: $(SRC)filter_equivalent.cpp $(DIR)golay.h $(BIN)equivalence.o
	$(CC) -Wall -g -O3 $(SRC)filter_equivalent.cpp $(BIN)equivalence.o -o $(BIN)filter_equivalent 

$(BIN)equivalence.o: $(DIR)equivalence.cpp $(DIR)golay.h $(DIR)coprimes.h
	$(CC) -Wall -g -O3 -c $(DIR)equivalence.cpp -o $(BIN)equivalence.o 

$(BIN)uncompression: $(SRC)uncompression.cpp $(BIN)array.o $(BIN)equivalence.o 
	$(CC) -Wall -g -O3 $(SRC)uncompression.cpp $(BIN)equivalence.o $(BIN)fourier.o $(BIN)array.o -o $(BIN)uncompression $(FFTW)

$(BIN)compress: $(SRC)compress.cpp
	$(CC) -Wall -g -O3 $(SRC)compress.cpp -o $(BIN)compress
clean:
	@echo "Cleaning up..."
	rm -f bin/*