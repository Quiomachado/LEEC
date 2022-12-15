#include "gd.h"


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
gdImagePtr  add_watermark(gdImagePtr in_img, gdImagePtr watermark);


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
gdImagePtr  resize_image(gdImagePtr in_img ,int new_width);

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
gdImagePtr  make_thumb(gdImagePtr in_img, int size);

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
gdImagePtr read_png_file(char * file_name);

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
int write_png_file(gdImagePtr write_img, char * file_name);

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
int create_directory(char * dir_name);
