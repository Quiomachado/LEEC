#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct _queueElem
{
    Item elem;
} QueueElem;

static QueueElem *queue;
static int free;
static int hsize;

void PQinit(int Size)
{
    queue = (QueueElem *)malloc(Size * sizeof(QueueElem));
    hsize = Size;
    free = 0;
}

void PQinsertFirst(Item A)
{
    QueueElem new;
    int i;
    if (free + 1 == hsize)
        exit(0);
    new.elem = A;
    for (i = free - 1; i >= 0; i--)
    {
        queue[i + 1] = queue[i];
    }
    queue[0] = new;
    free++;
    return;
}

int PQempty()
{
    if (free == 0)
        return 1;
    return 0;
}

Item PQdelMax()
{
    Item del;
    del = queue[--free].elem;
    return del;
}
