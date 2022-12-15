#include "image-lib.h"
#include <sys/stat.h>
#include <dirent.h>

/******************************************************************************
 * add_watermark()
 *
 * Arguments: in - pointer to image
 *            watermark - pointer to image watermark
 * Returns: out - pointer to image with watermark, or NULL in case of failure
 * Side-Effects: none
 *
 * Description: creates clone of image and puts a watermark on it
 *
 *****************************************************************************/
gdImagePtr  add_watermark(gdImagePtr in_img, gdImagePtr watermark){
	
	gdImagePtr out_img;

	int width,heigth;

	width = watermark->sx;
	heigth = watermark->sy;

	out_img =  gdImageClone (in_img);

	gdImageCopy(out_img, watermark, 0, 0, 0, 0, width, heigth);

	return(out_img);		
} 

/******************************************************************************
 * resize_image()
 *
 * Arguments: in - pointer to image
 *            new_width - new width to use in resizing
 * Returns: out - pointer to resized image, or NULL in case of failure
 * Side-Effects: none
 *
 * Description: creates clone of image with width and height scaled to target
 *              width
 *
 *****************************************************************************/
gdImagePtr  resize_image(gdImagePtr in_img ,int new_width){
	
	gdImagePtr out_img;
	int width,heigth;
	
	// Get the image's width and height
	
	width = in_img->sx;
	heigth = in_img->sy;
	int new_heigth = (int) new_width *1.0/width * heigth;
		

	gdImageSetInterpolationMethod(in_img, GD_BILINEAR_FIXED);
    out_img = gdImageScale(in_img, new_width, new_heigth);
	if (!out_img) {
		return NULL;
	}

	return(out_img);		
} 

/******************************************************************************
 * make_thumb()
 *
 * Arguments: in - pointer to image
 *            size - target size for thumbnail
 * Returns: out - pointer to thumbnail image, or NULL in case of failure
 * Side-Effects: none
 *
 * Description: thumbnail of image with smalles dimension equal to target size
 *
 *****************************************************************************/
gdImagePtr  make_thumb(gdImagePtr in_img, int size){
	
	gdImagePtr out_img, aux_img;


	int width,heigth;
	int new_heigth, new_width;
	// Get the image's width and height

	width = in_img->sx;
	heigth = in_img->sy;

	if (heigth > width){
		new_width = size;
		new_heigth = (int) new_width *1.0/width * heigth;
	}else{
		new_heigth = size;
		new_width = (int) new_heigth * 1.0 / heigth * width;
	}
		

	gdImageSetInterpolationMethod(in_img, GD_BILINEAR_FIXED);
    aux_img = gdImageScale(in_img, new_width, new_heigth);
	if (!aux_img) {
		return NULL;
    }


	gdRect crop_area;
	crop_area.height = size;
	crop_area.width = size;
	crop_area.x = 0;
	crop_area.y = 0;

	out_img = gdImageCrop(aux_img, & crop_area);
	gdImageDestroy(aux_img);

	if (!out_img) {
		return NULL;
    }

	return(out_img);		
} 

/******************************************************************************
 * read_png_file()
 *
 * Arguments: file_name - name of file with data for PNG image
 * Returns: img - the image read from file or NULL if failure to read
 * Side-Effects: none
 *
 * Description: reads a PNG image from a file
 *
 *****************************************************************************/
gdImagePtr read_png_file(char * file_name){

	FILE * fp;
	gdImagePtr read_img;

	fp = fopen(file_name, "rb");
   	if (!fp) {
        fprintf(stderr, "Can't read image %s\n", file_name);
        return NULL;
    }
    read_img = gdImageCreateFromPng(fp);
    fclose(fp);
  	if (read_img == NULL) {
    	return NULL;
    }

	return read_img;
}

/******************************************************************************
 * write_png_file()
 *
 * Arguments: img - pointer to image to be written
 *            file_name - name of file where to save PNG image
 * Returns: (bool) 1 in case of success, 0 in case of failure to write
 * Side-Effects: none
 *
 * Description: writes a PNG image to a file
 *
 *****************************************************************************/
int write_png_file(gdImagePtr write_img, char * file_name){
	FILE * fp;

	fp = fopen(file_name, "wb");
	if (fp == NULL) {
		return 0;
	}
	gdImagePng(write_img, fp);
	fclose(fp);

	return 1;
}

/******************************************************************************
 * create_directory()
 *
 * Arguments: file_name - name of directory to be created
 * Returns: (bool) 1 if the directory already exists or succesfully created
 *                 0 in case of failure to create
 * Side-Effects: none
 *
 * Description: Create a directory. 
 *
 *****************************************************************************/
int create_directory(char * dir_name){

	DIR * d = opendir(dir_name);
	if (d == NULL){
		if (mkdir(dir_name, 0777)!=0){
			return 0;
		}
	}else{
		fprintf(stderr, "%s directory already existent\n", dir_name);
		closedir(d);
	}
	return 1;
}
