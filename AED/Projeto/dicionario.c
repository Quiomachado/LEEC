#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dicionario.h"

struct node
{
    char *word;
    int size;
    struct node *next;
};

int GetMax(FILE *fpDic)
{
    int max = 0;
    char novaPal[100];
    while (fscanf(fpDic, "%s", novaPal) == 1)
    {
        if (strlen(novaPal) > max)
        {
            max = strlen(novaPal);
        }
    }
    return max + 1;
}

/*Inicializa o nosso dicionario*/
node **IniDict(node **dict, int max)
{
    int i;
    dict = (node **)malloc(sizeof(node *) * max);
    for (i = 0; i < max; i++)
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
        dict[i]->size = 0;
    }
    return dict;
}

/*recebe o dicionario inicializado e o ficheiro de dicionario lê-o chamando a função InserirPalavra em cada palavra*/
node **LerDicionario(FILE *fpDic, node **dict, int max)
{
    char novaPal[max];
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
    novo->next = tmp;
    novo->size = dict[tamanho]->size + 1;
    dict[tamanho] = novo;
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
    double size;
    size = head->size;

    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    Split(head, &a, &b);

    MergeSort(&a);
    MergeSort(&b);

    *dic = Merge(a, b);
    (*dic)->size = size;
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
    fprintf(fpOut, "%s %d\n", palavra1, dict[linha]->size);
    return;
}

/*Imprime a Posicao de cada palavra na sua linha*/
void ImprimirPosicao(int linha, node **dict, char *palavra1, char *palavra2, FILE *fpOut)
{
    int pos1 = 0, pos2 = 0, count = 0;

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
        if (pos1 != 0 && pos2 != 0)
            return;
    }

    /* pos1 = BinarySearch(dict[linha], palavra1);
    pos2 = BinarySearch(dict[linha], palavra2); */

    fprintf(fpOut, "%s %d\n%s %d\n", palavra1, pos1, palavra2, pos2);
    return;
}

node *Middle(node *start, node *last, int *location)
{
    if (start == NULL)
        return NULL;

    int temp = *location;

    node *slow = start;
    node *fast = start->next;

    while (fast != last)
    {
        fast = fast->next;
        if (fast != last)
        {
            slow = slow->next;
            temp++;
            fast = fast->next;
        }
    }

    *location = temp;

    return slow;
}

int BinarySearch(node *head, char *word)
{
    node *start = head;
    node *last = NULL;
    int location = 0;
    int sLocation = 0;

    do
    {
        node *mid = Middle(start, last, &location);

        if (mid == NULL)
            return -1;

        if (strcmp(mid->word, word) == 0)
            return location - 1;
        else if (strcmp(mid->word, word) < 0)
        {
            start = mid->next;
            location++;
            sLocation = location;
        }

        else
        {
            last = mid;
            location = sLocation;
        }
    } while (last == NULL || last != start);

    return -1;
}

/*liberta a memoria alocada para o dicionario*/
void FreeDict(node **dict, int max)
{
    int i;
    node *tmp;
    for (i = 0; i < max; i++)
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