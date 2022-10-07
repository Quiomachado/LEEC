#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dicionario.h"

typedef struct node
{
    char *word;
    struct node *next;
} node;


