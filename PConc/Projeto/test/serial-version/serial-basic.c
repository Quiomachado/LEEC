/******************************************************************************
 * Programacao Concorrente
 * MEEC 21/22
 *
 * Projecto - Parte1
 *                           serial-complexo.c
 * 
 * Compilacao: gcc serial-complexo -o serial-complex -lgd
 *           
 *****************************************************************************/

#include "gd.h"
#include "image-lib.h"

/* the directories wher output files will be placed */
#define RESIZE_DIR "./serial-Resize/"
#define THUMB_DIR "./serial-Thumbnail/"
#define WATER_DIR "./serial-Watermark/"


/******************************************************************************
 * main()
 *
 * Arguments: (none)
 * Returns: 0 in case of sucess, positive number in case of failure
 * Side-Effects: creates thumbnail, resized copy and watermarked copies
 *               of images
 *
 * Description: implementation of the complex serial version 
 *              This application only works for a fixed pre-defined set of files
 *
 *****************************************************************************/
int main(){

	/* array containg the names of files to be processed	 */
	char * files [] =  {"Lisboa-1.png", "IST-1.png", "IST-2.png", "IST-3.png", "00841.png", "00844.png", "00846.png", "00849.png" }; 
	/* length of the files array (number of files to be processed	 */
	int nn_files = 8;

	/* file name of the image created and to be saved on disk	 */
	char out_file_name[100];

	/* input images */
	gdImagePtr in_img,  watermark_img;
	/* output images */
	gdImagePtr out_thumb_img, out_resized_img, out_watermark_img;

	/* creation of output directories */
	if (create_directory(RESIZE_DIR) == 0){
		fprintf(stderr, "Impossible to create %s directory\n", RESIZE_DIR);
		exit(-1);
	}
	if (create_directory(THUMB_DIR) == 0){
		fprintf(stderr, "Impossible to create %s directory\n", THUMB_DIR);
		exit(-1);
	}
	if (create_directory(WATER_DIR) == 0){
		fprintf(stderr, "Impossible to create %s directory\n", WATER_DIR);
		exit(-1);
	}

    watermark_img = read_png_file("watermark.png");
	if(watermark_img == NULL){
		fprintf(stderr, "Impossible to read %s image\n", "watermark.png");
		exit(-1);
	}


	/* 
	 * Add the watermarks
	 */
	for (int i = 0; i < nn_files; i++){	

	    printf("watermark  %s\n", files[i]);
		/* load of the input file */
	    in_img = read_png_file(files[i]);
		if (in_img == NULL){
			fprintf(stderr, "Impossible to read %s image\n", files[i]);
			continue;
		}

		/* add watermark */
		out_watermark_img = add_watermark(in_img, watermark_img);
  		if (out_watermark_img == NULL) {
            fprintf(stderr, "Impossible to creat thumbnail of %s image\n", files[i]);
        }else{
			/* save watermark */
			sprintf(out_file_name, "%s%s", WATER_DIR, files[i]);
			if(write_png_file(out_watermark_img, out_file_name) == 0){
	            fprintf(stderr, "Impossible to write %s image\n", out_file_name);
			}
			gdImageDestroy(out_watermark_img);
		}
		gdImageDestroy(in_img);

	}





	/* 
	 * To resize images and add watermark
	 */
	for (int i = 0; i < nn_files; i++){	

		printf("resize %s\n", files[i]);
		/* load of the input file */
	    in_img = read_png_file(files[i]);
		if (in_img == NULL){
			fprintf(stderr, "Impossible to read %s image\n", files[i]);
			continue;
		}
		/* resizes of each image */
		out_watermark_img = add_watermark(in_img, watermark_img);
		if (out_watermark_img == NULL) {
			fprintf(stderr, "Impossible to add watermark to %s image\n", files[i]);
		}else{
			out_resized_img = resize_image(out_watermark_img, 800);
			if (out_resized_img == NULL) {
				fprintf(stderr, "Impossible to resize %s image\n", files[i]);
			}else{
				/* save resized */
				sprintf(out_file_name, "%s%s", RESIZE_DIR, files[i]);
				if(write_png_file(out_resized_img, out_file_name) == 0){
					fprintf(stderr, "Impossible to write %s image\n", out_file_name);
				}
				gdImageDestroy(out_resized_img);
			}
			gdImageDestroy(out_watermark_img);
		}
		gdImageDestroy(in_img);
	}

	/* 
	 * Add watermark and create thumbnails
	 */
	for (int i = 0; i < nn_files; i++){	

	   	printf("thumbnail %s\n", files[i]);
		/* load of the input file */
	    in_img = read_png_file(files[i]);
		if (in_img == NULL){
			fprintf(stderr, "Impossible to read %s image\n", files[i]);
			continue;
		}

		/* creation of thumbnail image */
		out_watermark_img = add_watermark(in_img, watermark_img);
		if (out_watermark_img == NULL) {
			fprintf(stderr, "Impossible to creat thumbnail of %s image\n", files[i]);
		}else{
			out_thumb_img = make_thumb(out_watermark_img, 150);
			if (out_thumb_img == NULL) {
				fprintf(stderr, "Impossible to creat thumbnail of %s image\n", files[i]);
			}else{
				/* save thumbnail image */
				sprintf(out_file_name, "%s%s", THUMB_DIR, files[i]);
				if(write_png_file(out_thumb_img, out_file_name) == 0){
					fprintf(stderr, "Impossible to write %s image\n", out_file_name);
				}
				gdImageDestroy(out_thumb_img);
			}
			gdImageDestroy(out_watermark_img);
		}
		gdImageDestroy(in_img);

	}

	gdImageDestroy(watermark_img);
	exit(0);
}

