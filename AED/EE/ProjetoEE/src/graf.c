#include "graf.h"

#include <stdio.h>
#include <stdlib.h>

struct node_struct
{
    int v;
    double wt;
    node *next;
};

struct graph_struct
{
    int V;
    int E;
    int *degree;
    node **adj;
};

node *GetNext(node *t)
{
    return t->next;
}

int GetV(node *t)
{
    return t->v;
}

double GetWt(node *t)
{
    return t->wt;
}

node *GetAdj(graph *G, int v)
{
    return G->adj[v];
}

int GetDegree(graph *G, int v)
{
    return G->degree[v];
}

int GetVCount(graph *G)
{
    return G->V;
}

int GetECount(graph *G)
{
    return G->E;
}

node *NEW(int v, double wt, node *next)
{
    node *x = (node *)malloc(sizeof(node));
    if (x == NULL)
        exit(0);
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

graph *GRAPHinit(int V)
{
    int v;
    graph *G = (graph *)malloc(sizeof(graph));
    if (G == NULL)
        exit(0);
    G->V = V;
    G->E = 0;
    G->adj = (node **)malloc((V + 1) * sizeof(node *));
    if (G->adj == NULL)
        exit(0);
    G->degree = (int *)malloc((V + 1) * sizeof(int));
    if (G->degree == NULL)
        exit(0);
    for (v = 0; v <= V; v++)
    {
        G->adj[v] = NULL;
        G->degree[v] = 0;
    }
    return G;
}

void GRAPHinsertE(graph *G, int ver1, int ver2, double wt)
{
    G->adj[ver1] = NEW(ver2, wt, G->adj[ver1]);
    G->adj[ver2] = NEW(ver1, wt, G->adj[ver2]);
    G->degree[ver1]++;
    G->degree[ver2]++;
    G->E++;
}

void GRAPHremoveE(graph *G, int ver1, int ver2)
{
    int v = ver1;
    int w = ver2;
    node *t;
    node *prev = NULL;
    for (t = G->adj[v]; t != NULL; t = t->next)
    {
        if (t->v == w)
        {
            if (prev == NULL)
                G->adj[v] = t->next;
            else
                prev->next = t->next;
            free(t);
            break;
        }
        prev = t;
    }
    prev = NULL;
    for (t = G->adj[w]; t != NULL; t = t->next)
    {
        if (t->v == v)
        {
            if (prev == NULL)
                G->adj[w] = t->next;
            else
                prev->next = t->next;
            free(t);
            break;
        }
        prev = t;
    }
    G->degree[v]--;
    G->degree[w]--;
    G->E--;
}

void GRAPHDestroy(graph *G)
{
    int v;
    node *t, *next;
    for (v = 0; v <= G->V; v++)
    {
        for (t = G->adj[v]; t != NULL; t = next)
        {
            next = t->next;
            free(t);
        }
    }
    free(G->adj);
    free(G->degree);
    free(G);
}