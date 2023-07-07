#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include "graf.h"

#define P G->adj[v][w]

struct NODE {
    int v1;
    int v2;
    double wt;
    node *next;
};

struct GRAPH {
    double **adj;
    int *st;
    int *fr;
    double *val;
    int mstCount;
    int E;
    int V;
    double mstWT;
    node *mst;
};

int GetMstCount (graph *G) {
    return G->mstCount;
}

int GetV (graph *G) {
    return G->V;
}

int GetE (graph *G) {
    return G->E;
}

double GetMstWt (graph *G) {
    return G->mstWT;
}

unsigned int SizeofNode () {
    return sizeof(node);
}

node *GetMst (graph *G) {
    return G->mst;
}

int GetMstI (graph *G, int i) {
    return G->st[i];
}

node *CopyNode (node *old_head, node *head) {
    old_head->v1 = head->v1;
    old_head->v2 = head->v2;
    old_head->wt = head->wt;
    old_head->next = head->next;
    free(head);
    return old_head;
}

graph* GRAPHinit (int V) {
    graph *G = NULL;
    int i, k;
    G = (graph *)malloc(sizeof(graph));
    if (G == NULL)
        exit(0);
    G->adj = (double **)malloc(sizeof(double *) * V);
    if (G->adj == NULL)
        exit(0);
    G->val = (double *)malloc(sizeof(double) * (V + 1));
    if (G->val == NULL)
        exit(0);
    G->fr = (int *)malloc(sizeof(int) * V);
    if (G->fr == NULL)
        exit(0);
    G->st = (int *)malloc(sizeof(int) * V);
    if (G->st == NULL)
        exit(0);
    G->mst = NULL;
    G->E = 0;
    G->V = V;
    G->mstWT = 0;
    for (i = 0; i < V; i++) {
        G->adj[i] = (double *)malloc(sizeof(double) * V);
        if (G->adj[i] == NULL)
            exit(0);
        for (k = 0; k < V; k++) {
            G->adj[i][k] = DBL_MAX;
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
    node *tmp, *next;
    for (i = 0; i < G->V; i++) {
        free(G->adj[i]);
    }
    for (tmp = G->mst; tmp != NULL; tmp = next) {
        next = tmp->next;
        free(tmp);
    }
    free(G->adj);
    free(G->fr);
    free(G->val);
    free(G->st);
    free(G);
}

void DESTROYoldSt (node *old_st) {
    node *tmp;
    for (old_st = old_st; old_st != NULL; old_st = tmp) {
        tmp = old_st->next;
        free (old_st);
    }
}

void dfs (double **adj, int vertice, int *visited, int num_vertices) {
    int i;
    visited[vertice] = 1;

    for (i = 0; i < num_vertices; i++) {
        if (adj[vertice][i] != DBL_MAX && !visited[i])
            dfs(adj, i, visited, num_vertices);
    }
}

int GRAPHConnectivity (graph *G) {
    int V, i;
    int *visited;
    V = G->V;
    visited = (int *)malloc(sizeof(int) * V);
    for (i = 0; i < V; i++)
        visited[i] = 0;
    
    dfs(G->adj, 0, visited, V);
    
    for (i = 0; i < V; i++) {
        if (!visited[i]) {
            free(visited);
            return 0;
        }
    }

    free(visited);
    return 1;
}

node *NEW(int v1, int v2, double wt) {
    node *x = (node *)malloc(sizeof(node));
    if (x == NULL)
        exit(0);
    if (v1 <= v2) {
        x->v1 = v1;
        x->v2 = v2;
    } else {
        x->v1 = v2;
        x->v2 = v1;
    }
    x->wt = wt;
    x->next = NULL;
    return x;
}

void MSTInsertSorted (graph *G, int v1, int v2, double wt) {
    node *current, *new;
    node *head;
    if (v1 == 1 && v2 == 1)
        return;
    head = G->mst;
    
    new = NEW(v1, v2, wt);

    if (head == NULL || (head->v1 >= new->v1 && head->v2 > new->v2)) {
        new->next = head;
        head = new;
    }
    else {
        current = head;
        while (current->next != NULL && current->next->v1 < new->v1) {
            current = current->next;
        }
        while (current->next != NULL && current->next->v1 == new->v1 && current->next->v2 < new->v2)
            current = current->next;
        new->next = current->next;
        current->next = new;
    }
    G->mst = head;
}

void GRAPHmst (graph *G, int exclude) {
    int v, w, min, i;
    G->mstCount = -1;
    G->mst = NULL;

    for (i = 0; i <= G->V; i++) {
        G->val[i] = DBL_MAX;
        if (i != G->V) {
            G->fr[i] = i;
            G->st[i] = -1;
        }
    }

    min = 0; G->st[0] = 0; G->val[G->V] = DBL_MAX;
    v = 0;

    while (min != G->V) {
        v = min;
        if (v == exclude)
            continue;
        if (G->val[min] != DBL_MAX)
            G->mstWT += G->val[min];
        G->st[v] = G->fr[v];
        MSTInsertSorted(G, v + 1, G->st[v] + 1, G->val[min]);
        G->mstCount++;
        for (w = 0, min = G->V; w < G->V; w++) {
            if (w == exclude)
                continue;
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
    node *tmp;
    for (tmp = G->mst; tmp != NULL; tmp = tmp->next)
        fprintf(fp_out, "%d %d %.2f\n", tmp->v1, tmp->v2, tmp->wt);
}

void GRAPHmstDiff (graph *G, FILE *fp_out, node *old_st) {
    node *t1, *t2;
    t1 = G->mst;
    t2 = old_st;
    while (t1 != NULL && t2 != NULL) {
        if (t1->v1 == t2->v1 && t1->v2 == t2->v2) {
            t1 = t1->next;
            t2 = t2->next;
        }
        else if (t1->v1 < t2->v1 || (t1->v1 == t2->v1 && t1->v2 < t2->v2)) {
            fprintf(fp_out, "%d %d %.2f\n", t1->v1, t1->v2, t1->wt);
            t1 = t1->next;
        }
        else {
            t2 = t2->next;
        }
    }
    while (t1 != NULL) {
        fprintf(fp_out, "%d %d %.2f\n", t1->v1, t1->v2, t1->wt);
        t1 = t1->next;
    }
}

int CheckEdge (graph *G, int v1, int v2) {
    int tmp;
    node *t1;
    if (v2 < v1) {
        tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    
    t1 = G->mst;
    while (t1 != NULL) {
        if ((t1->v1 == v1 && t1->v2 == v2) || (t1->v1 == v2 && t1->v2 == v1)) {
            return 1;
        }
        t1 = t1->next;
    }
    return 0;
}
