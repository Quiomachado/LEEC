#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

#include "graf.h"

#define P G->adj[v][w]

struct GRAPH {
    double **adj;
    int *st;
    int *fr;
    double *val;
    int E;
    int V;
    double mstWT;
};

int GetV (graph *G) {
    return G->V;
}

int GetE (graph *G) {
    return G->E;
}

double GetMstWt (graph *G) {
    return G->mstWT;
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
    G->mstWT = 0;
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


void GRAPHmst (graph *G) {
    int v, w, min;

    min = 0; G->st[0] = 0; G->val[G->V] = DBL_MAX;
    v = 0;
    while (min != G->V) {
        v = min;
        if (G->val[min] != DBL_MAX)
            G->mstWT += G->val[min];
        G->st[v] = G->fr[v];
        for (w = 0, min = G->V; w < G->V; w++) {
            if (G->st[w] == -1) {
                if (P < G->val[w]) {
                    G->val[w] = P;
                    G->fr[w] = v;
                }
                if (G->val[w] < G->val[min]) min = w;
            }
        }
    } 
}

void GRAPHprintMst (graph *G, FILE *fp_out, char *mode) {
    int i;
    fprintf(fp_out, "%d %d %s %d %.2f\n", G->V, G->E, mode, G->V - 1, G->mstWT);
    for (i = 1; i < G->V; i++)
        fprintf(fp_out, "%d %d %.2f\n", i + 1, G->st[i] + 1, G->adj[i][G->st[i]]);
}

