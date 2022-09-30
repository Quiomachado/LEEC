/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-03-01
 *
 * NAME
 *   palTab.c
 *
 * DESCRIPTION
 *   Main program for unique word finding with tables
 *
 * COMMENTS
 *   Code variant for distribution
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STR 100

typedef struct _st_texto {
  int  n_total_palavras;      /* total number of words */
  int  n_dist_palavras;       /* number of distinct words*/
  char **palavras;            /* Table of strings for words */
  int  *ocorrencias;          /* Table of integers counting occurrence */
} st_texto;


/******************************************************************************
 * LePalavra()
 *
 * Arguments: f - pointer to file where word will be read
 * Returns:  pointer to word just read
 * Side-Effects: none
 *
 * Description:
 *   Return pointer to local buffer with word, or NULL if file read failed
 *   Maximum word size MAX_STR
 *****************************************************************************/

char *LePalavra ( FILE *f )
{
  static char palavra[MAX_STR];       /* note static local buffer returned */

  if ( fscanf ( f, "%s", palavra ) ==1 )
    return (palavra);
  else
    return ((char *) NULL);
}


/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - pointer to string holding name of file to open
 *            mode - pointer to string with 'r'/'w' etc mode for file open
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *   Open named file in requested mode, message stderr and exit if open fails
 *****************************************************************************/

FILE *AbreFicheiro ( char *nome, char *mode )
{
  FILE *fp;
  fp = fopen ( nome, mode );
  if ( fp == NULL ) {
    fprintf ( stderr, "ERROR: cannot open file '%s'\n", nome);
    exit ( 1 );                                 /* non-zero exit status */
  }
  return (fp);
}


/******************************************************************************
 * AlocaTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *   Read input file to find dimensions, allocate and initialize tables
 *****************************************************************************/

void AlocaTabelaPalavras ( char *ficheiro, st_texto *t)
{
  FILE *fp;
  char *palavra;
  int i, len, n_max_caracteres = 0;

  (*t).n_total_palavras = 0;
  (*t).n_dist_palavras = 0;
  fp = AbreFicheiro ( ficheiro, "r" );
  while ( ( palavra = LePalavra ( fp ) ) != NULL ) {
    (*t).n_total_palavras++;
    len = strlen ( palavra );
    if ( len > n_max_caracteres )
      n_max_caracteres = len;
  }
  fclose ( fp );
  printf ( "Words count: %d\n", (*t).n_total_palavras );

  (*t).palavras =  /* -- INSERT code for memory allocation --*/;
  if ( (*t).palavras == NULL ) {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 2 );
  }
  (*t).ocorrencias = /* -- INSERT code for memory allocation --*/;
  if ( (*t).ocorrencias == NULL ) {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 4 );
  }
  for ( i = 0; i < (*t).n_total_palavras; i++ )   {
    (*t).palavras[i] =  /* -- INSERT code for memory allocation --*/;
    if ( (*t).palavras[i] == NULL ) {
      fprintf ( stderr, "ERROR: not enough memory available!\n" );
      exit ( 3 );
    }
    (*t).palavras[i][0] = /* -- INSERT code to initialize table of strings  --*/ ;
    (*t).ocorrencias[i] = /* -- INSERT code to initialize table  of counters --*/ ;
  }
  return;
}


/******************************************************************************
 * NovaPalavra()
 *
 * Arguments: palavra - pointer to string holding a word
 *            st_texto - pointer to structure where run information is kept
 * Returns:  int index of word in table
 * Side-Effects: none
 *
 * Description:
 *   Search for a word in the table. If the word is not found returns -1,
 *   Otherwise returns the position of the word in the table
 *****************************************************************************/

int NovaPalavra ( char *palavra, st_texto *t )
{
  int i = 0;
  while ( ( (*t).palavras[i][0] != '\0' ) && i < (*t).n_total_palavras ) {
    if ( strcmp ( (*t).palavras[i], palavra ) == 0 )
      return (i);
    i++;
  }
  return (-1);
}


/******************************************************************************
 * PreencheTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void PreencheTabelaPalavras ( char *ficheiro, st_texto *t )
{
  FILE *f;
  int n;
  char *palavra;

  f = AbreFicheiro ( ficheiro, "r" );
  while ( ( palavra = LePalavra ( f ) ) != NULL ) {
    if ( ( n = NovaPalavra ( palavra, &(*t) ) ) == -1 ) {
      strcpy ( (*t).palavras[(*t).n_dist_palavras], palavra );
      (*t).ocorrencias[(*t).n_dist_palavras]++;
      (*t).n_dist_palavras++;
    }
    else {
      (*t).ocorrencias[n]++;
    }
  }
  fclose ( f );
  return;
}


/******************************************************************************
 * EscreveFicheiro()
 *
 * Arguments: ficheiro - pointer to string holding name of file to save
 *            st_texto - pointer to structure where information is kept
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *   Open output file, write table of words.
 *****************************************************************************/

void EscreveFicheiro ( char *ficheiro, st_texto *t )
{
  FILE *f;
  char *nome;
  int i = 0;

  nome =  /* -- INSERT code for memory allocation,  --*/ ;
  /* including dot (.) extension and string termination, see below */
  if ( nome == NULL ) {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 5 );
  }
  strcpy ( nome, ficheiro );
  strcat ( nome, ".palavras" );
  f = AbreFicheiro ( nome, "w" );
  for ( i = 0; i < (*t).n_dist_palavras; i++ ) {
    fprintf ( f, "%d: %s\n", (*t).ocorrencias[i], (*t).palavras[i] );
  }
  printf ( "Count of distinct words: %d\n", (*t).n_dist_palavras );
  fclose ( f );

  /* Anything else I should do here? */

  return;
}


/******************************************************************************
 * main()
 *
 * Arguments: argc - counter of number of arguments in call
 *            argv - pointer to array of strings holding the arguments
 * Returns: exit status
 * Side-Effects: none
 *
 * Description:
 *   Get filename, read input file and make word table, write output file
 *****************************************************************************/

int main ( int argc, char **argv )
{
  int i;
  st_texto st_palavras;

  if ( argc < 2 ) {
    fprintf ( stderr, "ERROR: missing filename in argument!\n" );
    exit ( 6 );
  }
  AlocaTabelaPalavras ( argv[1], &st_palavras );
  PreencheTabelaPalavras ( argv[1],&st_palavras );
  EscreveFicheiro ( argv[1], &st_palavras );

  return (0);
}
