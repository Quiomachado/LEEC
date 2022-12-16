#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "image-lib.h"
char WATERMARK[] = "watermark.png";

#define RESIZE_DIR "./Resize-dir/"
#define THUMB_DIR "./Thumbnail-dir/"
#define WATER_DIR "./Watermark-dir/"

typedef struct imgs
{
    gdImagePtr *in_img;
    gdImagePtr watermark_img;
} imgs;

int main(int argc, char **argv)
{
    char *img_dir_path = NULL;
    char dir_extra[] = "./";
    int n_threads = 0;
    int n_img = 0;
    char img_file_path[] = "image-list.txt";
    FILE *img_file = NULL;
    char img_list[40][100];
    char buffer[100];
    imgs **inputs = {NULL};
    int *n_img_thread = NULL;
    int img_counter = 0;

    if (argc != 3)
    {
        printf("Wrong Number of arguments.\n");
        printf("./ap-paralelo-1 img_dir number_of_threads\n");
        exit(1);
    }

    img_dir_path = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 4));
    strcpy(img_dir_path, dir_extra);
    strcat(img_dir_path, argv[1]);
    strcat(img_dir_path, "/");

    n_threads = argv[2];

    inputs = (imgs **)malloc(sizeof(imgs *) * n_threads);

    img_file = fopen(img_file_path, "r");
    if (img_file == NULL)
    {
        printf("File %s not found.\n", img_file_path);
        exit(1);
    }
    while (fscanf(img_file, "%s", buffer) == 1)
    {
        strcpy(img_list[n_img], img_dir_path);
        strcat(img_list[n_img], buffer);
        n_img++;
    }

    n_img_thread = (int *)malloc(sizeof(int) * n_threads);
    if (n_img_thread == NULL)
        exit(1);

    for (int i = 0; i < n_threads; i++)
        n_img_thread[i] = n_threads / n_img;
    for (int i = n_threads % n_img - 1; i >= 0; i--)
        n_img_thread[i] += 1;

    for (int i = 0; i < n_threads; i++)
    {
        inputs[i]->watermark_img = read_png_file(WATERMARK);
        inputs[i]->in_img = (gdImagePtr *)malloc(sizeof(n_img_thread[i]));
        for (int k = 0; k < n_img_thread[i]; k++)
        {
            inputs[i]->in_img[k] = read_png_file(img_list[img_counter]);
            img_counter++;
        }
    }

    

    free(img_dir_path);
    for (int i = 0; i < n_threads; i++)
    {
        gdImageDestroy(inputs[i]->watermark_img);
        for (int k = 0; k < n_img_thread[i]; k++)
            gdImageDestroy(inputs[i]->in_img[k]);
        free(inputs[i]->in_img);
        free(inputs[i]);
    }
    free(inputs);
    free(n_img_thread);
    return 0;
}