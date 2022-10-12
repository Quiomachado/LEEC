CC = gcc
CFLAGS=-Wall -std=c99 -g -pg

wrdmttns: main.o dicionario.o
		$(CC) $(CFLAGS) -o wrdmttns main.o dicionario.o

main.o: main.c dicionario.h
		$(CC) -c $(CFLAGS) main.c

dicionario.o: dicionario.c dicionario.h
		$(CC) -c $(CFLAGS) dicionario.c

clean::
		rm -f *.o core a.out wrdmttns *~