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
    char img[100];
    char img_name[100];
    int n_img;
} imgs;

int WM_pipe[2];
int R_pipe[2];
int TH_pipe[2];

void *watermark_function(void *arg)
{
    imgs *input = NULL;
    char out_file_name[1000];
    gdImagePtr in_img;
    gdImagePtr out_watermark_img;
    gdImagePtr watermark_img = read_png_file(WATERMARK);

    while (1)
    {
        read(WM_pipe[0], &input, sizeof(input));
        printf("%s read from WM_pipe\n", input->img_name);
        if (input->n_img == -10)
        {
            gdImageDestroy(watermark_img);
            write(R_pipe[1], &input, sizeof(input));
            return (void *)NULL;
        }

        sprintf(out_file_name, "%s%s", WATER_DIR, input->img_name);
        if (access(out_file_name, F_OK) != -1)
            continue;

        /* load of the input file */
        in_img = read_png_file(input->img);
        if (in_img == NULL)
        {
            fprintf(stderr, "Impossible to read %s image\n", input->img);
            continue;
        }

        /* add watermark */
        out_watermark_img = add_watermark(in_img, watermark_img);
        if (out_watermark_img == NULL)
        {
            fprintf(stderr, "Impossible to creat thumbnail of %s image\n", input->img);
        }
        else
        {
            /* save watermark */
            if (write_png_file(out_watermark_img, out_file_name) == 0)
            {
                fprintf(stderr, "Impossible to write %s image\n", out_file_name);
            }
            strcpy(input->img, out_file_name);
            write(R_pipe[1], &input, sizeof(input));
            printf("%s write to R_pipe\n", input->img_name);
            gdImageDestroy(out_watermark_img);
        }
        gdImageDestroy(in_img);
    }
    gdImageDestroy(watermark_img);
    return (void *)NULL;
}

void *resize_function(void *arg)
{
    imgs *input = NULL;
    char out_file_name[1000];
    gdImagePtr in_img;
    gdImagePtr out_resized_img;

    while (1)
    {
        read(R_pipe[0], &input, sizeof(input));
        printf("%s read from R_pipe\n", input->img_name);
        if (input->n_img == -10)
        {
            write(TH_pipe[1], &input, sizeof(input));
            return (void *)NULL;
        }

        sprintf(out_file_name, "%s%s", RESIZE_DIR, input->img_name);
        if (access(out_file_name, F_OK) != -1)
            continue;

        /* load of the input file */
        in_img = read_png_file(input->img);
        if (in_img == NULL)
        {
            fprintf(stderr, "Impossible to read %s image\n", input->img);
            continue;
        }
        out_resized_img = resize_image(in_img, 800);
        if (out_resized_img == NULL)
        {
            fprintf(stderr, "Impossible to resize %s image\n", input->img);
        }
        else
        {
            /* save resized */
            if (write_png_file(out_resized_img, out_file_name) == 0)
            {
                fprintf(stderr, "Impossible to write %s image\n", out_file_name);
            }
            strcpy(input->img, out_file_name);
            write(TH_pipe[1], &input, sizeof(input));
            printf("%s write to TH_pipe\n", input->img_name);
            gdImageDestroy(out_resized_img);
        }
        gdImageDestroy(in_img);
    }
    return (void *)NULL;
}

void *thumbnail_function(void *arg)
{
    imgs *input = NULL;
    char out_file_name[1000];
    gdImagePtr in_img;
    gdImagePtr out_thumb_img;

    while (1)
    {
        read(TH_pipe[0], &input, sizeof(input));
        printf("%s read from TH_pipe\n", input->img_name);
        if (input->n_img == -10)
        {
            return (void *)NULL;
        }

        sprintf(out_file_name, "%s%s", THUMB_DIR, input->img_name);
        if (access(out_file_name, F_OK) != -1)
            continue;

        /* load of the input file */
        in_img = read_png_file(input->img);
        if (in_img == NULL)
        {
            fprintf(stderr, "Impossible to read %s image\n", input->img);
            continue;
        }
        out_thumb_img = make_thumb(in_img, 150);
        if (out_thumb_img == NULL)
        {
            fprintf(stderr, "Impossible to creat thumbnail of %s image\n", input->img);
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
        gdImageDestroy(in_img);
        free(input);
    }
    return (void *)NULL;
}

int main(int argc, char **argv)
{
    char *img_dir_path = NULL;
    char dir_extra[] = "./";
    int n_img = 0;
    char img_file_p[] = "image-list.txt";
    char img_file_path[100];
    FILE *img_file = NULL;
    int n_threads;
    char img_list[40][100];
    char img_name[40][100];
    char buffer[100];
    pthread_t *WM_thread_ids;
    pthread_t *R_thread_ids;
    pthread_t *TH_thread_ids;
    imgs *input;
    if (argc != 3)
    {
        printf("Wrong Number of arguments.\n");
        printf("./ap-paralelo-2 img_dir (number of threads per stage)\n");
        exit(1);
    }

    n_threads = atoi(argv[2]);

    img_dir_path = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 4));
    strcpy(img_dir_path, dir_extra);
    strcat(img_dir_path, argv[1]);
    strcat(img_dir_path, "/");

    strcpy(img_file_path, img_dir_path);
    strcat(img_file_path, img_file_p);

    img_file = fopen(img_file_path, "r");
    if (img_file == NULL)
    {
        printf("File %s not found.\n", img_file_path);
        exit(1);
    }
    if (pipe(WM_pipe) != 0)
    {
        printf("Error Creating Pipe.\n");
    }
    if (pipe(R_pipe) != 0)
    {
        printf("Error Creating Pipe.\n");
    }
    if (pipe(TH_pipe) != 0)
    {
        printf("Error Creating Pipe.\n");
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

    WM_thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
    if (WM_thread_ids == NULL)
        exit(-1);
    R_thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
    if (R_thread_ids == NULL)
        exit(-1);
    TH_thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
    if (TH_thread_ids == NULL)
        exit(-1);

    for (int i = 0; i < n_threads; i++)
    {
        pthread_create(&WM_thread_ids[i], NULL, watermark_function, NULL);
        pthread_create(&R_thread_ids[i], NULL, resize_function, NULL);
        pthread_create(&TH_thread_ids[i], NULL, thumbnail_function, NULL);
    }

    for (int i = 0; i < n_img; i++)
    {
        input = (imgs *)malloc(sizeof(imgs));
        input->n_img = n_img;
        strcpy(input->img, img_list[i]);
        strcpy(input->img_name, img_name[i]);
        write(WM_pipe[1], &input, sizeof(input));
        printf("%s write to WM_pipe\n", input->img_name);
    }
    input = (imgs *)malloc(sizeof(imgs));
    input->n_img = -10;
    for (int i = 0; i < n_threads; i++)
    {
        write(WM_pipe[1], &input, sizeof(input));
    }

    for (int i = 0; i < n_threads; i++)
    {
        pthread_join(WM_thread_ids[i], NULL);
        pthread_join(R_thread_ids[i], NULL);
        pthread_join(TH_thread_ids[i], NULL);
    }
    free(img_dir_path);
    free(input);
    fclose(img_file);
    free(WM_thread_ids);
    free(R_thread_ids);
    free(TH_thread_ids);
    return 0;
}
