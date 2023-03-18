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

void GRAPHinsertE(graph *G, int ver1, int ver2, int wt)
{
    G->adj[ver1] = NEW(ver2, wt, G->adj[ver1]);
    G->adj[ver2] = NEW(ver1, wt, G->adj[ver2]);
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
    G->E--;
}

void GraphDestroy(graph *G)
{
    int v;
    node *t, *next;
    for (v = 0; v < G->V; v++)
    {
        for (t = G->adj[v]; t != NULL; t = next)
        {
            next = t->next;
            free(t);
        }
    }
    free(G->adj);
    free(G);
}