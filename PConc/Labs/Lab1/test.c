#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Num_Words(char *path)
{
    FILE *fpIn = NULL;
    int size = 0;
    fpIn = fopen(path, "r");
    char buffer[100];
    while (fscanf(fpIn, "%s", buffer) == 1)
    {
        size++;
    }
    fclose(fpIn);
    return size;
}

char **Read_Dic(int size, char *path)
{
    char **word_array = {NULL};
    FILE *fpIn = NULL;
    char buffer[100];
    int iterator = 0;
    fpIn = fopen(path, "r");
    word_array = (char **)malloc(sizeof(char *) * size);
    while (fscanf(fpIn, "%s", buffer) == 1)
    {
        word_array[iterator] = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(word_array[iterator], buffer);
        iterator++;
    }
    if (iterator != size)
    {
        printf("NOT SAME SIZE!!!\n");
        exit(0);
    }
    fclose(fpIn);
    return word_array;
}

int MyCompare(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

void Sort(char **word_array, int size)
{
    qsort(word_array, size, sizeof(char *), MyCompare);
}

int main(int argc, char **argv)
{
    char **word_array = {NULL};
    int size = 0;
    printf("%s", argv[1]);
    /* char *path = NULL;
    path = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));
    if (path == NULL)
        exit(0); */
    char path[] = "lusiadas-words.txt";
    /* strcpy(path, argv[1]); */
    size = Num_Words(path);
    word_array = Read_Dic(size, path);
    Sort(word_array, size);
    for (int i = 0; i < size; i++)
    {
        /* printf("%s\n", word_array[i]); */
        free(word_array[i]);
    }
    free(word_array);
    // free(path);
    return 0;
}