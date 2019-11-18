CC=g++

all: test

test: test.o MyBigInt.o
	$(CC) -o test test.o MyBigInt.o
	./test

MyBigInt.o: MyBigInt.cpp
	$(CC) -c MyBigInt.cpp

test.o: test.cpp MyBigInt.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
