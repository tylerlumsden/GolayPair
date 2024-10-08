.PHONY = all clean

DIR = lib/
BIN = bin/
SRC = src/
CC = g++
FFTW = -I/usr/local/include -L/usr/local/lib -lfftw3 -lm
all: bin/binary.o bin/golay.o bin/fourier.o bin/orderly_equivalence.o bin/equivalence.o bin/array.o bin/generate_hybrid bin/cache_filter bin/canon_filter bin/match_pairs bin/uncompression bin/compress

$(BIN)orderly_equivalence.o: $(DIR)orderly_equivalence.cpp $(DIR)golay.h $(DIR)coprimes.h
	$(CC) -Wall -g -c -O3 $(DIR)orderly_equivalence.cpp -o $(BIN)orderly_equivalence.o 

$(BIN)binary.o: $(DIR)binary.cpp $(DIR)binary.h
	$(CC) -Wall -g -c -O3 $(DIR)binary.cpp -o $(BIN)binary.o

$(BIN)array.o: $(DIR)array.cpp $(DIR)golay.h
	$(CC) -Wall -g -c $(DIR)array.cpp -o $(BIN)array.o

$(BIN)fourier.o: $(DIR)fourier.cpp $(DIR)golay.h
	$(CC) -Wall -Wextra -O3 -g -c $(DIR)fourier.cpp -o $(BIN)fourier.o $(FFTW)

$(BIN)golay.o: $(DIR)golay.h
	$(CC) -Wall -g -O3 -c $(DIR)golay.cpp -o $(BIN)golay.o

$(BIN)match_pairs: $(SRC)match_pairs.cpp $(DIR)golay.h $(BIN)golay.o $(BIN)binary.o
	$(CC) -Wall -g -O3 $(SRC)match_pairs.cpp $(BIN)golay.o $(BIN)binary.o -o $(BIN)match_pairs 

$(BIN)generate_hybrid: $(SRC)generate_hybrid.cpp $(BIN)golay.o $(BIN)array.o $(BIN)fourier.o $(BIN)orderly_equivalence.o $(BIN)binary.o
	$(CC) -Wall -g -O3 $(SRC)generate_hybrid.cpp $(BIN)orderly_equivalence.o $(BIN)array.o $(BIN)fourier.o $(BIN)golay.o $(BIN)binary.o -o $(BIN)generate_hybrid $(FFTW)

$(BIN)cache_filter: $(SRC)cache_filter.cpp $(DIR)golay.h $(BIN)equivalence.o
	$(CC) -Wall -g -O3 $(SRC)cache_filter.cpp $(BIN)equivalence.o -o $(BIN)cache_filter

$(BIN)canon_filter: $(SRC)canon_filter.cpp $(DIR)golay.h $(BIN)equivalence.o
	$(CC) -Wall -g -O3 $(SRC)canon_filter.cpp $(BIN)equivalence.o -o $(BIN)canon_filter

$(BIN)equivalence.o: $(DIR)equivalence.cpp $(DIR)golay.h $(DIR)coprimes.h
	$(CC) -Wall -g -O3 -c $(DIR)equivalence.cpp -o $(BIN)equivalence.o 

$(BIN)uncompression: $(SRC)uncompression.cpp $(BIN)array.o $(BIN)equivalence.o $(BIN)binary.o
	$(CC) -Wall -g -O3 $(SRC)uncompression.cpp $(BIN)equivalence.o $(BIN)fourier.o $(BIN)array.o $(BIN)binary.o -o $(BIN)uncompression $(FFTW)

$(BIN)compress: $(SRC)compress.cpp $(BIN)fourier.o
	$(CC) -Wall -g -O3 $(SRC)compress.cpp $(BIN)fourier.o -o $(BIN)compress $(FFTW)
clean:
	@echo "Cleaning up..."
	rm -f bin/*