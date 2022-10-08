#include <stdio.h>
#include <stdlib.h>

#include "dicionario.h"

void Usage(char *nomeProg)
{
    printf("Usage: %s <nome1>.dict <nome2>.pals\n", nomeProg);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        Usage(argv[0]);
    }
    IniDict();
    FreeDict();
    return 0;
}