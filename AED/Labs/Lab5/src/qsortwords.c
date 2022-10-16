/******************************************************************************
 * (c) 2010-2020 IST AED Team
 * Last modified: abl 2020-04-21
 *
 * NAME
 *   sortwords.c
 *
 * DESCRIPTION
 *   Main program for unique word finding and sorting with tables
 *
 * COMMENTS
 *   Code for preliminary distribution, to be completed
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "word.h"

enum sort_order
{
    ascending,
    descending
};

enum sort_criteria
{
    alphabetic,
    length,
    occurrences
};

int OP_CNT = 0; /* global variable, to simplify complexity assessment */

/******************************************************************************
 * sort ()
 *
 * Arguments: a - table of items to sort
 *            l, r - limits on table to consider
 *            less - item comparison function
 * Returns: (void)
 * Side-Effects: table is sorted in place
 *
 * Description: implements "some" sorting algorithm for abstract type (Item),
 *       using also an abstract type comparison function (*less)
 *           a[] - array of abstract type Item to be sorted
 *           l - index of first element in the array to be sorted
 *           r - last element of the array to be sorted
 *           (*less)(Item,Item) - abstract type comparison function
 *****************************************************************************/

int partition(Item arr[], int l, int r, int (*less)(Item, Item))
{
    Item pivot = arr[r];
    Item tmp;

    int i = l - 1;
    int j;

    for (j = l; j < r; j++)
    {
        if (less(arr[j], pivot))
        {
            i++;

            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            OP_CNT += 4;
        }
        OP_CNT += 2;
    }

    tmp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = tmp;
    OP_CNT += 4;

    return (i + 1);
}

void sort(Item arr[], int l, int r, int (*less)(Item, Item)) /* BUBLE SORT */
{
    if (l < r)
    {
        int pi = partition(arr, l, r, less);

        sort(arr, l, pi - 1, less);
        sort(arr, pi + 1, r, less);
    }
}

/******************************************************************************
 * main ()
 *
 *****************************************************************************/

int main(int argc, char **argv)
{
    int TnumWords;   /* total number of words in input file */
    int numWords;    /* number of distint words in input file */
    WordTab wordtab; /* table holding the structure */

    /* default initialization for alfabetic order and ascending */
    enum sort_criteria criterio = alphabetic;
    enum sort_order sentido = ascending;
    char *file = argv[1];

    argv++; /* get past prog and file names */
    while (*(++argv))
    {
        if (strcmp(*argv, "-alfabetica") == 0)
            criterio = alphabetic;
        else if (strcmp(*argv, "-ocorrencias") == 0)
            criterio = occurrences;
        else if (strcmp(*argv, "-comprimento") == 0)
            criterio = length;
        else if (strcmp(*argv, "-a") == 0)
            sentido = ascending;
        else if (strcmp(*argv, "-d") == 0)
            sentido = descending;
        else
        {
            fprintf(stderr, "Wrong arguments\n");
            exit(3);
        }
    }
    TnumWords = AllocWordArray(&wordtab, file);
    printf("Total number of words: %d\n", TnumWords);

    numWords = FillInWordArray(wordtab, file);
    printf("Number of different words = %d\n", numWords);

    OP_CNT = 0;

    /*  Call the sorting function using as argument the
        appropriate comparison function selected by user option */

    if (criterio == alphabetic)
    {

        if (sentido == ascending)
            sort((Item)wordtab, 0, numWords - 1, LessAlphabetic);
        else if (sentido == descending)
            sort((Item)wordtab, 0, numWords - 1, MoreAlphabetic);
    }
    else if (criterio == occurrences)
    {
        if (sentido == ascending)
            sort((Item)wordtab, 0, numWords - 1, LessNumUses);
        else if (sentido == descending)
            sort((Item)wordtab, 0, numWords - 1, MoreNumUses);
    }
    else if (criterio == length)
    {
        if (sentido == ascending)
            sort((Item)wordtab, 0, numWords - 1, LessLength);
        else if (sentido == descending)
            sort((Item)wordtab, 0, numWords - 1, MoreLength);
    }

    /* ---------------------------------------- */
    printf("Accesses count for sort: %d\n", OP_CNT);

    WriteFile(wordtab, file, numWords);
    /*  printf("Number of different words: %d\n", n_palavras);  */

    /* -- Insert code to call functions to free allocated memory -- */

    FreeWordArray(&wordtab, numWords);

    /* ------------------------------------------------------------ */

    return 0;
}
