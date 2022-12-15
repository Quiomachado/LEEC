CC = gcc
CFLAGS=-Wall -g -lpthread -lgd

all: main

main: main.o
		$(CC) $(CFLAGS) -o main main.o

main.o:
		$(CC) -c $(CFLAGS) main.c

clean::
		rm -f *.o core main *~