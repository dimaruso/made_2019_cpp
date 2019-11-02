CC=g++

all: test

test: test.o MyMatrix.o
	$(CC) -o test test.o MyMatrix.o
	./test

MyMatrix.o: MyMatrix.cpp
	$(CC) -c MyMatrix.cpp

test.o: test.cpp MyMatrix.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
