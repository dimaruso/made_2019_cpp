CC=g++

all: test

test: test.o Formatter.o
	$(CC) -o test test.o Formatter.o
	./test

Formatter.o: Formatter.cpp
	$(CC) -c Formatter.cpp

test.o: test.cpp Formatter.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
