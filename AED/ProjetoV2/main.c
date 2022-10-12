#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicionario.h"

void Usage(char *nomeProg)
{
    printf("Usage: %s <nome1>.dict <nome2>.pals\n", nomeProg);
    exit(1);
}

int main(int argc, char **argv)
{
    char *nomeFicheiroIn, *nomeFicheiroOut, *nomeDic, *aux;
    char extOut[] = ".stats";
    FILE *fpDic, *fpPals, *fpOut;
    char palavra1[30], palavra2[30];
    int num = 1;
    int count = 0;
    char ***dic = {NULL};
    int *counters = NULL;
    int maxSize, location1, location2;
    int exitProcessing = 0;

    if (argc < 3)
    {
        Usage(argv[0]);
    }

    /*criacao de strings com os nomes dos ficheiros*/
    nomeDic = argv[1];
    nomeFicheiroIn = argv[2];
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
    fclose(fpDic);
    fpDic = fopen(nomeDic, "r");
    if (fpDic == NULL)
    {
        FreeMem(dic, counters, maxSize);
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
        if (count > 0)
        {
            fprintf(fpOut, "\n");
        }
        if (strlen(palavra1) != strlen(palavra2))
        {
            fprintf(fpOut, "%s %s %d\n", palavra1, palavra2, num);
            continue;
        }
        Sort(dic, counters, strlen(palavra1));
        if (Search(dic[strlen(palavra1)], palavra1, 0, counters[strlen(palavra1)]) == -1 || Search(dic[strlen(palavra2)], palavra2, 0, counters[strlen(palavra2)]) == -1 || (num != 1 && num != 2))
        {
            fprintf(fpOut, "%s %s %d\n", palavra1, palavra2, num);
            continue;
        }
        if (num == 1)
            ImprimirTamanhoDaLinha(strlen(palavra1), counters, palavra1, fpOut);
        else if (num == 2)
        {
            location1 = Search(dic[strlen(palavra1)], palavra1, 0, counters[strlen(palavra1)]);
            location2 = Search(dic[strlen(palavra2)], palavra2, 0, counters[strlen(palavra2)]);
            fprintf(fpOut, "%s %d\n%s %d\n", palavra1, location1, palavra2, location2);
        }
        count++;
    }

    /*libertação de memória alocada*/
    FreeMem(dic, counters, maxSize);
    free(nomeFicheiroOut);
    free(aux);
    fclose(fpPals);
    fclose(fpDic);
    if (!exitProcessing)
        fclose(fpOut);
    return 0;
}