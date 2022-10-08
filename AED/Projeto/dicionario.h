#ifndef _DICIONARIO_H_
#define _DICIONARIO_H_

typedef struct node node;

node **IniDict(node **dict);
node **LerDicionario(FILE *dic, node **dict);
node **InserirPalavra(char *palavra, node **dict);
void FreeDict(node **dict);

#endif