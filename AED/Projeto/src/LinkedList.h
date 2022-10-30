#ifndef LINKEDLISTHEADER
#define LINKEDLISTHEADER

#include "defs.h"

typedef struct LinkedListStruct LinkedList;

LinkedList *initLinkedList(void);
void FreeLinkedLIst(LinkedList *first, void (*freeItemFnt)(Item));
LinkedList *getNextNodeLinkedList(LinkedList *node);
Item getItemLinkedList(LinkedList *node);
LinkedList *insertUnsortedLinkedList(LinkedList *next, Item this);

#endif