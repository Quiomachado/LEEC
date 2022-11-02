#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int subs[] = NULL;
    FILE *fpPals;
    char *trash;
    int len, tmp;
    int subLen;
    fpPals = fopen(argv[1], "r");
    while (fscanf(fpPals, "%s %s %d", trash, trash, &tmp) == 3)
    {
        len = strlen(trash);
        if (subs[len] > tmp)
            subs[len] = tmp;
    }
}