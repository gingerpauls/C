all: main

main: main.o complex.o
	g++ -o main main.o complex.o

complex.o: complex.c complex.h
	g++ -c complex.c

main.o: main.c
	g++ -c main.c