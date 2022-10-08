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
    char palavra1[100], palavra2[100];
    int num = 1;

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

    /*ler dicionario e criar estrutura*/
    dict = IniDict(dict);
    dict = LerDicionario(fpDic, dict);

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

    /*ler ficheiro Pals*/
    while (fscanf(fpPals, "%s %s %d", palavra1, palavra2, &num) == 3)
    {
        if (strlen(palavra1) != strlen(palavra2))
            exit(69);
        dict = OrdenarLinha(strlen(palavra1), dict);
        if (num == 1)
            ImprimirTamanhoLinha(strlen(palavra1), dict, palavra1, fpOut);
        else if (num == 2)
            ImprimirPosicao(strlen(palavra1), dict, palavra1, palavra2, fpOut);
        fprintf(fpOut, "\n");
    }

    /*libertação de memória alocada*/
    FreeDict(dict);
    free(nomeFicheiroOut);
    free(aux);
    fclose(fpPals);
    fclose(fpDic);
    fclose(fpOut);
    return 0;
}