CC=g++

all: calculator


calculator: main.o 
    $(CC) -o calculator main.o s

main.o: main.cpp
    $(CC) -c main.cpp


run:
	./test < input.txt

clean:
    rm -rf *.o calculator