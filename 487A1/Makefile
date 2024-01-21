CXX = g++

objects = main.o complex.o

all: complexcalc

complexcalc: $(objects)
	g++ -o complexcalc $(objects)

complex.o: complex.c complex.h
	g++ -c complex.c

main.o: main.c complex.h
	g++ -c main.c

clean:
    rm *.o $(objects)