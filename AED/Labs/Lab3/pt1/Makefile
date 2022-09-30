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


bin: *.c
	cc palTab.c -o palTab
	chmod +x palTab


FILES = $(shell ls ../test/*.txt)

VALG = valgrind --leak-check=full

t:
	for F in ${FILES}; do  ./palTab $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./palTab $${F} ; done;


tt:
	for F in ${FILES}; do  time ./palTab $${F} ; done;
