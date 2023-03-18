#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graf.h"

char MODES[4][3] = {"A0", "B0", "C0", "D0"};

void GetDegree(graph *G, int id, FILE *fp_out, int mode)
{
    int degree = 0;
    char mode_str[3];
    node *t = 0;
    strcpy(mode_str, MODES[mode]);
    for (t = GetAdj(G, id); t != NULL; t = GetNext(t))
    {
        degree++;
    }
    fprintf(fp_out, "%d %d %s %d %d\n\n", GetVCount(G), GetECount(G), mode_str, id, degree);
    return;
}

int main(int argc, char *argv[])
{
    int max_args = 2;
    char *file_input = 0;
    char *file_output = 0;
    char file_ending[9] = ".queries";
    char *aux = 0;
    FILE *fp_in = 0, *fp_out = 0;
    int V = 0, E = 0, id1 = 0, id2 = 0;
    graph *G = 0;
    int ver1 = 0, ver2 = 0;
    double wt = 0;
    char mode_str[2];
    int mode = 0;

    // Check if the number of arguments is correct
    if (argc > max_args)
    {
        exit(0);
    }

    // Get the input file name
    file_input = argv[1];
    aux = (char *)malloc(sizeof(char) * (strlen(file_input) + 1));
    strcpy(aux, file_input);
    aux[strlen(aux) - 8] = '\0';
    file_output = (char *)malloc(sizeof(char) * (strlen(aux) + strlen(file_ending) + 1));
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

    // Read the rest of the input file and insert the edges into the graph
    switch (mode)
    {
    case 0:
        while (fscanf(fp_in, "%d %d %le", &ver1, &ver2, &wt) != EOF)
        {
            GRAPHinsertE(G, ver1, ver2, wt);
        }
        GetDegree(G, id1, fp_out, mode);
        break;
    case 1:
        fscanf(fp_in, "%d", &id2);
        while (fscanf(fp_in, "%d %d %le", &ver1, &ver2, &wt) != EOF)
        {
            GRAPHinsertE(G, ver1, ver2, wt);
        }
        break;
    case 2:
        while (fscanf(fp_in, "%d %d %le", &ver1, &ver2, &wt) != EOF)
        {
            GRAPHinsertE(G, ver1, ver2, wt);
        }
        break;
    case 3:
        while (fscanf(fp_in, "%d %d %le", &ver1, &ver2, &wt) != EOF)
        {
            GRAPHinsertE(G, ver1, ver2, wt);
        }
        break;
    default:
        break;
    }

    // Close the input and output files and free all memory
    fclose(fp_in);
    fclose(fp_out);
    GRAPHDestroy(G);
    free(aux);
    free(file_output);

    return 0;
}