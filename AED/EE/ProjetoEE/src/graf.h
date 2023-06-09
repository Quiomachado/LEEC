#ifndef __GRAF_H__
#define __GRAF_H__

typedef struct GRAPH graph;

int GetV (graph *G);
int GetE (graph *G);
graph* GRAPHinit (int V);
void GRAPHinsertE (graph *G, int ver1, int ver2, double wt);
void GRAPHremoveE (graph *G, int ver1, int ver2);
void GRAPHDestroy (graph *G);

#endif
