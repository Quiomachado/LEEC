#include "graf.h"

#include <stdio.h>
#include <stdlib.h>

// structure for node with the vertice number, wt associated with the connection
struct node_struct
{
    int v;
    double wt;
    node *next;
};

// structure for the linked list graph with number of vertices, edges and degree for each vertice
struct graph_struct
{
    int V;
    int E;
    int *degree;
    node **adj;
};

// function to allow you to get the next node in the linked list
node *GetNext(node *t)
{
    return t->next;
}

// function to get the vertice number
int GetV(node *t)
{
    return t->v;
}

// function to get the weight associated with the connection to the vertice
double GetWt(node *t)
{
    return t->wt;
}

// function to get the linked list of the adjacent vertices
node *GetAdj(graph *G, int v)
{
    return G->adj[v];
}

// function to get the degree of the vertice v
int GetDegree(graph *G, int v)
{
    return G->degree[v];
}

// function to get the number of vertices
int GetVCount(graph *G)
{
    return G->V;
}

// function to get the number of edges
int GetECount(graph *G)
{
    return G->E;
}

// function to create a new node and allocate the memory
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

// function to initialize the graph and it's memmory
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

// function to insert a new edge in the graph
void GRAPHinsertE(graph *G, int ver1, int ver2, double wt)
{
    G->adj[ver1] = NEW(ver2, wt, G->adj[ver1]);
    G->adj[ver2] = NEW(ver1, wt, G->adj[ver2]);
    G->degree[ver1]++;
    G->degree[ver2]++;
    G->E++;
}

//fucntion to remove an edge from the graph
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

// function to free the graph
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

// function to initialize the graph as a table
double **TableGRAPHInit(double **G, int V)
{
    int i;
    G = (double **)malloc(sizeof(double*) * V);
    if (G == NULL)
        exit(0);
    for (i = 0; i < V; i++)
    {
        G[i] = (double *)calloc(1, sizeof(double) * V);
        if (G[i] == NULL)
            exit(0);
    }
    return G;
}

// function to insert a new "edge" in the table graph
double **TableGRAPHInsert(double **G, int id1, int id2, double wt)
{
    G[id1 - 1][id2 - 1] = 1;
    G[id2 - 1][id1 - 1] = 1;
    return G;
}

// function to free the table graph
void TableGRAPHDelete(double **G, int V)
{
    int i;
    for (i = 0; i < V; i++)
        free(G[i]);
    free(G);
}
