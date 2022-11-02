#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

typedef struct _queueElem QueueElem;

void PQinit(int Size);
void PQinsert(int pos, int wt);
int PQempty();
int PQdelMax();
void PQdec(int Idx, int nWt);

#endif