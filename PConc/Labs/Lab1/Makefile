CC = gcc
CFLAGS=-Wall -g

all: test

test: test.o
		$(CC) $(CFLAGS) -o test test.o

test.o: test.c
		$(CC) -c $(CFLAGS) test.c

clean::
		rm -f *.o core test *~

valgrind::
		valgrind --leak-check=full ./test

vlusiadas-words.txt::
		valgrind --leak-check=full ./test lusiadas-words.txt