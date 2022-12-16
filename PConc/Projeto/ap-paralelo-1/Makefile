CC = gcc
CFLAGS=-Wall -g -lpthread -lgd

all: main

main: image-lib.o main.o
		$(CC) -o ap-paralelo-1 main.o image-lib.o $(CFLAGS)

image-lib.o: image-lib.c image-lib.h
		$(CC) -c image-lib.c $(CFLAGS)

main.o: main.c image-lib.h
		$(CC) -c main.c $(CFLAGS)

clean::
		rm -f *.o core ap-paralelo-1 *~