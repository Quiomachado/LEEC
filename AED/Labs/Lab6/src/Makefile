# AED 2022-2023
# Makefile for Lab6 graphs
# Last edit: lms 2022.10.20
#-----------------------------------------------------------------------
#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

#   Sources
SOURCES = ev2el.c LinkedList.c queue.c

#   Objects  ('Make' automatically compiles .c to .o)
OBJECTS = ev2el.o LinkedList.o queue.o

all: ev2el

ev2el: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

LinkedList.o: LinkedList.h defs.h LinkedList.c

queue.o: queue.h defs.h queue.c

clean::
	rm -f *.o core a.out ev2el  *~

t:
	./ev2el ../tests/grafo11.edge > grafo11.ladj
	./ev2el ../tests/grafo4.edge  > grafo4.ladj
	./ev2el ../tests/grafo5.edge  > grafo5.ladj
	./ev2el ../tests/grafo6.edge  > grafo6.ladj
