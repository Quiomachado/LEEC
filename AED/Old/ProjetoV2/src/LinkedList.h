#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

typedef struct LinkedListStruct LinkedList;

LinkedList *initList(void);
void freeLinkedList(LinkedList *first, void (*freeItem)(Item));
LinkedList *getNextNodeLinkedList(LinkedList *node);
LinkedList *getDataLinkedList(LinkedList *node);
LinkedList *insertAlpha(LinkedList *head, Item item, int (*compareItems)(Item it1, Item it2));

#endif