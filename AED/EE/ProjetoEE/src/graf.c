#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

#include "graf.h"

struct GRAPH {
    double **adj;
    int *st;
    int *fr;
    double *val;
    int E;
    int V;
};

int GetV (graph *G) {
    return G->V;
}

int GetE (graph *G) {
    return G->E;
}

graph* GRAPHinit (int V) {
    graph *G = NULL;
    int i, k;
    G = (graph *)malloc(sizeof(graph));
    G->adj = (double **)malloc(sizeof(double *) * V);
    G->val = (double *)malloc(sizeof(double) * (V + 1));
    G->fr = (int *)malloc(sizeof(int) * V);
    G->st = (int *)malloc(sizeof(int) * V);
    G->E = 0;
    G->V = V;
    for (i = 0; i <= V; i++) {
        G->val[i] = DBL_MAX;
        if (i != V) {
            G->fr[i] = i;
            G->st[i] = -1;
            G->adj[i] = (double *)malloc(sizeof(double) * V);
            for (k = 0; k < V; k++) {
                G->adj[i][k] = DBL_MAX;
            }
        }
    }
    return G;
}

void GRAPHinsertE (graph *G, int ver1, int ver2, double wt) {
    if (G->adj[ver1][ver2] == DBL_MAX) G->E++;
    G->adj[ver1][ver2] = wt;
    G->adj[ver2][ver1] = wt;
}

void GRAPHremoveE (graph *G, int ver1, int ver2) {
    if (G->adj[ver1][ver2] != DBL_MAX) {
        G->adj[ver1][ver2] = DBL_MAX;
        G->adj[ver2][ver1] = DBL_MAX;
        G->E--;
    }
}

void GRAPHDestroy (graph *G) {
    int i;
    for (i = 0; i < G->V; i++) {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G->fr);
    free(G->val);
    free(G->st);
    free(G);
}







