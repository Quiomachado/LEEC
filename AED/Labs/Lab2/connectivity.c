/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-22
 *
 * NAME
 *   connectivity.c
 *
 * DESCRIPTION
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 *   Code for public distribution
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "connectivity.h"

#define DEBUG 0

unsigned long int elemProc = 0;
unsigned long int elemUni = 0;
unsigned long int elem = 0;

/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *****************************************************************************/

void quick_find(int *id, int N, FILE *fp, int quietOut)
{
   int i, p, q, t, k, j, l = 0;
   int pairs_cnt = 0; /* connection pairs counter */
   int links_cnt = 0; /* number of links counter */
   elemProc = 0;
   elemUni = 0;
   elem = 0;
   int nConjuntos = N;
   unsigned long int flag = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++)
   {
      id[i] = i;
      elem++;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2)
   {
      pairs_cnt++;
      /* do search first */
      if (id[p] == id[q])
      {
         elemProc += 2;
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      for (t = id[p], i = 0, elemUni++; i < N; i++)
      {
         if (id[i] == t)
         {
            id[i] = id[q];
            elemUni += 3;
            flag++;
         }
      }
      if (flag != 0)
      {
         nConjuntos--;
      }
      links_cnt++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }

   for (i = 0; i < N; i++)
   {
      for (k = 0, j = 0; k < N; k++)
      {
         if (id[k] == i)
         {
            if (j == 0)
            {
               printf("%d", k);
            }
            else
            {
               printf("-%d", k);
            }
            j++;
         }
      }
      if (j != 0)
         printf("\n");
   }

   printf("Número de conjuntos: %d\n\n", nConjuntos);

   printf("QF: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("Find:  %ld\nUnion: %ld\nTotal: %ld\n", elemProc, elemUni, elemProc + elemUni + elem);
   return;
}

/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *****************************************************************************/

void quick_union(int *id, int N, FILE *fp, int quietOut)
{

   int i, j, p, q;
   int pairs_cnt = 0; /* connection pairs counter */
   int links_cnt = 0; /* number of links counter */
   elemProc = 0;
   elemUni = 0;
   elem = 0;
   int nConjuntos = N;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++)
   {
      id[i] = i;
      elem++;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2)
   {
      pairs_cnt++;
      i = p;
      j = q;

      /* do search first */
      while (i != id[i])
      {
         i = id[i];
         elemProc += 2;
      }
      while (j != id[j])
      {
         j = id[j];
         elemProc += 2;
      }
      if (i == j)
      {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      id[i] = j;
      nConjuntos--;
      elemUni++;
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("Número de conjuntos: %d\n", nConjuntos);
   printf("Find:  %ld\nUnion: %ld\nTotal: %ld\n", elemProc, elemUni, elemProc + elemUni + elem);
}

/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE *fp, int quietOut)
{

   int i, j, p, q;
   int *sz = (int *)malloc(N * sizeof(int));
   int pairs_cnt = 0; /* connection pairs counter */
   int links_cnt = 0; /* number of links counter */
   elemProc = 0;
   elemUni = 0;
   elem = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++)
   {
      id[i] = i;
      sz[i] = 1;
      elem += 2;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2)
   {
      pairs_cnt++;

      /* do search first */
      for (i = p; i != id[i]; i = id[i])
         elemProc += 2;
      for (j = q; j != id[j]; j = id[j])
         elemProc += 2;

      if (i == j)
      {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      if (sz[i] < sz[j])
      {
         id[i] = j;
         sz[j] += sz[i];
         elemUni += 5;
      }
      else
      {
         id[j] = i;
         sz[i] += sz[j];
         elemUni += 5;
      }
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("WQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("Find:  %ld\nUnion: %ld\nTotal: %ld\n", elemProc, elemUni, elemProc + elemUni + elem);

   free(sz);
   return;
}

/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE *fp, int quietOut)
{
   int i, j, p, q, t, x;
   int *sz = (int *)malloc(N * sizeof(int));
   int pairs_cnt = 0; /* connection pairs counter */
   int links_cnt = 0; /* number of links counter */
   elemProc = 0;
   elemUni = 0;
   elem = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++)
   {
      id[i] = i;
      sz[i] = 1;
      elem += 2;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2)
   {
      pairs_cnt++;

      /* do search first */
      for (i = p; i != id[i]; i = id[i])
         elemProc += 2;
      for (j = q; j != id[j]; j = id[j])
         elemProc += 2;

      if (i == j)
      {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      if (sz[i] < sz[j])
      {
         id[i] = j;
         sz[j] += sz[i];
         t = j;
         elemUni += 5;
      }
      else
      {
         id[j] = i;
         sz[i] += sz[j];
         t = i;
         elemUni += 5;
      }
      links_cnt++;

      /* retrace the path and compress to the top */
      for (i = p; i != id[i]; i = x)
      {
         x = id[i];
         id[i] = t;
         elemUni += 3;
      }
      for (j = q; j != id[j]; j = x)
      {
         x = id[j];
         id[j] = t;
         elemUni += 3;
      }
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("CWQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("Find:  %ld\nUnion: %ld\nTotal: %ld\n", elemProc, elemUni, elemProc + elemUni + elem);

   free(sz);
   return;
}
