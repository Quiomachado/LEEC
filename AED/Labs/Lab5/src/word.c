/******************************************************************************
 * (c) 2010-2020 IST AED Team
 * Last modified: lms 2021-10-21
 *
 * NAME
 *   word.c
 *
 * DESCRIPTION
 *   Data structure to hold word and useage count
 *	Auxiliary functions to read and write text files
 *		functions to allocate and manipulate structures
 *		functions to sort abstract structures
 *		implementations of "less" functions for different criteria
 *
 * COMMENTS
 *   Code for preliminary distribution, to be completed
 ******************************************************************************/

#define MAX_CHARS 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> /* strcasecmp() */

#include "word.h"

struct _WordS
{ /* structure for word */
   char *word;
   int numUses;
};

/******************************************************************************
 * ExitMemError ()
 *
 * Arguments:    k - exit status to use
 * Returns:      (void)
 * Side-Effects: executions ends
 *
 * Description: general function for memory allocation error and exit
 *****************************************************************************/

void ExitMemError(int k)
{
   fprintf(stderr, "ERROR: Not enough memory.\n");
   exit(k);
}

/******************************************************************************
 * ReadWord ()
 *
 * Arguments:    fp - file pointer to read from
 * Returns:      char * - pointer to word read, NULL if read fails
 * Side-Effects: none
 *
 * Description:
 *   Reads a word from open file, returns pointer to local static buffer
 *   Words in file are assumed to not exceed MAX_CHARS-1 in length
 *****************************************************************************/

char *ReadWord(FILE *fp)
{
   static char locword[MAX_CHARS]; /* buffer for caller to copy */

   if (fscanf(fp, "%s", locword) == 1)
      return locword;
   else
      return NULL;
}

/******************************************************************************
 * OpenFile ()
 *
 * Arguments: nome - pointer to string containing name of file to open
 *            mode - mode to use to open the file
 * Returns: FILE * - handle to file opened
 * Side-Effects: input file is opened
 *
 * Description: Open file for reading, returns handle, or exits if it fails
 *****************************************************************************/

FILE *OpenFile(char *name, char *mode)
{
   FILE *fp;

   fp = fopen(name, mode);
   if (fp == NULL)
   {
      fprintf(stderr, "Error: Unable to open file '%s'\n.", name);
      exit(1);
   }
   return fp;
}

/******************************************************************************
 * AllocWordArray ()
 *
 * Arguments: wtab - pointer to word table
 *            ficheiro - handle for input file
 * Returns: int - number of words read
 * Side-Effects: words are read, word table is allocated; input file is closed
 *
 * Description: Reads the input file, counts the total number of words and
 *		allocates the memory for the table structure
 *****************************************************************************/

int AllocWordArray(WordTab *wtab, char *file)
{
   FILE *fp;
   char *locword;

   int nWords = 0;

   fp = OpenFile(file, "r");
   while ((locword = ReadWord(fp)) != NULL)
      nWords++;

   fclose(fp);

   (*wtab) = (WordTab)malloc(nWords * sizeof(WordS *));

   if (*wtab == NULL)
      ExitMemError(2);

   return nWords;
}

/******************************************************************************
 * NewWord ()
 *
 * Arguments:    wtab - word table
 *               palavra - pointer to string containing word
 *               numWords - number of distinct words found so far
 * Returns:      int - index/status regarding word being new
 * Side-Effects: none
 *
 * Description: Search table for word, return index or -1 if not found
 *****************************************************************************/

int NewWord(WordTab wtab, char *locword, int numWords)
{
   int i = 0;

   while (i < numWords)
   {
      if (strcasecmp(wtab[i]->word, locword) == 0)
         return i;
      i++;
   }
   return -1;
}

/******************************************************************************
 * FillInWordArray ()
 *
 * Arguments:    wtab - word table
 *               ficheiro - name of input file
 * Returns:      int - number of distinct words in file
 * Side-Effects: prints message with distinct word count
 *
 * Description: Opens file, fills table with distinct words found
 *****************************************************************************/

