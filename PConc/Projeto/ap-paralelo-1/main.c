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
    int n_files;
} imgs;

void *thread_function(void *arg)
{
    imgs *input = (imgs *)arg;
    gdImagePtr watermark_img = input->watermark_img;
    gdImagePtr in_img;
    gdImagePtr out_thumb_img, out_resized_img, out_watermark_img;
    char out_file_name[100];

    for (int i = 0; i < input->n_files; i++)
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
        out_watermark_img = add_watermark(in_img, watermark_img);
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

    /*
     * To resize images and add watermark
     */
    for (int i = 0; i < input->n_files; i++)
    {
        printf("resizing  %s\n", input->img_list[i]);
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
        /* resizes of each image */
        out_watermark_img = add_watermark(in_img, watermark_img);
        if (out_watermark_img == NULL)
        {
            fprintf(stderr, "Impossible to add watermark to %s image\n", input->img_list[i]);
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

    /*
     * Add watermark and create thumbnails
     */
    for (int i = 0; i < input->n_files; i++)
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

        /* creation of thumbnail image */
        out_watermark_img = add_watermark(in_img, watermark_img);
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
    gdImageDestroy(input->watermark_img);
    free(input);
    return (void *)NULL;
}

int main(int argc, char **argv)
{
    char *img_dir_path = NULL;
    char dir_extra[] = "./";
    int n_threads = 0;
    int n_img = 0;
    char img_file_path[] = "image-list.txt";
    FILE *img_file = NULL;
    char img_list[40][100];
    char img_name[40][100];
    char buffer[100];
    imgs *inputs = NULL;
    int *n_img_thread = NULL;
    int img_counter = 0;
    pthread_t *thread_ids;

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

    n_threads = atoi(argv[2]);

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

    n_img_thread = (int *)calloc(1, sizeof(int) * n_threads);
    if (n_img_thread == NULL)
        exit(1);

    for (int i = 0; i < n_threads; i++)
        n_img_thread[i] = n_img / n_threads;
    for (int i = (n_img % n_threads) - 1; i >= 0; i--)
        n_img_thread[i] += 1;

    thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);

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

    for (int i = 0; i < n_threads; i++)
    {
        inputs = (imgs *)malloc(sizeof(imgs));
        inputs->watermark_img = read_png_file(WATERMARK);
        if (inputs->watermark_img == NULL)
        {
            fprintf(stderr, "Impossible to read %s file\n", WATERMARK);
            exit(-1);
        }
        inputs->n_files = n_img_thread[i];
        for (int k = 0; k < n_img_thread[i]; k++)
        {
            strcpy(inputs->img_list[k], img_list[img_counter]);
            strcpy(inputs->img_name[k], img_name[img_counter]);
            img_counter++;
        }
        pthread_create(&thread_ids[i], NULL, thread_function, inputs);
    }
    for (int i = 0; i < n_threads; i++)
    {
        pthread_join(thread_ids[i], NULL);
    }

    free(thread_ids);
    free(img_dir_path);
    free(n_img_thread);
    fclose(img_file);
    return 0;
}