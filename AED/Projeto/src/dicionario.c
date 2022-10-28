#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicionario.h"

int *IniCounters(FILE *fpDic, int *maxSize)
{
    char novaPal[100];
    int size = 0;
    int *counters = (int *)calloc(1, sizeof(int));

    while (fscanf(fpDic, "%s", novaPal) == 1)
    {
        if (strlen(novaPal) > size)
        {
            counters = (int *)realloc(counters, sizeof(int) * (strlen(novaPal) + 1));
            for (size = size + 1; size <= strlen(novaPal); size++)
                counters[size] = 0;
            size = strlen(novaPal);
        }
        counters[strlen(novaPal)]++;
    }

    *maxSize = size;

    return counters;
}

char ***IniDic(FILE *fpDic, int *counters, int n)
{
    int i, j;
    char ***dic = {NULL};

    dic = (char ***)malloc(sizeof(char **) * (n + 1));
    for (i = 1; i <= n; i++)
    {
        dic[i] = (char **)malloc(sizeof(char *) * (counters[i] + 1));
        for (j = 0; j <= counters[i]; j++)
        {
            dic[i][j] = (char *)malloc(sizeof(char) * (i + 1));
            dic[i][j][0] = '\0';
        }
    }

    return dic;
}

char ***LerDicionario(FILE *fpDic, char ***dic, int *counters, int n)
{
    int times[n + 1];
    char nPal[n];
    int i;
    unsigned int tamanho;

    for (i = 0; i < n + 1; i++)
        times[i] = 0;

    while (fscanf(fpDic, "%s", nPal) == 1)
    {
        tamanho = strlen(nPal);
        strcpy(dic[tamanho][times[tamanho]], nPal);
        times[tamanho]++;
    }

    return dic;
}

int MyCompare(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

void Sort(char ***dic, int *counters, int linha)
{
    qsort(dic[linha], counters[linha] + 1, sizeof(char *), MyCompare);
}

int Search(char **dic, char *palavra, int low, int high)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;

        if (strcmp(dic[mid], palavra) == 0)
            return mid - 1;
        if (strcmp(dic[mid], palavra) > 0)
            return Search(dic, palavra, low, mid - 1);
        return Search(dic, palavra, mid + 1, high);
    }

    return -1;
}

void ImprimirTamanhoDaLinha(int linha, int *counters, char *palavra, FILE *fpOut)
{
    fprintf(fpOut, "%s %d\n", palavra, counters[linha]);
    return;
}

void FreeMem(char ***dic, int *counters, int n)
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j <= counters[i]; j++)
        {
            free(dic[i][j]);
        }
        free(dic[i]);
    }
    free(dic);
    free(counters);
}