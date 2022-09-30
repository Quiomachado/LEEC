/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-03-01
 *
 * NAME
 *   words.c
 *
 * DESCRIPTION
 *   Implements functions for type t_palavra
 *
 * COMMENTS
 *   Code variant for distribution
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>    /* strcasecmp() */

#include "list.h"
#include "words.h"


struct _t_palavra {
  char* pal;
  int ocorrencias;
};


/******************************************************************************
 * testaPalavra ()
 *
 * Arguments: lp - pointer to list of words
 *            novaPal - pointer to new word to be tested / inserted
 * Returns: t_listaPalavras  *  - pointer to list of words
 * Side-Effects: none
 *
 * Description: search for a word in the list
 *              if found increment occurrence count, return list unchanged
 *              otherwise adds a new word to the list and return a pointer
 *                    to the beginning of the list
 *              (this pointer may not be the same passed in)
 * NOTE: for results identical to PalTab.c use strcmp(), instead of strcasecmp()
 *****************************************************************************/

t_lista  *testaPalavra(t_lista *lp, char *novaPal)
{
  t_lista *aux;       /* pointer to scan the list */
  t_palavra *pal;
  int err;            /* error status, not checked */

  aux = lp;
  while (aux != NULL){
    pal = (t_palavra*) getItemLista(aux);
    if( strcasecmp(getPalavra(pal),novaPal) == 0) {
      incOcorr(pal);
      return lp;
    }
    aux = getProxElementoLista(aux);
  }
  /* Expect insertion at the begin of the list (not sorted!) */

  pal = criaPalavra(novaPal);
  lp = criaNovoNoLista(lp, pal, &err);

  return lp;
}


/******************************************************************************
 * libertaItem ()
 *
 * Arguments: p - pointer to Item
 * Returns: (void)
 * Side-Effects: calls function to free word structure
 *
 * Description: interfaces generic list item to specific word structure
 *****************************************************************************/

void libertaItem(Item this)
{
  libertaPalavra((t_palavra *) this);
  return;
}



/******************************************************************************
 * erroMemoria ()
 *
 * Arguments: msg - pointer to message to print
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: print to standard error output an allocation error message
 *
 *****************************************************************************/

void erroMemoria(char *msg) {

  fprintf(stderr, "Error during memory reserve attempt.\n");
  fprintf(stderr, "Msg: %s\n",msg);
  fprintf(stderr, "Exit Program due to unmanaged error.\n");

  exit(1);
}



/******************************************************************************
 * criaPalavra()
 *
 * Arguments: pal - word to be stored
 * Returns: t_palavra  *
 * Side-Effects: space is allocated for new word
 *
 * Description: Create and return a new word, set occurrence counter to 1
 *****************************************************************************/

t_palavra  *criaPalavra(char *pal)
{
  t_palavra *nova;

  nova = /* INSERT CODE to ALLOCATE MEMORY */
    if(nova == NULL)
      erroMemoria("Reserve memory for new word in criaPalavra" );

  nova -> pal = /* INSERT CODE to ALLOCATE MEMORY */
    if(nova == NULL)
      erroMemoria("Reserve of name in criaPalavra" );

  strcpy(nova -> pal,pal);
  nova -> ocorrencias = 1;

  return nova;
}


/******************************************************************************
 * getPalavra ()
 *
 * Arguments: p - pointer to word structure
 * Returns: (char *) pointer to actual word (string)
 * Side-Effects: none
 *
 * Description: returns a pointer to the string containing the actual word
 *****************************************************************************/

char *getPalavra(t_palavra *p)
{
  return p -> pal;
}


/******************************************************************************
 * getNocorr ()
 *
 * Arguments: p - pointer to word structure
 * Returns: int
 * Side-Effects: none
 *
 * Description: returns the counter (ocorrencias) associated to a word
 *****************************************************************************/

int getNocorr(t_palavra *p)
{
  return p -> ocorrencias;
}


/******************************************************************************
 * inOcorr ()
 *
 * Arguments: p - pointer to word structure
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: increment counter for the number of times (ocorrencias)
 *              a word has been found
 *****************************************************************************/

void incOcorr(t_palavra *p)
{
  (p -> ocorrencias)++;
}


/******************************************************************************
 * escreveUmaPalavra ()
 *
 * Arguments: p - pointer to word structure
 *            fp - pointer to output file descriptor
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: writes to given file the word and the number of times
 *              it was seen on the input (ocorrencias)
 *****************************************************************************/

void escreveUmaPalavra(t_palavra *p, FILE *fp)
{
  fprintf(fp,"%4d : %s\n", p->ocorrencias, p->pal);
}


/******************************************************************************
 * libertaPalavra ()
 *
 * Arguments: p - pointer to word structure
 * Returns: (void)
 * Side-Effects: allocated memory for word structure is freed
 *
 * Description: free memory reserved for word
 *****************************************************************************/

void libertaPalavra(t_palavra *p)
{
  /* -- FREE MEMORY RESERVED FOR WORD -- */

  return;
}
