#include "LinkedList.h"

struct LinkedListStruct
{
    Item data;
    LinkedList *next;
};

LinkedList *initList(void)
{
    return NULL;
}

void freeLinkedList(LinkedList *first, void (*freeItem)(Item))
{
    LinkedList *aux, *next;

    aux = first;
    while (aux != NULL)
    {
        next = aux->next;
        freeItem(aux->data);
        free(aux);
    }
    return;
}

LinkedList *getNextNodeLinkedList(LinkedList *node)
{
    if (node == NULL)
        return NULL;
    return (node->next);
}

LinkedList *getDataLinkedList(LinkedList *node)
{
    if (node == NULL)
        return NULL;
    return (node->data);
}

LinkedList *insertAlpha(LinkedList *head, Item item, int (*compareItems)(Item it1, Item it2))
{
    LinkedList *new, *aux;

    new = (LinkedList *)calloc(1, sizeof(LinkedList));
    if (new == NULL)
        return NULL;

    new->data = item;
    new->next = NULL;

    if (head == NULL)
    {
        return new;
    }

    if (compareItems(item, head->data) <= 0)
    {
        new->next = head;
        return new;
    }

    aux = head;
    while (aux != NULL)
    {
        if (aux->next != NULL)
        {
            if (compareItems(item, aux->next->data) <= 0)
            {
                new->next = aux->next;
                aux->next = new;
                return head;
            }
        }
        else
        {
            aux->next = new;
            return head;
        }
        aux = aux->next;
    }
    return NULL;
}