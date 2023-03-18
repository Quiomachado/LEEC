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
    node **adj;
};

struct edge_struct
{
    int v;
    int w;
    double wt;
};

node *NEW(int v, double wt, node *next)
{
    node *x = (node *)malloc(sizeof(node));
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

graph *GRAPHinit(int V)
{
    int v;
    graph *G = (graph *)malloc(sizeof(graph));
    G->V = V;
    G->E = 0;
    G->adj = (node **)malloc(V * sizeof(node *));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertE(graph *G, edge *e)
{
    int v = e->v;
    int w = e->w;
    double wt = e->wt;
    G->adj[v] = NEW(w, wt, G->adj[v]);
    G->adj[w] = NEW(v, wt, G->adj[w]);
    G->E++;
}

void GRAPHremoveE(graph *G, edge *e)
{
    int v = e->v;
    int w = e->w;
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
    G->E--;
}