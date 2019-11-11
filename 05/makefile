CC=g++

all: test

test: test.o MySerializer.o
	$(CC) -o test test.o MySerializer.o
	./test

MySerializer.o: MySerializer.cpp
	$(CC) -c MySerializer.cpp

test.o: test.cpp MySerializer.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
