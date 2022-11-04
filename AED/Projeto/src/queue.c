#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct _queueElem
{
    int pos;
    int wt;
};

typedef struct heapS
{
    int clear;
    int hsize;
    QueueElem *queue;
} heap;

void exch(QueueElem A, QueueElem B)
{
    QueueElem tmp;
    tmp = A;
    A = B;
    B = tmp;
    return;
}

heap *FixUp(heap *acervo, int Idx)
{
    while (Idx > 0 && (acervo->queue[(Idx - 1) / 2].wt < acervo->queue[Idx].wt))
    {
        exch(acervo->queue[Idx], acervo->queue[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
    return acervo;
}

heap *FixDown(heap *acervo, int Idx)
{
    int Child;
    int N = (acervo->clear) - 2;

    while (2 * Idx < N)
    {
        Child = 2 * Idx + 1;
        if (Child < N && (acervo->queue[Child].wt > acervo->queue[Child + 1].wt))
            Child++;
        if (!(acervo->queue[Idx].wt > acervo->queue[Child].wt))
            break;
        exch(acervo->queue[Idx], acervo->queue[Child]);
        Idx = Child;
    }
    return acervo;
}

heap *PQinit(heap *acervo, int Size)
{
    acervo = (heap *)malloc(sizeof(heap));
    if (acervo == NULL)
        exit(0);
    acervo->queue = (QueueElem *)calloc(1, Size * sizeof(QueueElem));
    if (acervo->queue == NULL)
        exit(0);
    acervo->hsize = Size;
    acervo->clear = 0;
    return acervo;
}

heap *PQinsert(heap *acervo, int pos, int wt)
{
    QueueElem A;
    A.pos = pos;
    A.wt = wt;
    if (((acervo->clear) + 1) < acervo->hsize)
    {
        acervo->queue[acervo->clear] = A;
        acervo = FixUp(acervo, acervo->clear);
        acervo->clear++;
    }
    return acervo;
}

int PQempty(heap *acervo)
{
    if (acervo->clear == 0)
        return 1;
    return 0;
}

int PQdelMax(heap **acervo)
{
    exch((*acervo)->queue[0], (*acervo)->queue[(*acervo)->clear - 1]);
    *acervo = FixDown(*acervo, 0);
    return (*acervo)->queue[--((*acervo)->clear)].pos;
}

heap *PQdec(heap *acervo, int Idx, int nWt)
{
    int tmp;
    for (tmp = 0; tmp < acervo->clear; tmp++)
        if (acervo->queue[tmp].pos == Idx)
            break;
    if (nWt < acervo->queue[tmp].wt)
    {
        acervo->queue[tmp].wt = nWt;
        acervo = FixUp(acervo, tmp);
    }
    else if (nWt > acervo->queue[tmp].wt)
    {
        acervo->queue[tmp].wt = nWt;
        acervo = FixDown(acervo, tmp);
    }
    return acervo;
}

void PQFree(heap *acervo)
{
    free(acervo->queue);
    free(acervo);
}
