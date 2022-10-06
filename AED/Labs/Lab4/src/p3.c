/*
 *  File name: p3-pub.c
 *
 *  Author: 2022/2023 P1 AED Team
 *
 *  Release date: 2022/10/05
 *
 *  Description: See the handout.
 *
 *  Version: 1.0
 *
 *  Change log:
 *    V1.0 - 2022/10/05 -  First version
 *
 */



/* Header Inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "SpMat.h"



/*
 * Function:
 *   main
 */
int main(int argc, char *argv[])
{
  FILE *fp;
  char *fname;
  int choice;
  int exitProcessing = 0;
  double result;
  SpMat *spmat = (SpMat*) NULL;

  /* Check number of arguments */
  if(argc < 2) {
    printf("Usage: LAIp3 filename\n");
    exit(1);
  }

  /* Open input file */
  fname = argv[1];

  /* check that the file can be opened */
  if ((fp = fopen(fname, "r")) == NULL) {
    fprintf(stderr, "file %s could not be opened.\n", fname);
    exit(2);
  }

  while (!exitProcessing) {

    fprintf(stdout, "Welcome to the LAIp3 interface to sparse matrices.\n");
    fprintf(stdout, "\t You can choose between the following commands:\n");
    fprintf(stdout, "\t\t 0 - exit\n");
    fprintf(stdout, "\t\t 1 - read sparse matrix from file %s\n", fname);
    fprintf(stdout, "\t\t 2 - print sparse matrix read from file %s\n", fname);
    fprintf(stdout, "\t\t 3 - print sum of each line in file\n");
    fprintf(stdout, "\t\t 4 - compute what is required in P3.3\n\n");
    fprintf(stdout, "\tWhat is your option? ");

    (void)fscanf(stdin, "%d", &choice);

    /* what is the command */
    switch (choice) {
    case 0:
      /* exit */
      exitProcessing = 1;
      break;
    case 1:
      spmat = readSpMatFile(fp, fname);
      break;
    case 2:
      if (spmat == (SpMat*) NULL) {
        fprintf(stderr, "need to read sparse matrix first.\n");
      } else {
        printSpMat(spmat);
      }
      break;
    case 3:
      if (spmat == (SpMat*) NULL) {
        fprintf(stderr, "need to read sparse matrix first.\n");
      } else {
        sumLinesSpMat(spmat);
      }
      break;
    case 4:
      if (spmat == (SpMat*) NULL) {
        fprintf(stderr, "need to read sparse matrix first.\n");
      } else {
        result = SpMatXXX(spmat);
        fprintf(stdout, "result=%lf\n", result);
      }
      break;
    default:
      printf("error: unknown command '%d'\n", choice);
      break;
     }

  }

  /* Close input file                                             */
  fclose(fp);

  /* Free memory allocated to vector                              */
  if (spmat != (SpMat*)NULL) {
    deleteSpMat(spmat);
  }

  return 0;
}




