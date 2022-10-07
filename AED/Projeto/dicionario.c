#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dicionario.h"

struct node
{
    char *word;
    struct node *next;
    struct node *previous;
};

node *dict[100];

void IniDict()
{
    int i;
    for (i = 0; i < 100; i++)
    {
        dict[i] = (node *)malloc(sizeof(node));
        dict[i]->word = (char *)malloc(sizeof(char));
        dict[i]->word[0] = '\0';
    }
}

void InserirPalavra(char *palavra)
{
    unsigned int tamanho = strlen(palavra);
    node *tmp = dict[tamanho];
    node *novo = (node *)malloc(sizeof(node));
    node *aux;
    while (tmp != NULL)
    {
        if (strcmp(palavra, tmp->word) < 0)
            break;
        tmp = tmp->next;
    }
    novo->word = (char *)malloc(sizeof(char) * (tamanho + 1));
    strcpy(novo->word, palavra);
    aux = tmp->previous;
    aux->next = novo;
    novo->previous = aux;
    novo->next = tmp;
    tmp->previous = novo;
}

void FreeDict()
{
    int i;
    node *tmp;
    for (i = 0; i < 100; i++)
    {
        while (dict[i] != NULL)
        {
            tmp = dict[i];
            dict[i] = dict[i]->next;
            free(tmp->word);
            free(tmp);
        }
    }
}