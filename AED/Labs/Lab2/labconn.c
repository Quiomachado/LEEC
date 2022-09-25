/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-19
 *
 * NAME
 *   labconn.c
 *
 * DESCRIPTION
 *   Main program to call the different connectivity algorithms.
 *   Requires test data file name as argument.
 *   Option "-q" for reduced output in interactive mode.
 *   Option "-1/2/3/4" for for single run in batch, quiet mode.
 *
 * COMMENTS
 *  Batch mode added experimentally. Todo: rework logic, fix repeated code
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "connectivity.h"

void usage(char *);

int quietOut = 0;


int main(int argc, char *argv[])
{
   int BatchMode = 0;
   int N, *id, choice = 0;
   int opt, find = 1;
   char line[32];
   FILE *fp;

   /* must have at least one argument besides the exec name */
   if (argc < 2) {
      usage(argv[0]);
      exit(0);
   }

   while ((opt = getopt(argc, argv, "1234q")) != -1) {
      find++;
      switch (opt) {
      case 'q':  /* quiet on the output */
         quietOut = 1;
         break;
      case '1':       /* batch mode QF */
         BatchMode = 1;
         break;
      case '2':       /* batch mode QU */
         BatchMode = 2;
         break;
      case '3':       /* batch mode WQU */
         BatchMode = 3;
         break;
      case '4':       /* batch mode WCQU */
         BatchMode = 4;
         break;
      default: /* '?' */
         usage(argv[0]);
         exit(0);
      }
   }

   /* open file and read array size */
   fp = (FILE *) fopen(argv[find], "r");
   if (fp == (FILE *) NULL) {
      fprintf(stderr, "File %s cannot be read.  Please correct.\n", argv[1]);
      exit(0);
   }
   if (fscanf(fp, "%d", &N) != 1) {
      fprintf(stderr,
              "Need to get N (number of elements) from first line of file\n");
      exit(0);
   }
   if (N > 0) {
      id = (int *) calloc(N, sizeof(int));
      if (id == ((int*)NULL)) {
         fprintf(stderr, "Could not allocate id[] array. Exiting.\n");
         exit(1);
      }
   } else {
      fprintf(stderr,
              "Non positive number of elements unexpected. Exiting.\n");
      exit(1);
   }

   /* exec once in batch mode */
   if (BatchMode > 0){
      fprintf(stdout, "File: %s\n", argv[find]);  /* input file */
      quietOut = 1;
      switch (BatchMode) {
      case 1:
         quick_find(id, N, fp, quietOut);
         break;
      case 2:
         quick_union(id, N, fp, quietOut);
         break;
      case 3:
         weighted_quick_union(id, N, fp, quietOut);
         break;
      case 4:
         compressed_weighted_quick_union(id, N, fp, quietOut);
         break;
      }
      free(id);
      fclose(fp);
      exit(0);
   }

   /* in interactive mode executive while asked;
    * query which algorithm to use */
   while (choice >= 0) {

      fprintf(stdout, "\n\tConnectivity Problem\n\nChoose an algorithm:\n");
      fprintf(stdout, "\t1 - Quick Find\n");
      fprintf(stdout, "\t2 - Quick Union\n");
      fprintf(stdout, "\t3 - Weighted Quick Union\n");
      fprintf(stdout, "\t4 - Weighted Quick Union with Compression\n");
      fprintf(stdout, "\n");
      fprintf(stdout, "\t0 - Exit\n");

      do {
         choice = -1;
         if (feof(stdin)){   /* input ceased, quit menu loop */
            fprintf(stdout, "\n");
            choice = 0;
            break;
         }
         fprintf(stdout, "\nYour choice: (1,2,3,4,0) ");
         if (fscanf(stdin, "%d", &choice) != 1) {
            continue;
         }
      } while (choice < 0 || choice > 4);

      if (choice == 0)
         break;

      switch (choice) {
      case 1:
         quick_find(id, N, fp, quietOut);
         break;
      case 2:
         quick_union(id, N, fp, quietOut);
         break;
      case 3:
         weighted_quick_union(id, N, fp, quietOut);
         break;
      case 4:
         compressed_weighted_quick_union(id, N, fp, quietOut);
         break;
      default:
         fprintf(stderr, "Yikes\n");
         exit(1);
      }
      /* rewind the file; reread size (not needed but must consume input) */
      rewind(fp);
      fscanf(fp, "%d", &N);
   }

   free(id);
   fclose(fp);
   exit(0);
}


void usage(char *prog)
{
   fprintf(stdout,
           "usage: %s [-q] filename      interactive use, -q quiet\n", prog);
   fprintf(stdout,
           "   or: %s  -N  filename      a single run of option N [1..4]\n",
           prog);
   return;
}
