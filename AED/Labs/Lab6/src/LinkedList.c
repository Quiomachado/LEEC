/******************************************************************************
 * (c) 2018-2019 AED Team
 * Last modified: abl 2019-03-17
 *
 * NAME
 *      LinkedList.c
 *
 * DESCRIPTION
 *      Implementation of an abstract Linked List
 *
 * COMMENTS
 *      (Derived from 2018/10/24 lab4 code)
 *
 *  Implementation details:
 *      Linked list node: Each node of the list contains an item and a
 *      pointer to the next node.
 *      The item is specified in the file defs.h, expectably also a pointer.
 *
 *      Item deletion/freeing and comparison functions must be supplied
 *
 *****************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#include"LinkedList.h"

/*
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *      1) Item of the linked list node (possibly pointer to data)
 *      2) Pointer to next node of the linked list.
 */
struct LinkedListStruct
{
    Item this;
    LinkedList *next;
};


/*
 *  Function:
 *    initLinkedList
 *
 *  Description:
 *    Initializes a new linked list.
 *
 *  Arguments:
 *    None
 *
 *  Return value:
 *    Returns the pointer to a new linked list.
 */
LinkedList * initLinkedList(void)
{
    return NULL;
}


/*
 *  Function:
 *    freeLinkedList
 *
 *  Description:
 *    Frees the memory allocated to a linked list.
 *
 *  Arguments:
 *    Pointer to the first element of a linked list:
 *      (LinkedList *) first
 *    Function to free the memory allocated to the items:
 *      void freeItem(Item)
 *
 *  Return value:
 *    None
 */
void freeLinkedList(LinkedList *first, void (* freeItemFnt)(Item))
{
    LinkedList *aux, *next;

    /* Cycle from the first to the last element           */
    for(aux = first; aux != NULL; aux = next)
    {
        next = aux->next;           /* Keep track of the next node */
        freeItemFnt(aux->this);     /* Free current item data with passed function */
        free(aux);                  /* Free current node    */
    }
    return;
}


/*
 *  Function:
 *    lengthLinkedList
 *
 *  Description:
 *    Determines the length of a linked list.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *        (LinkedList *) first
 *
 *  Return value:
 *    Returns the length of the linked list.
 */
int lengthLinkedList(LinkedList *first)
{
    LinkedList *aux;
    int counter;

    /* Length determination cycle                                   */
    for(aux = first, counter = 0;
        aux!=NULL;
        counter++, aux = aux->next);

    return counter;
}


/*
 *  Function:
 *    getNextNodeLinkedList
 *
 *  Description:
 *    Returns the next node of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the next node of a linked list. NULL
 *   is returned in case the current node is empty or there is no
 *   node following the current node.
 */
LinkedList * getNextNodeLinkedList(LinkedList * node)
{
  return ((node == NULL) ? NULL : node->next);
}


/*
 *  Function:
 *    getItemLinkedList
 *
 *  Description:
 *    Gets the item of a linked list node.
 *
 *  Arguments:
 *    Pointer to a linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the item of a linked list node. NULL
 *   is returned if the node is NULL (or if the item is NULL).
 */
Item getItemLinkedList(LinkedList *node)
{
    if(node == NULL)  /* Check that node is not empty */
        return NULL;

    return node->this;
}



/*
 *  Function:
 *    insertUnsortedLinkedList
 *
 *  Description:
 *    Creates a new node at the head of the linked list.
 *
 *  Arguments:
 *    Item to associate to the new node:
 *      Item this
 *    Pointer to the next node:
 *      (LinkedList *) next
 *
 *  Return value:
 *    Returns the pointer to the new head of the list.
 */
LinkedList *insertUnsortedLinkedList(LinkedList *next, Item this)
{
    LinkedList *new;

    /* Memory allocation */
    new = (LinkedList *) malloc(sizeof(LinkedList));

    /* Check memory allocation errors */
    if(new == NULL)
        return NULL;

    /* Initialize new node */
    new->this = this;
    new->next = next;

    return new;
}


/*
 *  Function:
 *    insertSortedLinkedList
 *
 *  Description:
 *    Inserts an item in order in a sorted linked list.
 *
 *  Arguments:
 *    Pointer to the first node of a sorted linked list:
 *        (LinkedList *) first
 *    Pointer to item to be inserted:
 *        Item item
 *    Pointer to function to compare two items:
 *        int comparisonItemFnt(void * item1, void * item2)
 *
 *      This function must return a value less, equal, or greater
 *      than zero if item1 compares less, equal, or greater than
 *      item2, respectively.
 *
 *    Pointer to integer to write error return value:
 *        (int *) err
 *
 *        0 upon sucess, 1 in case the item is NULL, and 2 in
 *      case of memory allocation failure.
 *
 *  Return value:
 *    Returns the pointer to the first node of the sorted linked list.
 */
LinkedList * insertSortedLinkedList(LinkedList *first,
                Item item,
                int (* compareItems) (Item it1, Item it2),
                int * err)
{
    LinkedList  *new, *aux;

    /* alloc and check */
    new = (LinkedList *) malloc(sizeof(LinkedList));
    if(new == NULL)
        return NULL;
    
    new->this = item;           /* Initialize new node  */
    new->next = NULL;

    if (first == NULL)          /* first item in list */
    {
        return new;
    }
    /* list not empty, insertion sort */
    /* insert at head */
    if ((compareItems(item, first->this) <= 0) )
    {
        new->next = first;
        return new;
    }
    /* second etc */
    aux = first;
    while(aux != NULL)
    {
        if (aux->next != NULL)
        {
            if ( compareItems(item, aux->next->this) <= 0 )
            {
                new->next = aux->next;
                aux->next = new;
                return first;
            }
        }
        else        /* none left, insert in tail */
        {
            aux->next = new;
            return first;
        }
        aux = aux->next;
    }
    return NULL;
}
