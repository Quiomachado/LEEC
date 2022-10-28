#ifndef _DICIONARIO_H_
#define _DICIONARIO_H_

int *IniCounters(FILE *fpDic, int *maxSize);
char ***IniDic(FILE *fpDic, int *counters, int n);
char ***LerDicionario(FILE *fpDic, char ***dic, int *counters, int n);
void ImprimirTamanhoDaLinha(int linha, int *counters, char *palavra, FILE *fpOut);
int MyCompare(const void *a, const void *b);
void Sort(char ***dic, int *counters, int linha);
int Search(char **dic, char *palavra, int low, int high);
void FreeMem(char ***dic, int *counters, int n);

#endif