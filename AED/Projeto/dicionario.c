#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dicionario.h"

struct node
{
    char *word;
    struct node *next;
};

/*Inicializa o nosso dicionario*/
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

/*recebe o dicionario inicializado e o ficheiro de dicionario lê-o chamando a função InserirPalavra em cada palavra*/
node **LerDicionario(FILE *fpDic, node **dict)
{
    char novaPal[100];
    while (fscanf(fpDic, "%s", novaPal) == 1)
    {
        dict = InserirPalavra(novaPal, dict);
    }
    return dict;
}

/*Insere cada palavra no dicionario pela ordem que aparecem*/
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
    return dict;
}

/*ordena a linha do dicionario por ordem alfabética através de MergeSort*/
node **OrdenarLinha(int linha, node **dict)
{
    MergeSort(&dict[linha]);
    return dict;
}

/*Algorítmo de MergeSort*/
void MergeSort(node **dic)
{
    node *head = *dic;
    node *a, *b;

    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    Split(head, &a, &b);

    MergeSort(&a);
    MergeSort(&b);

    *dic = Merge(a, b);
}

/*Une as duas metades já organizadas alfabéticamente*/
node *Merge(node *a, node *b)
{
    node *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (strcmp(a->word, b->word) < 0)
    {
        result = a;
        result->next = Merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = Merge(a, b->next);
    }
    return result;
}

/*divide a list em metade*/
void Split(node *origem, node **front, node **back)
{
    node *fim, *metade;
    metade = origem;
    fim = origem->next;

    while (fim != NULL)
    {
        fim = fim->next;
        if (fim != NULL)
        {
            metade = metade->next;
            fim = fim->next;
        }
    }

    *front = origem;
    *back = metade->next;
    metade->next = NULL;
}

/*Imprime o tamanho da linha*/
void ImprimirTamanhoLinha(int linha, node **dict, char *palavra1, FILE *fpOut)
{
    int count = -1;
    node *tmp;
    tmp = dict[linha];
    while (tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }
    fprintf(fpOut, "%s %d\n", palavra1, count);
    return;
}

/*Imprime a Posicao de cada palavra na sua linha*/
void ImprimirPosicao(int linha, node **dict, char *palavra1, char *palavra2, FILE *fpOut)
{
    int pos1 = 0, pos2 = 0, count = -1;
    node *tmp;
    tmp = dict[linha];
    while (tmp != NULL)
    {
        if (strcmp(palavra1, tmp->word) == 0)
        {
            pos1 = count;
        }
        if (strcmp(palavra2, tmp->word) == 0)
        {
            pos2 = count;
        }
        count++;
        tmp = tmp->next;
    }
    fprintf(fpOut, "%s %d\n%s %d\n", palavra1, pos1, palavra2, pos2);
    return;
}

/*liberta a memoria alocada para o dicionario*/
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