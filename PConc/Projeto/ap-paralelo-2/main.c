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
    char img_list[40][100];
    char img_name[40][100];
    gdImagePtr watermark_img;
    int n_img;
} imgs;

void *watermark_function(void *arg)
{
    imgs *input = (imgs *)arg;
    char out_file_name[100];
    gdImagePtr in_img;
    gdImagePtr out_watermark_img;

    for (int i = 0; i < input->n_img; i++)
    {
        printf("watermark  %s\n", input->img_list[i]);

        sprintf(out_file_name, "%s%s", WATER_DIR, input->img_name[i]);
        if (access(out_file_name, F_OK) != -1)
            continue;

        /* load of the input file */
        in_img = read_png_file(input->img_list[i]);
        if (in_img == NULL)
        {
            fprintf(stderr, "Impossible to read %s image\n", input->img_list[i]);
            continue;
        }

        /* add watermark */
        out_watermark_img = add_watermark(in_img, input->watermark_img);
        if (out_watermark_img == NULL)
        {
            fprintf(stderr, "Impossible to creat thumbnail of %s image\n", input->img_list[i]);
        }
        else
        {
            /* save watermark */
            if (write_png_file(out_watermark_img, out_file_name) == 0)
            {
                fprintf(stderr, "Impossible to write %s image\n", out_file_name);
            }
            gdImageDestroy(out_watermark_img);
        }
        gdImageDestroy(in_img);
    }
    return (void *)NULL;
}

void *resize_function(void *arg)
{
    imgs *input = (imgs *)arg;
    char out_file_name[100];
    gdImagePtr in_img;
    gdImagePtr out_resized_img, out_watermark_img;

    for (int i = 0; i < input->n_img; i++)
    {
        printf("resize  %s\n", input->img_list[i]);
        sprintf(out_file_name, "%s%s", RESIZE_DIR, input->img_name[i]);
        if (access(out_file_name, F_OK) != -1)
            continue;

        /* load of the input file */
        in_img = read_png_file(input->img_list[i]);
        if (in_img == NULL)
        {
            fprintf(stderr, "Impossible to read %s image\n", input->img_list[i]);
            continue;
        }

        /* add watermark */
        out_watermark_img = add_watermark(in_img, input->watermark_img);
        if (out_watermark_img == NULL)
        {
            fprintf(stderr, "Impossible to creat thumbnail of %s image\n", input->img_list[i]);
        }
        else
        {
            out_resized_img = resize_image(out_watermark_img, 800);
            if (out_resized_img == NULL)
            {
                fprintf(stderr, "Impossible to resize %s image\n", input->img_list[i]);
            }
            else
            {
                /* save resized */
                if (write_png_file(out_resized_img, out_file_name) == 0)
                {
                    fprintf(stderr, "Impossible to write %s image\n", out_file_name);
                }
                gdImageDestroy(out_resized_img);
            }
            gdImageDestroy(out_watermark_img);
        }
        gdImageDestroy(in_img);
    }
    return (void *)NULL;
}

void *thumbnail_function(void *arg)
{
    imgs *input = (imgs *)arg;
    char out_file_name[100];
    gdImagePtr in_img;
    gdImagePtr out_thumb_img, out_watermark_img;

    for (int i = 0; i < input->n_img; i++)
    {
        printf("thumbnail  %s\n", input->img_list[i]);
        sprintf(out_file_name, "%s%s", THUMB_DIR, input->img_name[i]);
        if (access(out_file_name, F_OK) != -1)
            continue;

        /* load of the input file */
        in_img = read_png_file(input->img_list[i]);
        if (in_img == NULL)
        {
            fprintf(stderr, "Impossible to read %s image\n", input->img_list[i]);
            continue;
        }

        /* add watermark */
        out_watermark_img = add_watermark(in_img, input->watermark_img);
        if (out_watermark_img == NULL)
        {
            fprintf(stderr, "Impossible to creat thumbnail of %s image\n", input->img_list[i]);
        }
        else
        {
            out_thumb_img = make_thumb(out_watermark_img, 150);
            if (out_thumb_img == NULL)
            {
                fprintf(stderr, "Impossible to creat thumbnail of %s image\n", input->img_list[i]);
            }
            else
            {
                /* save thumbnail image */
                if (write_png_file(out_thumb_img, out_file_name) == 0)
                {
                    fprintf(stderr, "Impossible to write %s image\n", out_file_name);
                }
                gdImageDestroy(out_thumb_img);
            }
            gdImageDestroy(out_watermark_img);
        }
        gdImageDestroy(in_img);
    }
    return (void *)NULL;
}

int main(int argc, char **argv)
{
    char *img_dir_path = NULL;
    char dir_extra[] = "./";
    int n_img = 0;
    char img_file_path[] = "image-list.txt";
    FILE *img_file = NULL;
    int n_threads = 3;
    char img_list[40][100];
    char img_name[40][100];
    char buffer[100];
    pthread_t thread_ids[3];
    imgs *input;
    if (argc != 2)
    {
        printf("Wrong Number of arguments.\n");
        printf("./ap-paralelo-2 img_dir\n");
        exit(1);
    }

    img_dir_path = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 4));
    strcpy(img_dir_path, dir_extra);
    strcat(img_dir_path, argv[1]);
    strcat(img_dir_path, "/");

    img_file = fopen(img_file_path, "r");
    if (img_file == NULL)
    {
        printf("File %s not found.\n", img_file_path);
        exit(1);
    }
    while (fscanf(img_file, "%s", buffer) == 1)
    {
        strcpy(img_name[n_img], buffer);
        strcpy(img_list[n_img], img_dir_path);
        strcat(img_list[n_img], buffer);
        n_img++;
    }

    if (create_directory(RESIZE_DIR) == 0)
    {
        fprintf(stderr, "Impossible to create %s directory\n", RESIZE_DIR);
        exit(-1);
    }
    if (create_directory(THUMB_DIR) == 0)
    {
        fprintf(stderr, "Impossible to create %s directory\n", THUMB_DIR);
        exit(-1);
    }
    if (create_directory(WATER_DIR) == 0)
    {
        fprintf(stderr, "Impossible to create %s directory\n", WATER_DIR);
        exit(-1);
    }

    input = (imgs *)malloc(sizeof(imgs));
    input->n_img = n_img;
    input->watermark_img = read_png_file(WATERMARK);
    for (int i = 0; i < n_img; i++)
    {
        strcpy(input->img_list[i], img_list[i]);
        strcpy(input->img_name[i], img_name[i]);
    }

    pthread_create(&thread_ids[0], NULL, watermark_function, input);
    pthread_create(&thread_ids[1], NULL, resize_function, input);
    pthread_create(&thread_ids[2], NULL, thumbnail_function, input);

    for (int i = 0; i < n_threads; i++)
    {
        pthread_join(thread_ids[i], NULL);
    }

    free(img_dir_path);
    gdImageDestroy(input->watermark_img);
    free(input);
    fclose(img_file);
    return 0;
}
