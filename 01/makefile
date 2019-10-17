CC=g++
  
all: calculator


calculator: main.o 
    $(CC) -o calculator main.o

main.o: main.cpp
    $(CC) -c main.cpp

test: main.o
	$(CC) -o calculator main.o
	python pythonTest.py
run: main.o
	$(CC) -o calculator main.o
	./calculator

clean:
    rm -rf *.o calculator