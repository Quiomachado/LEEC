/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-15
 *
 * NAME
 *   connectivity.h
 *
 * DESCRIPTION
 *   Function declarations for connectivity problem solvers
 *
 * COMMENTS
 *
 ******************************************************************************/

#ifndef __connectivity__
#define __connectivity__

void quick_find(int *id, int N, FILE * fp, int quietOut);
void quick_union(int *id, int N, FILE * fp, int quietOut);
void weighted_quick_union(int *id, int N, FILE * fp, int quietOut);
void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut);

#endif    /* __connectivity__ */
