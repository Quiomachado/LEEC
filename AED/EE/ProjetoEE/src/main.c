#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graf.h"

// Allowed Modes
char MODES[3][3] = {"A1", "B1", "D1"};

int main(int argc, char *argv[])
{
    int max_args = 2;
    char *file_input = NULL;
    char *file_output = NULL;
    char file_ending[9] = ".bbones";
    char *aux = NULL;
    FILE *fp_in = NULL, *fp_out = NULL;
    int V = 0, E = 0, id1 = 0, id2 = 0;
    graph *G = NULL;
    int ver1 = 0, ver2 = 0;
    double wt = 0;
    char mode_str[2];
    int mode = 0;
    int edge_count = 0;
    node *old_st;

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
    aux[strlen(aux) - 7] = '\0';
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
    fscanf(fp_in, "%d %d %s", &V, &E, mode_str);
    do
    {
        // Initialize the graph
        G = GRAPHinit(V);

        old_st = (node *)malloc(SizeofNode());

        // Turn the mode into an integer
        if (strcmp(mode_str, MODES[0]) == 0)
            mode = 0;
        else if (strcmp(mode_str, MODES[1]) == 0)
            mode = 1;
        else if (strcmp(mode_str, MODES[2]) == 0)
            mode = 2;
        else
            exit(0);

        edge_count = 0;

        // Read the rest of the input file and insert the edges into the graph
        switch (mode)
        {
        case 0:
            while (edge_count < E)
            {
                fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                edge_count++;
                GRAPHinsertE(G, ver1 - 1, ver2 - 1, wt);
            }
            GRAPHmst(G, -1);
            fprintf(fp_out, "%d %d %s %d %.2f\n", V, E, mode_str, GetMstCount(G), GetMstWt(G));
            GRAPHprintMst(G, fp_out, mode_str);
            free(old_st);
            GRAPHDestroy(G);
            break;
        case 1:
            fscanf(fp_in, "%d %d", &id1, &id2);
            while (edge_count < E)
            {
                fscanf(fp_in, "%d %d %lf", &ver1, &ver2, &wt);
                edge_count++;
                GRAPHinsertE(G, ver1 - 1, ver2 - 1, wt);
            }
            GRAPHmst(G, -1);
            if (id1 > V || id1 < 1 || id2 > V || id2 < 1 || id1 == id2)
            {
                fprintf(fp_out, "%d %d %s %d %d %d %.2f %d\n", V, E, mode_str, id1, id2, GetMstCount(G), GetMstWt(G), -1);
                free(old_st);
                GRAPHprintMst(G, fp_out, mode_str);
                GRAPHDestroy(G);
                break;
            }
            
            if (!CheckEdge(G, id1, id2)) {
                fprintf(fp_out, "%d %d %s %d %d %d %.2f %d\n", V, E, mode_str, id1, id2, GetMstCount(G), GetMstWt(G), 0);
                free(old_st);
                GRAPHprintMst(G, fp_out, mode_str);
                GRAPHDestroy(G);
                break;
            }
            GRAPHremoveE(G, id1 - 1, id2 - 1);
            if (!GRAPHConnectivity(G)) {
                fprintf(fp_out, "%d %d %s %d %d %d %.2f %d\n", V, E, mode_str, id1, id2, GetMstCount(G), GetMstWt(G), -1);
                free(old_st);
                GRAPHprintMst(G, fp_out, mode_str);
                GRAPHDestroy(G);
                break;
            }
            fprintf(fp_out, "%d %d %s %d %d %d %.2f %d\n", V, E, mode_str, id1, id2, GetMstCount(G), GetMstWt(G), 1);
            GRAPHprintMst(G, fp_out, mode_str);


            old_st = CopyNode(old_st, GetMst(G));
            

            GRAPHmst(G, -1);

            GRAPHmstDiff(G, fp_out, old_st);
            DESTROYoldSt(old_st);
            GRAPHDestroy(G);
            break;
        case 2:
            fscanf(fp_out, "%d", &id1);
            if (id1 > V || id1 < 1)
            {
                fprintf(fp_out, "%d %d %s %d %d\n\n", V, E, mode_str, id1, -1);
                GRAPHDestroy(G);
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
                if (ver1 == id1 || ver2 == id1)
                    continue;
                GRAPHinsertE(G, ver1 - 1, ver2 - 1, wt);
            }
            GRAPHDestroy(G);
            break;
        default:
            break;
        }
    } while (fscanf(fp_in, "%d %d %s", &V, &E, mode_str) != EOF);

    // Close the input and output files and free all memory
    fclose(fp_in);
    fclose(fp_out);
    free(aux);
    free(file_output);

    return 0;
}