int FillInWordArray(WordTab wtab, char *file)
{
   FILE *f;
   int n;
   char *locword;
   int numWords = 0;

   f = OpenFile(file, "r");
   while ((locword = ReadWord(f)) != NULL)
   {
      if ((n = NewWord(wtab, locword, numWords)) == -1)
      {
         /* word has not been seen; add to table */
         wtab[numWords] = (WordS *)malloc(sizeof(WordS));

         if (wtab[numWords] == NULL)
            ExitMemError(3);
         wtab[numWords]->word = (char *)
             malloc(sizeof(char) * (strlen(locword) + 1));

         if (wtab[numWords]->word == NULL)
            ExitMemError(4);
         strcpy(wtab[numWords]->word, locword);
         wtab[numWords]->numUses = 1;
         numWords++;
      }
      else
      {
         /* word is not new; increment occurrence count */
         wtab[n]->numUses++;
      }
   }
   fclose(f);
   return numWords;
}

/******************************************************************************
 * WriteFile ()
 *
 * Arguments: wtab - word table
 *            ficheiro - handle for output file
 *            numWords - number of distinct words seen
 * Returns: (void)
 * Side-Effects: output file is written
 *
 * Description: Writes table to file
 *****************************************************************************/

void WriteFile(WordTab wtab, char *ficheiro, int numWords)
{
   FILE *f;
   char *word;
   int i = 0;

   word = (char *)malloc(
       (strlen(ficheiro) + strlen(".palavras") + 1) * sizeof(char));
   if (word == NULL)
   {
      fprintf(stderr,
              "ERROR: allocation of output filename. Not enough memory.\n");
      exit(2);
   }
   strcpy(word, ficheiro);
   strcat(word, ".palavras");

   f = OpenFile(word, "w");
   for (i = 0; i < numWords; i++)
   {
      fprintf(f, "%d: %s\n", wtab[i]->numUses, wtab[i]->word);
   }

   fclose(f);
   free(word);

   return;
}

/******************************************************************************
 * FreeWordArray ()
 *
 * Arguments: wtab - pointer to word table
 *            numWords - number of words actually used
 * Returns: (void)
 * Side-Effects: frees memory allocated for word table, structs and strings
 *
 * Description: Frees all the memory allocated in WordTab
 *****************************************************************************/

void FreeWordArray(WordTab *wtab, int numWords)
{
   /** -- free all memory allocated for table of words -- */
   int i;
   /*==== TODO ====*/
   for (i = 0; i < numWords; i++)
   {
      free((*wtab)[i]->word);
      free((*wtab)[i]);
   }
   free(*wtab);

   return;
}

/******************************************************************************
 * LessAlphabetic ()
 *
 * Arguments: a, b - items to be compared
 * Returns: int - result of comparison
 * Side-Effects: none
 *
 * Description: Implements the comparision for alphabetic ordering
 *****************************************************************************/

int LessAlphabetic(Item a, Item b)
{
   if (strcasecmp(((WordS *)a)->word, ((WordS *)b)->word) < 0)
      return 1;
   else
      return 0;
}

/*************************************************************************
 **  -- Add comparison functions for the remaining criteria --
 *************************************************************************/

int LessNumUses(Item a, Item b)
{
   if (((WordS *)a)->numUses < ((WordS *)b)->numUses)
      return 1;
   else
      return 0;
}

int LessLength(Item a, Item b)
{
   int sA, sB;
   sA = strlen(((WordS *)a)->word);
   sB = strlen(((WordS *)b)->word);
   if (sA < sB)
      return 1;
   else
      return 0;
}

int MoreAlphabetic(Item a, Item b)
{
   if (strcasecmp(((WordS *)a)->word, ((WordS *)b)->word) > 0)
      return 1;
   else
      return 0;
}
int MoreNumUses(Item a, Item b)
{
   if (((WordS *)a)->numUses > ((WordS *)b)->numUses)
      return 1;
   else
      return 0;
}

int MoreLength(Item a, Item b)
{
   int sA, sB;
   sA = strlen(((WordS *)a)->word);
   sB = strlen(((WordS *)b)->word);
   if (sA > sB)
      return 1;
   else
      return 0;
}

/*==== TODO ====*/
