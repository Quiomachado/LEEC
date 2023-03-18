#ifndef _GRAF_H_
#define _GRAF_H_

typedef struct node_struct node;
typedef struct graph_struct graph;

node *NEW(int v, double wt, node *next);
node *GetNext(node *t);
int GetV(node *t);
double GetWt(node *t);
node *GetAdj(graph *G, int v);
int GetVCount(graph *G);
int GetECount(graph *G);
int GetDegree(graph *G, int v);
graph *GRAPHinit(int V);
void GRAPHinsertE(graph *G, int ver1, int ver2, double wt);
void GRAPHremoveE(graph *G, int ver1, int ver2);
void GRAPHDestroy(graph *G);

#endif