CC = gcc
CFLAGS=-Wall -std=c99 -g

wrdmttns: main.o dicionario.o LinkedList.o queue.o
		$(CC) $(CFLAGS) -o wrdmttns main.o dicionario.o LinkedList.o queue.o

main.o: main.c dicionario.h
		$(CC) -c $(CFLAGS) main.c

dicionario.o: dicionario.c dicionario.h
		$(CC) -c $(CFLAGS) dicionario.c

LinkedList.o: LinkedList.c LinkedList.h defs.h
		$(CC) -c $(CFLAGS) LinkedList.c

queue.o: queue.c queue.h defs.h
		$(CC) -c $(CFLAGS) queue.c

clean::
		rm -f *.o core a.out wrdmttns *~