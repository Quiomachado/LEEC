#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_LENGTH 40

/* Alocação e inicialização de uma matriz de inteiros de L linhas */
/* e C colunas com todos os valores iguais a initial_value         */
int ** MATRIXint(int L, int C, int initial_value)
{

  int i, j, ** M;
  M = (int **) malloc(L*sizeof(int *));
  if (M == NULL) return M;
  for (i=0; i<L; i++) {
    M[i] = (int *) malloc(C*sizeof(int));
    if (M[i] == NULL) return NULL;
  }
  for(i=0; i<L; i++)
    for(j=0; j<C; j++)
      M[i][j] = initial_value;
  return M;
}

/* Libertação de uma matriz de inteiros com L linhas */
void MATRIXint_free(int ** M, int L)
{
  int i;
  for (i=0; i<L; i++)
    free(M[i]);
  free(M);
}

int main(int argc, char ** argv)
{
  /* Variáveis para armazenar o cabeçalho do problema */
  int V, E;
  char Variant[MAX_LENGTH];
  double MAX_COST, density, invalid;

  int v1, v2, i, j, **MADJ;

  char * fich=NULL;
  FILE *fout=NULL;

  /* Validação dos argumentos: em quantidade, tipo e valor */
  if (argc!= 6) {
    printf("Usage: ./Geenie -option vertices density max_cost string\nwhere:\n-option is one of -r or -o;\nvertices is an int defining the number of vertices;\ndensity is a double between 0 and V-1;\nmax_cost is a double defining the upperbound for edge cost;\nstring is the name of the output file\n");
    exit(0);
  }

  /* O primeiro argumento tem de definir qual o formato de saída */
  if (strcmp(argv[1],"-o")!=0 && strcmp(argv[1],"-r")!=0) {
    printf("Option for output format has to be one of -o(rdered) ou -r(andom)\n");
    exit(0);
  }

  /* O segundo argumento tem de definir o número de vértices do grafo */
  V = atoi(argv[2]);
  if (V <= 0) {
    printf("Number of vertices must be a non zero positive integer.\n");
    exit(0);
  } 

  /* O terceito argumento tem de ser um double para definir a densidade desejada */
  density = atof(argv[3]);
  if (density <=0 || density > V-1) {
    printf("Density has to be non negative and cannot exceed vertices-1.\n");
    exit(0);
  }
  /* Expressão para determinar o número de arestas a partir da densidade lida */
  E = density*V/2;

  /* O quarto argumento tem de ser um double para definir o custo máximo das arestas */
  MAX_COST = atof(argv[4]);
  if (MAX_COST <=0) {
    printf("Maximum edge cost has to be strictly positive.\n");
    exit(0);
  }

  /* Abertura do ficheiro de saída de nome "argv[5].routes0" */
  fich = (char *) malloc((strlen(argv[5])+strlen(".routes0")+1)*sizeof(char));
  if (fich == NULL) {
    printf("Unable to allocate variable to hold file name with extension.\n");
    exit(0);
  }
  strcpy(fich, argv[5]);
  strcat(fich, ".routes0");
  fout = fopen(fich, "w");
  if (fout == NULL) {
    printf("Unable to open output file.\n");
    exit(0);
  }

  /* Criação de matriz boleana para evitar repetição de arestas */
  MADJ=MATRIXint(V, V, 0);
  if (MADJ == NULL) {
    printf("Unable to allocate a matrix for the size requested.\n");
    exit(0);
  }

  /* Início da geração aleatória de dados */
  srand(time(NULL));
  /* Primeiro a variante */
  v1 = rand()%4;
  switch (v1) {
  case 0:
    strcpy(Variant, "A0");
    break;
  case 1:
    strcpy(Variant, "B0");
    break;
  case 2:
    strcpy(Variant, "C0");
    break;
  case 3:
    strcpy(Variant, "D0");
    break;
  }

  /* Escrita do cabeçalho do problema */  
  /* Este programa produz vértices inválidos para cabeçalhos 1% das vezes */
  invalid=1.0*rand()/RAND_MAX;
  if (invalid <= 0.005)
    /* Vértice de índice negativo */
    v1 = -1*(rand()%V);
  else if (invalid <= 0.01)
    /* Vértice de índice acima do número máximo admissível */
    v1 = rand()%V+1+V;
  else
    /* Vértice legal */
    v1 = rand()%V+1;
  fprintf(fout, "%d %d %s %d", V, E, Variant, v1);
  if (strcmp(Variant, "B0")==0) {
    /* A mesma coisa que anteriormente para geração de vértices válidos e inválidos */
    invalid=1.0*rand()/RAND_MAX;
    if (invalid <= 0.005)
      v1 = -1*(rand()%V+1);
    else if (invalid <= 0.01)
      v1 = rand()%V+1+V;
    else
      v1 = rand()%V+1;
    fprintf(fout, " %d\n", v1);
  }
  else 
    fprintf(fout, "\n");
 
  /* Geração de arestas */
  while (E>0) {
    v1= rand()%V;
    v2=rand()%V;
    /* Aresta gerada não pode ser repetida nem reflexiva */
    if (v1!=v2 && MADJ[v1][v2]!=1) {
      MADJ[v1][v2]=1;
      MADJ[v2][v1]=1;
      E--;
      /* Output para ficheiro pela ordem de geração */
      /* O custo da aresta é gerado apenas para output */
      if (strcmp(argv[1], "-r")==0)
	fprintf(fout, "%d %d %lf\n", v1+1, v2+1, (1.0*rand()/RAND_MAX)*MAX_COST);
    }
  }

  /* Escrita para ficheiro de saída das arestas geradas com geração de custo */
  /* Neste caso o output fica ordenado pelos vértices de partida             */
  if(strcmp(argv[1], "-o")==0)
    for (i=0; i<V; i++)
      for (j=i+1; j<V; j++)
	if (MADJ[i][j]==1) {
	  fprintf(fout, "%d %d %lf\n", i+1, j+1, (1.0*rand()/RAND_MAX)*MAX_COST);
	}
  /* Para ter uma linha vazia no final do problema */
  fprintf(fout, "\n");

  /* Liberta a memória associada com a string que contém o nome do ficheiro de saida */
  /* Fecha o ficheiro de saída e liberta a matriz boleana                            */
  free(fich);
  fclose(fout);
  MATRIXint_free(MADJ, V); 
  
  /*  printf("All is well...\n"); */
  exit(0);
}

