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
#define THUMB_DIR "./Thumbnail-dir/"

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
	gdImagePtr in_img;
	/* output images */
	gdImagePtr out_thumb_img;

	if (create_directory(THUMB_DIR) == 0){
		fprintf(stderr, "Impossible to create %s directory\n", THUMB_DIR);
		exit(-1);
	}

	/* 2nd iteration over all the files 
	 * To create the thumbnails
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
		out_thumb_img = make_thumb(in_img, 150);
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
		gdImageDestroy(in_img);

	}
	
	exit(0);
}

