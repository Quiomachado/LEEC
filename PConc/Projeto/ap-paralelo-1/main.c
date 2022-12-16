#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "image-lib.h"
char WATERMARK[] = "watermark.png";

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
    int *n_img_thread = NULL;
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

    free(img_dir_path);
    return 0;
}