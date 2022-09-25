# AED, last modified abl 2019.02.28
#
# To compile prog:
#    make
# To run all tests:
#    make t
#
# NOTE:
# In case of trouble with the shell for loop, GNU Make has 'foreach':
#	$(foreach file,$(FILES),./labconn $(file);)
# https://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile
#----------------------------------------------------------------------


bin: *.c
	cc connectivity.c labconn.c -o labconn
	chmod +x labconn


FILES_1=1x/10.txt 1x/100.txt 1x/1000.txt 1x/10000.txt
FILES_A=abcde/a.txt abcde/b.txt abcde/c.txt abcde/d.txt abcde/e.txt
FILES_Z=$(shell ls zx/*)

FILES=${FILES_1} ${FILES_A} ${FILES_Z}

t:  t1 t2 t3 t4


t1:
	rm -f out1.txt
	for F in ${FILES}; do  ./labconn -1 $$F >> out1.txt; done;

t2:
	rm -f out2.txt
	for F in ${FILES}; do  ./labconn -2 $$F >> out2.txt; done;

t3:
	rm -f out3.txt
	for F in ${FILES}; do  ./labconn -3 $$F >> out3.txt; done;

t4:
	rm -f out4.txt
	for F in ${FILES}; do  ./labconn -4 $$F >> out4.txt; done;
