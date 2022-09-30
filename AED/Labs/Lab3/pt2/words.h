/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-03-01
 *
 * NAME
 *   words.h
 *
 * DESCRIPTION
 *   Structure and prototypes for type t_palavra
 *   t_palavra includes a string (nome) and an int (ocorrencias)
 *
 * COMMENTS
 *   Needs list.h definitions
 ******************************************************************************/

#ifndef _PALAVRA_H
#define _PALAVRA_H

/* ex-utils */

void    erroMemoria (char *msg);
t_lista *testaPalavra (t_lista *lp, char *pal);
void    libertaItem(Item this);


/* type definition for structure to hold word */
typedef struct _t_palavra t_palavra;


/* Interface functions for type t_palavra */
t_palavra  *criaPalavra (char *nome);
char       *getPalavra (t_palavra *p);
int         getNocorr (t_palavra *p);
void        incOcorr (t_palavra *p);
void        escreveUmaPalavra (t_palavra *p,FILE *fp);
void        libertaPalavra(t_palavra *p);

#endif
