/******************************************************************************
 *
 * File Name: SpMat.c
 *	      (c) 2022 LMS
 * Author:    Luis Miguel Silveira
 * Revision:  v0
 *
 * NAME
 *     SpMat - processing of matrices in sparse structure
 *
 * SYNOPSIS
 *       #include "SpMat.h"
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "SpMat.h"

typedef struct _SpMat
{
  int nrow, ncol, nnz;
  double *val;
  int *col;
  int *rowSt;
} SpMat;

/******************************************************************************
 * deleteSpMat()
 *
 * Arguments: spmat - pointer to sparse matrix data structure
 * Returns: (void)
 * Side-Effects: sparse matrix allocated space is freed
 *
 * Description: frees the space from the sparse matrix and associated tables
 *
 *****************************************************************************/

void deleteSpMat(SpMat *spmat)
{
  free(spmat->rowSt);
  free(spmat->col);
  free(spmat->val);
  free(spmat);
}

/******************************************************************************
 * readSpMatFile()
 *
 * Arguments: fname - name of file with sparse matrix description
 * Returns: (void)
 * Side-Effects: allocates and fills all data for sparse matrix
 *
 * Description: stores data for sparse matrix in internal data structures
 *
 *****************************************************************************/

SpMat *readSpMatFile(FILE *fp, char *fname)
{
  int pos, numLine, nrow, ncol, nnz, line, col, value;
  SpMat *spmat;

  /* check that the file has the right header */
  if (fscanf(fp, "%d %d %d", &nrow, &ncol, &nnz) != 3)
  {
    fclose(fp);
    fprintf(stderr, "could not read header info from file %s.\n", fname);
    return (NULL);
  }

  /* header is ok, assume data is well described, allocate space */
  spmat = (SpMat *)malloc(sizeof(SpMat));
  if (spmat == (SpMat *)NULL)
  {
    fclose(fp);
    fprintf(stderr, "could not allocate sparse matrix structure.\n");
    return (NULL);
  }

  /* fill header of sparse matrix */
  spmat->nrow = nrow;
  spmat->ncol = ncol;
  spmat->nnz = nnz;

  /* allocate tables with checks */
  spmat->val = (double *)malloc(sizeof(double) * spmat->nnz);
  if (spmat->val == (double *)NULL)
  {
    fclose(fp);
    fprintf(stderr,
            "could not allocate value data for sparse matrix structure.\n");
    return (NULL);
  }
  spmat->col = (int *)malloc(sizeof(int) * spmat->nnz);
  if (spmat->col == (int *)NULL)
  {
    fclose(fp);
    fprintf(stderr,
            "could not allocate column data for sparse matrix structure.\n");
    return (NULL);
  }
  spmat->rowSt = (int *)malloc(sizeof(int) * spmat->nrow);
  if (spmat->rowSt == (int *)NULL)
  {
    fclose(fp);
    fprintf(stderr,
            "could not allocate rowSt data for sparse matrix structure.\n");
    return (NULL);
  }
  /* initialize rowSt for the case where we have an empty row (unlikely) */
  for (pos = 0; pos < nrow; pos++)
    spmat->rowSt[pos] = -1;

  /* Ok, now we are ready to read the matriz data and save it */
  for (pos = 0, numLine = 0; pos < nnz; pos++)
  {
    if (fscanf(fp, "%d %d %d", &line, &col, &value) != 3)
    {
      fclose(fp);
      deleteSpMat(spmat);
      fprintf(stderr, "could not read matrix info from file %s.\n", fname);
      return (NULL);
    }
    /* sanity check */
    if ((line < 0) || (line >= nrow) || (col < 0) || (col >= ncol))
    {
      fclose(fp);
      deleteSpMat(spmat);
      fprintf(stderr, "matrix data is not within bounds.\n");
      return (NULL);
    }

    /* save information for this element */
    spmat->val[pos] = value;
    spmat->col[pos] = col;
    /* are we at the start of a new row? */
    if (line == numLine)
    {
      /* this is the first element for this row, save the start position */
      spmat->rowSt[numLine] = pos;
      numLine++;
    }
    else if (line > numLine)
    {
      /* this is in the unlikely event that we were expecting elements for
         a given row and there were none and we now have elements for a row
         beyond that; this situation is unlikely is most applications */
      spmat->rowSt[line] = pos;
      numLine = line + 1;
    }
  }
  /* add extra info to last index of rowSt */
  spmat->rowSt[spmat->nrow] = spmat->nnz;

  return (spmat);
}

/******************************************************************************
 * printSpMatFile()
 *
 * Arguments: spmat - pointer to sparse matrix data structure
 * Returns: (void)
 * Side-Effects: (none)
 *
 * Description: prints sparse matrix structure in readable format similar
 *              to the one used to read from file
 *
 *****************************************************************************/

void printSpMat(SpMat *spmat)
{
  int pos = 0, curline = 0;

  fprintf(stdout, "%d  %d  %d\n", spmat->nrow, spmat->ncol, spmat->nnz);

  for (curline = 0; curline < spmat->nrow; curline++)
  {
    if (spmat->rowSt[curline] == -1)
      continue;
    for (; (pos < spmat->nnz) && (pos < spmat->rowSt[curline + 1]); pos++)
    {
      fprintf(stdout,
              "%d  %d  %lf\n", curline, spmat->col[pos], spmat->val[pos]);
    }
  }

  return;
}

/******************************************************************************
 * sumLinesSpMat()
 *
 * Arguments: spmat - pointer to sparse matrix data structure
 * Returns: (void)
 * Side-Effects: (none)
 *
 * Description: prints for each line the sum of the elements of that line
 *
 *****************************************************************************/

void sumLinesSpMat(SpMat *spmat)
{
  int line, pos;
  double sum;

  /* for each line of the matrix sum all its elements and print the accumulated
     value */
  for (line = 0; line < spmat->nrow; line++)
  {
    sum = 0.0;
    /* deal with lines with no elements */
    if (spmat->rowSt[line] == -1)
    {
      fprintf(stdout, "line=%d  sum=---\n", line);
      continue;
    }

    /* now pick all elements from that line and add them all */

    /**************  COMPLETE FOR PROBLEM 3.2  ************/;
    for (pos = spmat->rowSt[line]; pos < spmat->rowSt[line + 1]; pos++)

      /* ???  */
      sum += spmat->val[pos];
    /* now printf the result */
    fprintf(stdout, "line=%d  sum=%lf\n", line, sum);
  }

  return;
}

/******************************************************************************
 * SpMatXXXX()
 *
 * Arguments: spmat - pointer to sparse matrix data structure
 * Returns: return some double precision value
 * Side-Effects: (none)
 *
 * Description: do as expected
 *
 *****************************************************************************/

double SpMatXXX(SpMat *spmat)
{
  double result;

  result = 0;

  /**************  COMPLETE FOR PROBLEM 3.3  ************/;

  return (result);
}
