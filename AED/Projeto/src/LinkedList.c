#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

struct LinkedListStruct
{
    Item this;
    LinkedList *next;
};

LinkedList *initLinkedList(void)
{
    return NULL;
}

void FreeLinkedLIst(LinkedList *first, void (*freeItemFnt)(Item))
{
    LinkedList *aux, *next;

    for (aux = first; aux != NULL; aux = next)
    {
        next = aux->next;
        freeItemFnt(aux->this);
        free(aux);
    }
    return;
}

LinkedList *getNextNodeLinkedList(LinkedList *node)
{
    return ((node == NULL) ? NULL : node->next);
}

Item getItemLinkedList(LinkedList *node)
{
    return ((node == NULL) ? NULL : node->this);
}

LinkedList *insertUnsortedLinkedList(LinkedList *next, Item this)
{
    LinkedList *new;

    new = (LinkedList *)malloc(sizeof(LinkedList));
    if (new == NULL)
        exit(0);

    new->this = this;
    new->next = next;

    return new;
}