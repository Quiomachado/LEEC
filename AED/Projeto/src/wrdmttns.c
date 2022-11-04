#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicionario.h"
#include "LinkedList.h"
#include "queue.h"

static double maxWT = 1000000000000000;

int *GetMaxSubs(FILE *fpPals, int maxSize, int **pCounter)
{
    char trash1[30], trash2[30];
    int len, tmp, i;
    int *subs;
    int *pc;
    subs = (int *)malloc(sizeof(int) * maxSize);
    if (subs == NULL)
        exit(0);
    pc = (int *)malloc(sizeof(int) * maxSize);
    if (pc == NULL)
        exit(0);
    for (i = 0; i < maxSize; i++)
    {
        subs[i] = 0;
        pc[i] = 0;
    }
    while (fscanf(fpPals, "%s %s %d", trash1, trash2, &tmp) == 3)
    {
        len = strlen(trash1) - 1;
        if (len > maxSize)
            continue;
        pc[len]++;
        if (subs[len] < tmp)
            subs[len] = tmp;
    }
    *pCounter = pc;
    return subs;
}

int DiffChars(char *A, char *B, int len)
{
    int count, i;
    count = 0;
    for (i = 0; i < len; i++)
        if (A[i] != B[i])
            count++;
    return count;
}

int Dijkstra(LinkedList **A, int nv, int s, int f, int mSub, double **tmpW, int **tmpSt)
{
    LinkedList *t;
    int tmpPos, tmpWt;
    int v, w, flag = -1;
    heap *acervo = NULL;
    double *wt;
    int *st;

    st = (int *)malloc(sizeof(int) * nv);
    if (st == NULL)
        exit(0);
    wt = (double *)malloc(sizeof(double) * nv);
    if (wt == NULL)
        exit(0);

    acervo = PQinit(nv);
    for (v = 0; v < nv; v++)
    {
        st[v] = -1;
        wt[v] = maxWT;
    }
    wt[s] = 0;
    acervo = PQinsert(acervo, s, wt[s]);
    while (!PQempty(acervo))
    {
        v = PQdelMax(&acervo);
        if (v == f)
        {
            flag = 1;
            break;
        }
        for (t = A[v]; t != NULL; t = getNextNodeLinkedList(t))
        {
            tmpWt = getWt(t);
            tmpPos = getpos(t);
            if (tmpWt > mSub)
                continue;
            if (wt[w = tmpPos] == maxWT)
            {
                wt[w] = wt[v] + tmpWt;
                st[w] = v;
                acervo = PQinsert(acervo, w, wt[w]);
            }
            else if (wt[w] > wt[v] + tmpWt)
            {
                wt[w] = wt[v] + tmpWt;
                acervo = PQdec(acervo, w, wt[w]);
                st[w] = v;
            }
        }
    }
    *tmpSt = st;
    *tmpW = wt;

    PQFree(acervo);
    return flag;
}

void shortestPath(LinkedList **Graph, int Child, int *st, char **dic, FILE *fpOut, int *dist)
{
    LinkedList *aux;
    if (st[Child] == -1)
    {
        fprintf(fpOut, "%s %d\n", dic[Child], *dist);
        return;
    }
    for (aux = Graph[st[Child]]; aux != NULL; aux = getNextNodeLinkedList(aux))
    {
        if (getpos(aux) == Child)
        {
            (*dist) += getWt(aux);
            Child = st[Child];
            shortestPath(Graph, Child, st, dic, fpOut, dist);
            fprintf(fpOut, "%s\n", dic[getpos(aux)]);
            break;
        }
    }
}

int main(int argc, char **argv)
{
    char *nomeFicheiroIn, *nomeFicheiroOut, *nomeDic, *aux;
    char extOut[] = ".paths";
    FILE *fpDic, *fpPals, *fpOut;
    char palavra1[30], palavra2[30];
    int num = 1, i, k, j, wt;
    char ***dic = {NULL};
    int *counters = NULL;
    int *subs = NULL;
    int *pCounter = NULL;
    int maxSize, len, loc1, loc2, final = 0, flag = 0;
    int *isSorted;
    double *wts;
    int *st;
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
    isSorted = (int *)malloc(sizeof(int) * maxSize);
    for (i = 0; i < maxSize; i++)
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

    /*abir ficheiro de saida*/
    fpOut = fopen(nomeFicheiroOut, "w");
    if (fpOut == NULL)
    {
        exit(0);
    }

    /*ler ficheiro Pals*/
    while (fscanf(fpPals, "%s %s %d", palavra1, palavra2, &num) == 3)
    {
        len = strlen(palavra1) - 1;
        if (len > maxSize || num < 0)
        {
            fprintf(fpOut, "%s -1\n%s\n", palavra1, palavra2);
            continue;
        }
        if (num == 0 && strcmp(palavra1, palavra2) == 0)
        {
            fprintf(fpOut, "%s %d\n%s\n", palavra1, num, palavra2);
        }
        if (isSorted[len] == 0)
        {
            Sort(dic, counters, len);
            isSorted[len] = 1;
        }
        loc1 = Search(dic[len], palavra1, 0, counters[len] - 1);
        loc2 = Search(dic[len], palavra2, 0, counters[len] - 1);
        if (loc1 == -1 || loc2 == -1)
        {
            fprintf(fpOut, "%s -1\n%s\n", palavra1, palavra2);
            continue;
        }
        if (pCounter[len] > 0)
        {
            if (listv[len] == NULL)
            {
                listv[len] = (LinkedList **)calloc(1, sizeof(LinkedList *) * counters[len]);
                if (listv[len] == NULL)
                    exit(0);
                for (k = 0; k < counters[len]; k++)
                {
                    if (listv[len][k] == NULL)
                        listv[len][k] = initLinkedList();
                    for (j = k + 1; j < counters[len]; j++)
                    {
                        if ((wt = DiffChars(dic[len][k], dic[len][j], len + 1)) > subs[len])
                            continue;
                        listv[len][k] = insertUnsortedLinkedList(listv[len][k], j, (wt * wt));
                        listv[len][j] = insertUnsortedLinkedList(listv[len][j], k, (wt * wt));
                    }
                }
            }
            flag = Dijkstra(listv[len], counters[len], loc1, loc2, (num * num), &wts, &st);
            final = 0;
            if (flag == 1)
                shortestPath(listv[len], loc2, st, dic[len], fpOut, &final);
            else if (flag == -1)
                fprintf(fpOut, "%s -1\n%s\n", palavra1, palavra2);
            free(wts);
            free(st);
            pCounter[len]--;
            if (pCounter[len] <= 0)
            {
                for (i = 0; i < counters[len]; i++)
                    FreeLinkedLIst(listv[len][i]);
                free(listv[len]);
            }
        }
        fprintf(fpOut, "\n");
    }

    /*libertação de memória alocada*/
    FreeMem(dic, counters, maxSize);
    free(nomeFicheiroOut);
    free(aux);
    free(listv);
    fclose(fpPals);
    fclose(fpDic);
    free(isSorted);
    free(pCounter);
    free(subs);
    fclose(fpOut);
    return 0;
}