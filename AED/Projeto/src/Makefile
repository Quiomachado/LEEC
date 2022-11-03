CC = gcc
CFLAGS=-Wall -std=c99 -g -pg

wrdmttns: wrdmttns.o dicionario.o LinkedList.o queue.o
		$(CC) $(CFLAGS) -o wrdmttns wrdmttns.o dicionario.o LinkedList.o queue.o

wrdmttns.o: wrdmttns.c dicionario.h
		$(CC) -c $(CFLAGS) wrdmttns.c

dicionario.o: dicionario.c dicionario.h
		$(CC) -c $(CFLAGS) dicionario.c

LinkedList.o: LinkedList.c LinkedList.h defs.h
		$(CC) -c $(CFLAGS) LinkedList.c

queue.o: queue.c queue.h defs.h
		$(CC) -c $(CFLAGS) queue.c

clean::
		rm -f *.o core a.out wrdmttns *~