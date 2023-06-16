#ifndef __GRAF_H__
#define __GRAF_H__

#include <stdio.h>

typedef struct GRAPH graph;

int GetV (graph *G);
int GetE (graph *G);
double GetMstWt (graph *G);
graph* GRAPHinit (int V);
void GRAPHinsertE (graph *G, int ver1, int ver2, double wt);
void GRAPHremoveE (graph *G, int ver1, int ver2);
void GRAPHDestroy (graph *G);
void GRAPHmst (graph *G);
void GRAPHprintMst (graph *G, FILE *fp_out, char *mode);

#endif
