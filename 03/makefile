CC=g++

all: test

test: test.o TokenParser.o
	$(CC) -o test test.o TokenParser.o
	./test

TokenParser.o: TokenParser.cpp
	$(CC) -c TokenParser.cpp

test.o: test.cpp TokenParser.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
