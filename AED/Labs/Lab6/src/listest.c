/*  Quick test for List package, namely insert* functions
 *  Last change abl 2019.03.21
 */



/* Header Inclusions                                              */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LinkedList.h"


/*
 *  Function:
 *    freeEntryItem
 *
 *  Description:
 *    Frees the memory allocated to an Item of the type Entry
 *
 *  Arguments:
 *    Pointer to the item
 *      Item item
 *
 *  Return value:
 *    None.
 */
void freeEntryItem(Item item)
{
    return;       /* no mem actually allocated */
}


/*
 * Function:
 *   compareItems
 *
 *  Description:
 *    Item comparison function to be passed in for List sorting
 */
int  compareItems(Item it1, Item it2)
{
    int i1, i2;

    i1 = *((int *) it1);
    i2 = *((int *) it2);

    if (i1 < i2)
        return -1;
    if (i1 > i2)
        return 1;
    return 0;
}

/*#define N 8*/
#define N 20

int data[N]={84, 
39, 
78, 
79, 
91, 
19, 
33, 
76, 
27, 
55, 
47, 
62, 
36, 
51, 
95, 
91, 
63, 
71, 
14, 
60};


/*
 * Function:
 *   main
 */
int main(int argc, char *argv[])
{
    LinkedList *lp1, *lp2, *aux;

/*   int data[N]= {5, 6, 7, 8, 1, 2, 3, 4}; */
    int i, err;

    lp1 = initLinkedList();
    lp2 = initLinkedList();
    /* create lists */
    for (i=0; i<N; i++)
    {
        lp1 = insertUnsortedLinkedList(lp1, (Item) &(data[i]) );
        lp2 = insertSortedLinkedList(lp2, (Item) &(data[i]), compareItems, &err);
    }

    /* print out lists */
    printf ("---- lp1\n");
    aux = lp1;
    while(aux != NULL)
    {
        i = *((int *) getItemLinkedList(aux));
        printf ("item = %d \n",  i);
        aux = getNextNodeLinkedList(aux);
    }
    printf ("---- lp2\n");
    aux = lp2;
    while(aux != NULL)
    {
        i = *((int *) getItemLinkedList(aux));
        printf ("item = %d \n",  i);
        aux = getNextNodeLinkedList(aux);
    }

    /* Free linked lists with entries  */
    freeLinkedList(lp1, freeEntryItem);
    freeLinkedList(lp2, freeEntryItem);

    return 0;
}
