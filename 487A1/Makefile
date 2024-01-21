CC = g++
objects = main.o complex.o
executable = complexcalc

all: $(executable)

$(executable): $(objects)
	$(CC) -o $(executable) $(objects)

complex.o: complex.c complex.h
	$(CC) -c complex.c

main.o: main.c complex.h
	$(CC) -c main.c

clean:
	rm -f $(objects) $(executable)