all: generate-watermark generate-resize generate-thumbnail 

generate-watermark: generate-watermark.c image-lib.c image-lib.h
	gcc -Wall -pedantic generate-watermark.c image-lib.c -g -o generate-watermark -lgd

generate-resize: generate-resize.c image-lib.c image-lib.h
	gcc -Wall -pedantic generate-resize.c image-lib.c -g -o generate-resize -lgd

generate-thumbnail: generate-thumbnail.c image-lib.c image-lib.h
	gcc -Wall -pedantic generate-thumbnail.c image-lib.c -g -o generate-thumbnail -lgd

clean:
	rm generate-watermark generate-resize generate-thumbnail

clean-data:
	rm -fry ./Resize-dir ./Thumbnail-dir ./Watermark-dir
