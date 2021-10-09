CC=g++
CFLAGS=-I. -std=c++11 -g -Wall -pthread
DEPS = mundo.hpp taxi.hpp
OBJ = mundo.o taxi.o main.o 
SHELL:=/bin/bash -O extglob

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f -r *.o main