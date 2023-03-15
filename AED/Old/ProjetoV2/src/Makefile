CC = gcc
CFLAGS=-Wall -std=c99 -g

wrdmttns: main.o dicionario.o LinkedList.o
		$(CC) $(CFLAGS) -o wrdmttns main.o dicionario.o LinkedList.o

main.o: main.c dicionario.h
		$(CC) -c $(CFLAGS) main.c

dicionario.o: dicionario.c dicionario.h
		$(CC) -c $(CFLAGS) dicionario.c

LinkedList.o: LinkedList.c LinkedList.h defs.h
		$(CC) -c $(CFLAGS) LinkedList.c

clean::
		rm -f *.o core a.out wrdmttns *~