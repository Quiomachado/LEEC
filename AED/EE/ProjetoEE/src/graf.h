#ifndef _GRAF_H_
#define _GRAF_H_

typedef struct node_struct node;
typedef struct graph_struct graph;

node *NEW(int v, double wt, node *next);
graph *GRAPHinit(int V);
void GRAPHinsertE(graph *G, int ver1, int ver2, int wt);
void GRAPHremoveE(graph *G, int ver1, int ver2);

#endif