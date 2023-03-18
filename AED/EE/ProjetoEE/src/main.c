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
    if (argc > max_args)
    {
        printf("Too many arguments supplied.\n");
        exit(0);
    }

    file_input = argv[1];
    aux = (char *)malloc(sizeof(char) * (strlen(file_input) + 1));
    strcpy(aux, file_input);
    aux[strlen(aux) - 7] = '\0';
    file_output = (char *)malloc(sizeof(char) * (strlen(aux) + 9));
    sprintf(file_output, "%s%s", aux, file_ending);

    

    return 0;
}