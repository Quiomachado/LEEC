/******************************************************************************
 *
 * File Name: SpMat.h
 *	      (c) 2022 LMS
 * Author:    Luis Miguel Silveira
 * Revision:  v0
 *
 * NAME
 *     SpMat - definition of sparse matrix structure
 *
 * SYNOPSIS
 *
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#ifndef SpMatHeader
#define SpMatHeader



typedef struct _SpMat SpMat;


void deleteSpMat(SpMat*);

SpMat *readSpMatFile (FILE *, char *);

void printSpMat(SpMat*);

void sumLinesSpMat(SpMat*);

double SpMatXXX(SpMat*);

#endif

