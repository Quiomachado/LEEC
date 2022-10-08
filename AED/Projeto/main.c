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
    char *nomeFicheiroIn, *nomeFicheiroOut, *nomeDic;
    char extOut[] = ".paths";
    node **dict = {NULL};
    FILE *fpDic, *fpPals, *fpOut;

    if (argc < 3)
    {
        Usage(argv[0]);
    }

    /*criacao de strings com os nomes dos ficheiros*/
    nomeDic = argv[1];
    nomeFicheiroIn = argv[2];
    nomeFicheiroIn[strlen(nomeFicheiroIn) - 5] = '\0';
    nomeFicheiroOut = (char *)malloc(sizeof(char) * (strlen(nomeFicheiroIn) + 7));

    strcpy(nomeFicheiroOut, nomeFicheiroIn);
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

    FreeDict(dict);
    free(nomeFicheiroOut);
    fclose(fpDic);
    return 0;
}