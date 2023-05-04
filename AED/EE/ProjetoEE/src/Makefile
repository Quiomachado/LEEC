CC = gcc
CFLAGS=-Wall -std=c99

backbone: main.o graf.o
		$(CC) $(CFLAGS) -o backbone main.o graf.o

main.o: main.c graf.h
		$(CC) -c $(CFLAGS) main.c

graf.o: graf.c graf.h
		$(CC) -c $(CFLAGS) graf.c

clean::
		rm -f *.o core a.out backbone *~

FILES = $(shell ls ../densos2/*.routes0)

VALG = valgrind --leak-check=full

t:
	for F in ${FILES}; do  ./backbone $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./backbone $${F} ; done;


tt:
	for F in ${FILES}; do  time ./backbone $${F} ; done;
