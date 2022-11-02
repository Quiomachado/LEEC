#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct _queueElem
{
    int pos;
    int wt;
};

static QueueElem *queue;
static int clear;
static int hsize;

void exch(QueueElem A, QueueElem B)
{
    QueueElem tmp;
    tmp = A;
    A = B;
    B = tmp;
    return;
}

void FixUp(int Idx)
{
    while (Idx > 0 && (queue[(Idx - 1) / 2].wt < queue[Idx].wt))
    {
        exch(queue[Idx], queue[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
}

void FixDown(int Idx)
{
    int Child;
    int N = clear - 1;

    while (2 * Idx < N)
    {
        Child = 2 * Idx + 1;
        if (Child < N && (queue[Child].wt < queue[Child + 1].wt))
            Child++;
        if (!(queue[Idx].wt < queue[Child].wt))
            break;
        exch(queue[Idx], queue[Child]);
        Idx = Child;
    }
}

void PQinit(int Size)
{
    queue = (QueueElem *)malloc(Size * sizeof(QueueElem));
    hsize = Size;
    clear = 0;
}

void PQinsert(int pos, int wt)
{
    QueueElem A;
    A.pos = pos;
    A.wt = wt;
    if ((clear + 1) < hsize)
    {
        queue[clear] = A;
        FixUp(clear);
        clear++;
    }
    return;
}

int PQempty()
{
    if (clear == 0)
        return 1;
    return 0;
}

int PQdelMax()
{
    exch(queue[0], queue[clear - 1]);
    FixDown(0);
    return queue[--clear].pos;
}

void PQdec(int Idx, int nWt)
{
    if (nWt < queue[Idx].wt)
    {
        queue[Idx].wt = nWt;
        FixUp(Idx);
    }
    else if (nWt > queue[Idx].wt)
    {
        queue[Idx].wt = nWt;
        FixDown(Idx);
    }
}
