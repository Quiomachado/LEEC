/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-28
 *
 * NAME
 *   list.c
 *
 * DESCRIPTION
 *   Implement general linked list functions, for use in word lists
 *
 * COMMENTS
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "list.h"


/* Linked list  */
struct _t_lista {
  Item            this;
  struct _t_lista *prox;
};


/******************************************************************************
 * iniLista ()
 *
 * Arguments: none
 * Returns: t_lista *
 * Side-Effects: list is initialized
 *
 * Description: initializes list
 *****************************************************************************/

t_lista  *iniLista(void)
{
  return NULL;
}


/******************************************************************************
 * criaNovoNoLista ()
 *
 * Arguments: nome - Item to save in list node
 * Returns: t_lista  *
 * Side-Effects: none
 *
 * Description: creates and returns a new node that can later be added to the
 *              list
 *****************************************************************************/

t_lista  *criaNovoNoLista (t_lista* lp, Item this, int *err)
{
  t_lista *novoNo;

  novoNo = (t_lista*) malloc(sizeof(t_lista));
  if(novoNo!=NULL) {
    novoNo->this = this;
    novoNo->prox = lp;
    lp = novoNo;
    *err = 0;
  } else {
    *err = 1;
  }
  return lp;
}


/******************************************************************************
 * getItemLista ()
 *
 * Arguments: this - pointer to element
 * Returns: Item
 * Side-Effects: none
 *
 * Description: returns an Item from the list
 *****************************************************************************/

Item getItemLista (t_lista *p)
{
  return p -> this;
}


/******************************************************************************
 * getProxElementoLista ()
 *
 * Arguments: this - pointer to element
 * Returns: pointer to next element in list
 * Side-Effects: none
 *
 * Description: returns a pointer to an element of the list
 *
 *****************************************************************************/

t_lista *getProxElementoLista(t_lista *p) {

  return p -> prox;
}


/******************************************************************************
 * numItensNaLista ()
 *
 * Arguments: lp - pointer to list
 * Returns:  count of the number of items in list
 * Side-Effects: none
 *
 * Description: returns the number of items (nodes) in the list
 *
 *****************************************************************************/

int numItensNaLista(t_lista *lp) {
  t_lista *aux;  /* auxiliar pointers to travel through the list */
  int conta = 0;
  aux = lp;

  for(aux = lp; aux != NULL; aux = aux -> prox)
    conta++;

  return conta;
}

/******************************************************************************
 * libertaLista ()
 *
 * Arguments: lp - pointer to list
 * Returns:  (void)
 * Side-Effects: frees space occupied by list items
 *
 * Description: free list
 *
 *****************************************************************************/

void libertaLista(t_lista *lp, void freeItem(Item)) {
  t_lista *aux, *newhead;  /* auxiliar pointers to travel through the list */

  for(aux = lp; aux != NULL; aux = newhead) {
    newhead = aux->prox;
    freeItem(aux->this);
    free(aux);
  }

  return;
}
