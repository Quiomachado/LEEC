/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-28
 *
 * NAME
 *   list.h
 *
 * DESCRIPTION
 *   Structure and prototypes for type t_lista, a 1st order abstract data type
 *   that is a container.
 *   Each variable of type t_lista implements a node of list of Items.
 *
 * COMMENTS
 *
 ******************************************************************************/

#ifndef _LISTA_H
#define _LISTA_H

/* def for pointer casts */
#define Item void*

/* type definition for structure to hold list item */
typedef struct _t_lista t_lista;


t_lista  *iniLista (void);
t_lista  *criaNovoNoLista (t_lista *lp, Item this, int *err);
Item      getItemLista (t_lista *p);
t_lista  *getProxElementoLista(t_lista *p);
int       numItensNaLista (t_lista *lp);
void 	  libertaLista(t_lista *lp, void freeItem(Item));

#endif
