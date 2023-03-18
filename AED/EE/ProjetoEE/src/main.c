#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graf.h"

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
    int ver1 = 0, ver2 = 0, wt = 0;

    char mode[2];
    if (argc > max_args)
    {
        exit(0);
    }

    file_input = argv[1];
    aux = (char *)malloc(sizeof(char) * (strlen(file_input) + 1));
    strcpy(aux, file_input);
    aux[strlen(aux) - 7] = '\0';
    file_output = (char *)malloc(sizeof(char) * (strlen(aux) + 9));
    sprintf(file_output, "%s%s", aux, file_ending);

    fp_in = fopen(file_input, "r");
    if (fp_in == NULL)
        exit(0);
    fp_out = fopen(file_output, "w");
    if (fp_out == NULL)
        exit(0);

    fscanf(fp_in, "%d %d %s %d", &V, &E, mode, &id1);

    G = GRAPHinit(V);

    if (strcmp(mode, "A0") == 0)
    {
        while (fscanf(fp_in, "%d %d %d", &ver1, &ver2, &wt) != EOF)
        {
            GRAPHinsertE(G, ver1, ver2, wt);
        }
    }
    else if (strcmp(mode, "B0") == 0)
    {
        fscanf(fp_in, "%d", &id2);
        while (fscanf(fp_in, "%d %d %d", &ver1, &ver2, &wt) != EOF)
        {
            GRAPHinsertE(G, ver1, ver2, wt);
        }
    }
    else if (strcmp(mode, "C0") == 0)
    {
    }
    else if (strcmp(mode, "D0") == 0)
    {
    }

    return 0;
}