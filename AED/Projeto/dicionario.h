#ifndef _DICIONARIO_H_
#define _DICIONARIO_H_

typedef struct node node;

int GetMax(FILE *fpDic);
node **IniDict(node **dict, int max);
node **LerDicionario(FILE *dic, node **dict, int max);
node **InserirPalavra(char *palavra, node **dict);
node **OrdenarLinha(int linha, node **dict);
void MergeSort(node **dic);
node *Merge(node *a, node *b);
void Split(node *origem, node **front, node **back);
node *Middle(node *start, node *last, int *location);
int BinarySearch(node *head, char *word);
void ImprimirTamanhoLinha(int linha, node **dict, char *palavra1, FILE *fpOut);
void ImprimirPosicao(int linha, node **dict, char *palavra1, char *palavra2, FILE *fpOut);
void FreeDict(node **dict, int max);

#endif