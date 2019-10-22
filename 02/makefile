CC=g++

all: test

test: test.o Myallocator.o
	$(CC) -o test test.o Myallocator.o
	./test

Myallocator.o: Myallocator.cpp
	$(CC) -c Myallocator.cpp

test.o: test.cpp Myallocator.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o test