CC=g++

all: test

test: test.o ThreadPool.o
	$(CC) -o test test.o ThreadPool.o
	./test

ThreadPool.o: ThreadPool.cpp
	$(CC) -c ThreadPool.cpp

test.o: test.cpp ThreadPool.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
