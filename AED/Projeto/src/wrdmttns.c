#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicionario.h"
#include "LinkedList.h"
#include "queue.h"

static double maxWT = 1000000000000000;

typedef struct tStruct
{
    int pos;
    int wt;
} twint;

int *GetMaxSubs(FILE *fpPals, int maxSize, int **pCounter)
{
    char *trash = NULL;
    int len, tmp;
    int *subs;
    subs = (int *)malloc(sizeof(int) * maxSize);
    if (subs == NULL)
        exit(0);
    *pCounter = (int *)calloc(1, sizeof(int) * maxSize);
    while (fscanf(fpPals, "%s %s %d", trash, trash, &tmp) == 3)
    {
        len = strlen(trash);
        if (len > maxSize)
            continue;
        if (!(*pCounter[len]))
            *pCounter[len] = 1;
        if (subs[len] > tmp)
            subs[len] = tmp;
    }
    printf("WTF\n");
    return subs;
}

int DiffChars(char *A, char *B)
{
    int count, i, len;
    len = strlen(A);
    count = 0;
    for (i = 0; i < len; i++)
    {
        if (A[i] != B[i])
            count++;
    }
    return count;
}

double Dijkstra(LinkedList **A, int nv, int s, int f, int mSub)
{
    LinkedList *t;
    twint *tmp;
    int v, w;
    int *st;
    double *wt;
    double finalWt;

    st = (int *)malloc(sizeof(int) * nv);
    if (st == NULL)
        exit(0);
    wt = (double *)malloc(sizeof(double) * nv);
    if (wt == NULL)
        exit(0);

    PQinit(nv);
    for (v = 0; v < nv; v++)
    {
        st[v] = -1;
        wt[v] = maxWT;
    }
    PQinsert(s, wt[s]);
    wt[s] = 0;
    PQdec(s, wt[0]);
    while (!PQempty())
    {
        if (wt[v = PQdelMax()] != maxWT)
        {
            for (t = A[v]; t != NULL; getNextNodeLinkedList(t))
            {
                tmp = (twint *)getItemLinkedList(t);
                if (tmp->wt > mSub)
                    continue;
                PQinsert(tmp->pos, wt[tmp->pos]);
                if (wt[w = tmp->pos] > wt[v] + tmp->wt)
                {
                    wt[w] = wt[v] + tmp->wt;
                    PQdec(w, wt[w]);
                    st[w] = v;
                }
            }
        }
    }
    finalWt = wt[f];
    free(st);
    free(wt);
    if (finalWt == maxWT)
        return -1;
    return finalWt;
}

int main(int argc, char **argv)
{
    char *nomeFicheiroIn, *nomeFicheiroOut, *nomeDic, *aux;
    char extOut[] = ".paths";
    FILE *fpDic, *fpPals, *fpOut;
    char palavra1[30], palavra2[30];
    int num = 1, i, k, j, wt;
    char *token;
    char ***dic = {NULL};
    int *counters = NULL;
    int *subs = NULL;
    int *pCounter = NULL;
    int maxSize, len, loc1, loc2;
    int *isSorted;
    int exitProcessing = 0, count = 0;
    twint *new;
    LinkedList ***listv = {NULL};

    if (argc < 3)
    {
        exit(0);
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

    /*Get Max Num Of Subs Per Letter and reopen Pals*/
    subs = GetMaxSubs(fpPals, maxSize, &pCounter);
    fclose(fpPals);
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

    /*Criar Grafos*/
    listv = (LinkedList ***)calloc(1, sizeof(LinkedList **) * maxSize);
    if (listv == NULL)
        exit(0);
    for (i = 1; i < maxSize; i++)
    {
        if (pCounter[i])
        {
            listv[i] = (LinkedList **)calloc(1, sizeof(LinkedList *) * counters[i]);
            if (listv[i] == NULL)
                exit(0);
            for (k = 0; k < counters[i]; k++)
            {
                if (listv[i][k] == NULL)
                    listv[i][k] = initLinkedList();
                for (j = 0; j < counters[i]; j++)
                {
                    if (j == k)
                        continue;
                    if ((wt = DiffChars(dic[i][k], dic[i][j])) > subs[i])
                        continue;
                    new = (twint *)malloc(sizeof(twint));
                    if (new == NULL)
                        exit(0);
                    new->pos = j;
                    new->wt = (wt * wt);
                    listv[i][k] = insertUnsortedLinkedList(listv[i][k], (Item) new);
                }
            }
        }
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
        len = strlen(palavra1);
        if (len > maxSize || num < 0)
        {
            fprintf(fpOut, "%s -1\n%s\n", palavra1, palavra2);
            continue;
        }
        loc1 = Search(dic[len], palavra1, 0, counters[len]);
        loc2 = Search(dic[len], palavra2, 0, counters[len]);
        if (isSorted[len] == 0)
        {
            Sort(dic, counters, len);
            isSorted[len] = 1;
        }
        if (loc1 == -1 || loc2 == -1)
        {
            fprintf(fpOut, "%s -1\n%s\n", palavra1, palavra2);
            continue;
        }

        printf("%f\n", Dijkstra(listv[len], counters[len], loc1, loc2, num));

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