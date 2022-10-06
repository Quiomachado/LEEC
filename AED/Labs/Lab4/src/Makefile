#
#  File name: makefile
#
#  Author: 2022 Fall Semester P1 AED Team
#
#  Release date: 2022/10/05
#
#  Description: Makefile for LAI P3
#
#  Usage:
#        To generate the executable file for the program p3-pub, run
#         $ make p3
#
#        To clean all object files and the executable file, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall

#  Sources
SOURCES =  SpMat.c p3.c

#  Objects
OBJECTS = SpMat.o p3.o

p3: $(OBJECTS)
	gcc $(CFLAGS) -o $@ $(OBJECTS)

SpMat.o: SpMat.h SpMat.c

clean::
	rm -f *.o core a.out p3 *~

depend::
	makedepend $(SOURCES)

# DO NOT DELETE
