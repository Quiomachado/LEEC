#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

typedef struct _queueElem QueueElem;
typedef struct heapS heap;

heap *PQinit(int Size);
heap *PQinsert(heap *acervo, int pos, int wt);
int PQempty(heap *acervo);
int PQdelMax(heap **acervo);
heap *PQdec(heap *acervo, int Idx, int nWt);
void PQFree(heap *acervo);

#endif