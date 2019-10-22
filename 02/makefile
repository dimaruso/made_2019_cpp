CC=g++
  
all: Myallocator


Myallocator: main.o 
    $(CC) -o Myallocator main.o

main.o: main.cpp
    $(CC) -c main.cpp

test: main.o
	$(CC) -o Myallocator main.o
	python pythonTest.py


clean:
    rm -rf *.o Myallocator
