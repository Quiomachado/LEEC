all: serial-basic


serial-basic: serial-basic.c image-lib.c image-lib.h
	gcc -Wall -pedantic serial-basic.c image-lib.c -g -o serial-basic -lgd

clean:
	rm serial-basic

clean-data:
	rm -fry ./Resize-dir ./Thumbnail-dir ./Watermark-dir
