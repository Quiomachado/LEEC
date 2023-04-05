CFLAGS = -Wall -std=c99 -O3
Geenie: Input_File_Generator.o
	 gcc $(CFLAGS) -o Geenie Input_File_Generator.o
Input_File_Generator.o: Input_File_Generator.c
	 gcc $(CFLAGS) -c Input_File_Generator.c
clean:
	rm *.o Geenie
purge:
	rm *~