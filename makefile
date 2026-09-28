#modify this makefile so that it will work for this new assignment
CC = g++

all: a.out

a.out: main.cpp
	$(CC) -std=c++11 main.cpp -o a.out

clean:
	rm -f *.o *.out
