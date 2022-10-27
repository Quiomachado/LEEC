#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicionario.h"

int main(int argc, char **argv)
{
    char *nomeFicheiroIn, *nomeFicheiroOut, *nomeDic, *aux;
    char extOut[] = ".paths";
    FILE *fpDic, *fpPals, *fpOut;
    char palavra1[30], palavra2[30];
    int num = 1, i;
    char *token;
    char ***dic = {NULL};
    int *counters = NULL;
    int maxSize, location1, location2;
    int *isSorted;
    int exitProcessing = 0, count = 0;

    if (argc < 3)
    {
        exit(0);
    }

    /*criacao de strings com os nomes dos ficheiros*/
    nomeDic = argv[1];
    nomeFicheiroIn = argv[2];
    token = strtok(nomeDic, ".");
    count = 1;
    while (token != NULL)
    {
        token = strtok(NULL, ".");
        count++;
        if (count == 2 && token != NULL)
        {
            if (strcmp(token, "dict") != 0)
                exit(0);
        }
    }
    if (count > 3 || (count == 2 && token == NULL))
        exit(0);
    token = strtok(nomeFicheiroIn, ".");
    count = 1;
    while (token != NULL)
    {
        token = strtok(NULL, ".");
        count++;
        if (count == 2 && token != NULL)
        {
            if (strcmp(token, "pals") != 0)
                exit(0);
        }
    }
    if (count > 3 || (count == 2 && token == NULL))
        exit(0);
    aux = (char *)malloc(sizeof(char) * (strlen(nomeFicheiroIn) + 1));
    strcpy(aux, nomeFicheiroIn);
    aux[strlen(aux) - 5] = '\0';
    nomeFicheiroOut = (char *)malloc(sizeof(char) * (strlen(aux) + 7));

    strcpy(nomeFicheiroOut, aux);
    strcat(nomeFicheiroOut, extOut);

    /*abrir ficheiro de dicionario*/
    fpDic = fopen(nomeDic, "r");
    if (fpDic == NULL)
    {
        free(nomeFicheiroOut);
        free(aux);
        return 0;
    }

    /*ler dicionario e criar estrutura*/
    counters = IniCounters(fpDic, &maxSize);
    dic = IniDic(fpDic, counters, maxSize);
    isSorted = (int *)malloc(sizeof(int) * (maxSize + 1));
    for (i = 0; i <= maxSize; i++)
    {
        isSorted[i] = 0;
    }
    fclose(fpDic);
    fpDic = fopen(nomeDic, "r");
    if (fpDic == NULL)
    {
        FreeMem(dic, counters, maxSize);
        free(isSorted);
        free(nomeFicheiroOut);
        free(aux);
        return 0;
    }
    dic = LerDicionario(fpDic, dic, counters, maxSize);

    /*abrir ficheiro pals*/
    fpPals = fopen(nomeFicheiroIn, "r");
    if (fpPals == NULL)
    {
        FreeMem(dic, counters, maxSize);
        free(isSorted);
        free(nomeFicheiroOut);
        free(aux);
        fclose(fpDic);
        return 0;
    }

    /*abir ficheiro de saida*/
    fpOut = fopen(nomeFicheiroOut, "w");
    if (fpOut == NULL)
    {
        exitProcessing = 1;
    }

    /*ler ficheiro Pals*/
    while (fscanf(fpPals, "%s %s %d", palavra1, palavra2, &num) == 3 && !exitProcessing)
    {
        if (strlen(palavra1) > maxSize)
        {
            fprintf(fpOut, "%s -1\n%s\n", palavra1, palavra2);
            continue;
        }
        if (isSorted[strlen(palavra1)] == 0)
        {
            Sort(dic, counters, strlen(palavra1));
            isSorted[strlen(palavra1)] = 1;
        }
        if (Search(dic[strlen(palavra1)], palavra1, 0, counters[strlen(palavra1)]) == -1 || Search(dic[strlen(palavra2)], palavra2, 0, counters[strlen(palavra2)]) == -1)
        {
            fprintf(fpOut, "%s -1\n%s\n", palavra1, palavra2);
            continue;
        }
        fprintf(fpOut, "\n");
    }

    /*libertação de memória alocada*/
    FreeMem(dic, counters, maxSize);
    free(nomeFicheiroOut);
    free(aux);
    fclose(fpPals);
    fclose(fpDic);
    free(isSorted);
    if (!exitProcessing)
        fclose(fpOut);
    return 0;
}