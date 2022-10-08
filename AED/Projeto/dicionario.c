#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dicionario.h"

struct node
{
    char *word;
    struct node *next;
};

node **IniDict(node **dict)
{
    int i;
    dict = (node **)malloc(sizeof(node *) * 100);
    for (i = 0; i < 100; i++)
    {
        dict[i] = (node *)malloc(sizeof(node));
        if (dict[i] == NULL)
        {
            fprintf(stderr, "Problema de alocação de memória.\n");
            exit(2);
        }
        dict[i]->word = (char *)malloc(sizeof(char));
        if (dict[i]->word == NULL)
        {
            fprintf(stderr, "Problema de alocação de memória.\n");
            exit(2);
        }
        dict[i]->word[0] = '\0';
        dict[i]->next = NULL;
    }
    return dict;
}

node **LerDicionario(FILE *fpDic, node **dict)
{
    char novaPal[100];
    while (fscanf(fpDic, "%s", novaPal) == 1)
    {
        dict = InserirPalavra(novaPal, dict);
    }
    return dict;
}

node **InserirPalavra(char *palavra, node **dict)
{
    unsigned int tamanho = strlen(palavra);
    node *tmp = dict[tamanho];
    node *aux = tmp;
    node *novo = (node *)malloc(sizeof(node));
    if (novo == NULL)
    {
        fprintf(stderr, "Problema de alocação de memória.\n");
        exit(2);
    }
    while (tmp != NULL)
    {
        if (strcmp(palavra, tmp->word) < 0)
            break;
        aux = tmp;
        tmp = tmp->next;
    }
    novo->word = (char *)malloc(sizeof(char) * (tamanho + 1));
    if (novo->word == NULL)
    {
        fprintf(stderr, "Problema de alocação de memória.\n");
        exit(2);
    }
    strcpy(novo->word, palavra);
    if (aux == tmp)
    {
        novo->next = tmp;
        dict[tamanho] = novo;
    }
    else
    {
        novo->next = tmp;
        aux->next = novo;
    }
    /* if (tmp->previous != NULL)
    {
        aux = tmp->previous;
        aux->next = novo;
        novo->previous = aux;
        novo->next = tmp;
        tmp->previous = novo;
    }
    else
    {
        novo->previous = NULL;
        novo->next = tmp;
        tmp->previous = novo;
    } */
    return dict;
}

void FreeDict(node **dict)
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
    free(dict);
}