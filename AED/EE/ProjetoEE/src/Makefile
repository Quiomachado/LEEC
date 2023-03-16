CC = gcc
CFLAGS=-Wall -std=c99 -g

backbone: main.o graf.o
		$(CC) $(CFLAGS) -o backbone main.o graf.o

main.o: main.c graf.h
		$(CC) -c $(CFLAGS) main.c

graf.o: graf.c graf.h
		$(CC) -c $(CFLAGS) graf.c

clean::
		rm -f *.o core a.out backbone *~