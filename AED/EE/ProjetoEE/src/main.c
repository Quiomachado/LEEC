#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graf.h"

// Allowed Modes
char MODES[4][3] = {"A0", "B0", "C0", "D0"};

// function to find if two vertices (id1 and id2) are adjacent and the correspondent weight associated with the adjacency
void FindAdjency(graph *G, int id1, int id2, FILE *fp_out, int mode)
{
    char mode_str[3];
    node *t = NULL;

    strcpy(mode_str, MODES[mode]);
    for (t = GetAdj(G, id1); t != NULL; t = GetNext(t))
    {
        if (GetV(t) == id2)
        {
            fprintf(fp_out, "%d %d %s %d %d %.2lf\n\n", GetVCount(G), GetECount(G), mode_str, id1, id2, GetWt(t));
            return;
        }
    }

    fprintf(fp_out, "%d %d %s %d %d %d\n\n", GetVCount(G), GetECount(G), mode_str, id1, id2, -1);
    return;
}

// function to determine if there is a clique of 3 vertices with vertice id
void DetermineClique(graph *G, int id, FILE *fp_out, int mode)
{
    char mode_str[3];
    int v1 = 0, v2 = 0, v3 = 0;
    node *t1 = NULL, *t2 = NULL, *t3 = NULL;
    strcpy(mode_str, MODES[mode]);

    for (t1 = GetAdj(G, id); t1 != NULL; t1 = GetNext(t1))
    {
        v1 = GetV(t1);
        if (GetDegree(G, v1) < 2)
            continue;
        for (t2 = GetAdj(G, v1); t2 != NULL; t2 = GetNext(t2))
        {
            v2 = GetV(t2);
            if (GetDegree(G, v2) < 2 || v2 == id)
                continue;
            for (t3 = GetAdj(G, v2); t3 != NULL; t3 = GetNext(t3))
            {
                v3 = GetV(t3);
                if (GetDegree(G, v3) < 2 || v3 == v1)
                    continue;
                if (v3 == id)
                {
                    fprintf(fp_out, "%d %d %s %d %d\n\n", GetVCount(G), GetECount(G), mode_str, id, 1);
                    return;
                }
            }
        }
    }
    fprintf(fp_out, "%d %d %s %d %d\n\n", GetVCount(G), GetECount(G), mode_str, id, 0);
    return;
}

// function too check if the clique from 3 vertices has already been checked
int checkBeenChecked(double **checked, int v1, int v2, int v3)
{
    if (checked[v1][v2] != 1 && checked[v1][v3] != 1 && checked[v2][v1] != 1 && checked[v2][v3] != 1 && checked[v3][v1] != 1 && checked[v3][v2] != 1)
        return 1;
    return 0;
}

// function to count how many cliques of 3 vertice id belongs too
void CountClique(double **G_table, int V, int E, int id, FILE *fp_out, int mode)
{
    int i, k;
    char mode_str[3];
    int count = 0;
    strcpy(mode_str, MODES[mode]);
    for (i = 0; i < V; i++)
    {
        if(G_table[id - 1][i] != 0)
        {
            for (k = 0; k < V; k++)
            {
                if (G_table[i][k] != 0 && G_table[k][id - 1] != 0)
                {
                    if (checkBeenChecked(G_table, id - 1, i, k) == 0)
                    {
                        G_table[id - 1][i] += 1;
                        G_table[id - 1][k] += 1;
                        G_table[i][id - 1] += 1;
                        G_table[i][k] += 1;
                        G_table[k][id - 1] += 1;
                        G_table[k][i] += 1;
                        count++;
                    }
                }
            }
        }
    }
    fprintf(fp_out, "%d %d %s %d %d\n\n", V, E, mode_str, id, count);
}

