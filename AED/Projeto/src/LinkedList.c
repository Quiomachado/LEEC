#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

struct LinkedListStruct
{
    int pos;
    int wt;
    LinkedList *next;
};

LinkedList *initLinkedList(void)
{
    return NULL;
}

void FreeLinkedLIst(LinkedList *first)
{
    LinkedList *aux, *next;

    for (aux = first; aux != NULL; aux = next)
    {
        next = aux->next;
        free(aux);
    }
    return;
}

LinkedList *getNextNodeLinkedList(LinkedList *node)
{
    return (node->next);
}

int getWt(LinkedList *node)
{
    return (node->wt);
}

int getpos(LinkedList *node)
{
    return (node->pos);
}

LinkedList *insertUnsortedLinkedList(LinkedList *next, int pos, int wt)
{
    LinkedList *new;

    new = (LinkedList *)malloc(sizeof(LinkedList));
    if (new == NULL)
        exit(0);

    new->pos = pos;
    new->wt = wt;
    new->next = next;

    return new;
}