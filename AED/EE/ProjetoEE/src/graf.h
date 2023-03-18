#ifndef _GRAF_H_
#define _GRAF_H_

typedef struct node_struct node;
typedef struct graph_struct graph;
typedef struct edge_struct edge;

node *NEW(int v, double wt, node *next);
graph *GRAPHinit(int V);
void GRAPHinsertE(graph *G, edge *e);
void GRAPHremoveE(graph *G, edge *e);

#endif