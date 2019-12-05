CC=g++

all: test

test: test.o MyVector.o
	$(CC) -o test test.o MyVector.o
	./test

MyVector.o: MyVector.cpp
	$(CC) -c MyVector.cpp

test.o: test.cpp MyVector.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
