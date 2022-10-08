#ifndef _DICIONARIO_H_
#define _DICIONARIO_H_

typedef struct node node;

node **IniDict(node **dict);
node **LerDicionario(FILE *dic, node **dict);
node **InserirPalavra(char *palavra, node **dict);
node **OrdenarLinha(int linha, node **dict);
void MergeSort(node **dic);
node *Merge(node *a, node *b);
void Split(node *origem, node **front, node **back);
void ImprimirTamanhoLinha(int linha, node **dict, char *palavra1, FILE *fpOut);
void ImprimirPosicao(int linha, node **dict, char *palavra1, char *palavra2, FILE *fpOut);
void FreeDict(node **dict);

#endif