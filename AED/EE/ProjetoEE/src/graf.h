#ifndef __GRAF_H__
#define __GRAF_H__

typedef struct NODE node;
typedef struct GRAPH graph;

#include <stdio.h>

int GetV (graph *G);
int GetE (graph *G);
double GetMstWt (graph *G);
unsigned int SizeofNode ();
node *CopyNode (node *old_head, node *head);
node *GetMst (graph *G);
int GetMstI (graph *G, int i);
graph* GRAPHinit (int V);
void GRAPHinsertE (graph *G, int ver1, int ver2, double wt);
void GRAPHremoveE (graph *G, int ver1, int ver2);
void GRAPHDestroy (graph *G);
void DESTROYoldSt (node *old_st);
int GRAPHConnectivity (graph *G);
void GRAPHmst (graph *G, int exclude);
void GRAPHprintMst (graph *G, FILE *fp_out, char *mode);
void GRAPHmstDiff (graph *G, FILE *fp_out, node *old_st);
int CheckEdge (graph *G, int v1, int v2);

#endif
