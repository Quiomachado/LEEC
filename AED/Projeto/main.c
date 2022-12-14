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
    node **dict = {NULL};
    FILE *fpDic, *fpPals, *fpOut;
    char *palavra1, *palavra2;
    int num = 1, i, maxSize;
    int *isSorted;

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
        printf("ERROR cannot open dictionary file %s.\n", nomeDic);
        exit(3);
    }

    /*ler dicionario e obter tamanho maximo de palavra*/
    maxSize = GetMax(fpDic);

    /* Reiniciar dicionario */
    fclose(fpDic);
    fpDic = fopen(nomeDic, "r");
    if (fpDic == NULL)
    {
        printf("ERROR cannot open dictionary file %s.\n", nomeDic);
        exit(3);
    }

    /* Ler dicionario e guardar */
    dict = IniDict(dict, maxSize);
    dict = LerDicionario(fpDic, dict, maxSize);
    isSorted = (int *)malloc(sizeof(int) * maxSize);
    for (i = 0; i < maxSize; i++)
    {
        isSorted[i] = 0;
    }

    /*abrir ficheiro pals*/
    fpPals = fopen(nomeFicheiroIn, "r");
    if (fpPals == NULL)
    {
        printf("ERROR cannot open pals file %s.\n", nomeFicheiroIn);
        exit(3);
    }

    /*abir ficheiro de saida*/
    fpOut = fopen(nomeFicheiroOut, "w");
    if (fpOut == NULL)
    {
        printf("ERROR cannot open pals file %s.\n", nomeFicheiroOut);
        exit(3);
    }

    palavra1 = (char *)malloc(sizeof(char) * (maxSize + 1));
    palavra2 = (char *)malloc(sizeof(char) * (maxSize + 1));

    /*ler ficheiro Pals*/
    while (fscanf(fpPals, "%s %s %d", palavra1, palavra2, &num) == 3)
    {
        if (strlen(palavra1) != strlen(palavra2))
        {
            fprintf(fpOut, "%s %s %d\n", palavra1, palavra2, num);
            continue;
        }
        if (strlen(palavra1) > maxSize)
        {
            fprintf(fpOut, "%s %s %d\n", palavra1, palavra2, num);
            continue;
        }
        if (isSorted[strlen(palavra1)] == 0)
        {
            dict = OrdenarLinha(strlen(palavra1), dict);
            isSorted[strlen(palavra1)] = 1;
        }
        if (num == 1)
            ImprimirTamanhoLinha(strlen(palavra1), dict, palavra1, fpOut);
        else if (num == 2)
            ImprimirPosicao(strlen(palavra1), dict, palavra1, palavra2, fpOut);
        fprintf(fpOut, "\n");
    }

    /*liberta????o de mem??ria alocada*/
    free(isSorted);
    free(palavra1);
    free(palavra2);
    FreeDict(dict, maxSize);
    free(nomeFicheiroOut);
    free(aux);
    fclose(fpPals);
    fclose(fpDic);
    fclose(fpOut);
    return 0;
}