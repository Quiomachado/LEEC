#ifndef LINKEDLISTHEADER
#define LINKEDLISTHEADER

#include "defs.h"

typedef struct LinkedListStruct LinkedList;

LinkedList *initLinkedList(void);
void FreeLinkedLIst(LinkedList *first);
LinkedList *getNextNodeLinkedList(LinkedList *node);
LinkedList *insertUnsortedLinkedList(LinkedList *next, int pos, int wt);
int getWt(LinkedList *node);
int getpos(LinkedList *node);

#endif