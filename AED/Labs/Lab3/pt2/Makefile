# AED, last modified abl 2019.03.01
#
# To compile prog:
#    make
# To run tests:
#    make t
#
# NOTE:
# In case of trouble with the shell for loop, GNU Make has 'foreach':
#	$(foreach file,$(FILES),./labconn $(file);)
# https://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile
#----------------------------------------------------------------------

CC=gcc
CFLAGS=-g -Wall -ansi -pedantic

newWords: main.o list.o words.o
	$(CC) $(CFLAGS) -o newWords main.o list.o words.o

main.o: main.c list.h words.h
	$(CC) -c $(CFLAGS) main.c

list.o: list.c list.h
	$(CC) -c $(CFLAGS) list.c

words.o: words.c words.h  list.h
	$(CC) -c $(CFLAGS) words.c

clean::
	rm -f *.o core a.out newWords *~



FILES = $(shell ls ../test/*.txt)

VALG = valgrind --leak-check=full

t:
	for F in ${FILES}; do  ./newWords $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./newWords $${F} ; done;


tt:
	for F in ${FILES}; do  time ./newWords $${F} ; done;