int main(int argc, char *argv[])
{
    int max_args = 2;
    char *file_input = NULL;
    char *file_output = NULL;
    char file_ending[9] = ".queries";
    char *aux = NULL;
    FILE *fp_in = NULL, *fp_out = NULL;
    int V = 0, E = 0, id1 = 0, id2 = 0;
    graph *G = NULL;
    int ver1 = 0, ver2 = 0;
    double wt = 0;
    char mode_str[2];
    int mode = 0;
    int edge_count = 0;
    int flag = 0;
    double **G_table = NULL;

    // Check if the number of arguments is correct
    if (argc > max_args)
    {
        exit(0);
    }

    // Get the input file name
    file_input = argv[1];
    aux = (char *)malloc(sizeof(char) * (strlen(file_input) + 1));
    if (aux == NULL)
        exit(0);
    strcpy(aux, file_input);
    aux[strlen(aux) - 8] = '\0';
    file_output = (char *)malloc(sizeof(char) * (strlen(aux) + strlen(file_ending) + 1));
    if (file_output == NULL)
        exit(0);
    sprintf(file_output, "%s%s", aux, file_ending);

    // Open the input and output files and check if they exist
    fp_in = fopen(file_input, "r");
    if (fp_in == NULL)
        exit(0);
    fp_out = fopen(file_output, "w");
    if (fp_out == NULL)
        exit(0);

    // Read the first line of the input file
    fscanf(fp_in, "%d %d %s %d", &V, &E, mode_str, &id1);
    do
    {
        flag = 0;
        // Initialize the graph
        G = GRAPHinit(V);

        // Turn the mode into an integer
        if (strcmp(mode_str, MODES[0]) == 0)
            mode = 0;
        else if (strcmp(mode_str, MODES[1]) == 0)
            mode = 1;
        else if (strcmp(mode_str, MODES[2]) == 0)
            mode = 2;
        else if (strcmp(mode_str, MODES[3]) == 0)
            mode = 3;
        else
            exit(0);

        edge_count = 0;

        // Read the rest of the input file and insert the edges into the graph
        switch (mode)
        {
        case 0:
            if (id1 > V || id1 < 1)
            {
                fprintf(fp_out, "%d %d %s %d %d\n\n", V, E, mode_str, id1, -1);
                GRAPHDestroy(G);
                flag++;
                while (edge_count < E)
                {
                    fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                    edge_count++;
                    continue;
                }
                break;
            }
            while (edge_count < E)
            {
                fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                edge_count++;
                GRAPHinsertE(G, ver1, ver2, wt);
            }
            fprintf(fp_out, "%d %d %s %d %d\n\n", V, E, mode_str, id1, GetDegree(G, id1));
            GRAPHDestroy(G);
            break;
        case 1:
            fscanf(fp_in, "%d", &id2);
            if (id1 > V || id1 < 1 || id2 > V || id2 < 1)
            {
                fprintf(fp_out, "%d %d %s %d %d %d\n\n", V, E, mode_str, id1, id2, -1);
                GRAPHDestroy(G);
                flag++;
                while (edge_count < E)
                {
                    fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                    edge_count++;
                    continue;
                }
                break;
            }
            while (edge_count < E)
            {
                fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                edge_count++;
                GRAPHinsertE(G, ver1, ver2, wt);
            }
            FindAdjency(G, id1, id2, fp_out, mode);
            GRAPHDestroy(G);
            break;
        case 2:
            if (id1 > V || id1 < 1)
            {
                fprintf(fp_out, "%d %d %s %d %d\n\n", V, E, mode_str, id1, -1);
                GRAPHDestroy(G);
                flag++;
                while (edge_count < E)
                {
                    fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                    edge_count++;
                    continue;
                }
                break;
            }
            while (edge_count < E)
            {
                fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                edge_count++;
                GRAPHinsertE(G, ver1, ver2, wt);
            }
            DetermineClique(G, id1, fp_out, mode);
            GRAPHDestroy(G);
            break;
        case 3:
            GRAPHDestroy(G);
            G_table = TableGRAPHInit(G_table, V);
            if (id1 > V || id1 < 1)
            {
                fprintf(fp_out, "%d %d %s %d %d\n\n", V, E, mode_str, id1, -1);
                flag++;
                while (edge_count < E)
                {
                    fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                    edge_count++;
                    continue;
                }
                break;
            }
            while (edge_count < E)
            {
                fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                edge_count++;
                TableGRAPHInsert(G_table, ver1, ver2, wt);
            }
            CountClique(G_table, V, E, id1, fp_out, mode);
            TableGRAPHDelete(G_table, V);
            break;
        default:
            break;
        }
    } while (fscanf(fp_in, "%d %d %s %d", &V, &E, mode_str, &id1) != EOF);

    // Close the input and output files and free all memory
    fclose(fp_in);
    fclose(fp_out);
    free(aux);
    free(file_output);

    return 0;
}
