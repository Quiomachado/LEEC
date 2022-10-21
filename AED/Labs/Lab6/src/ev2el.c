/******************************************************************************
* (c) 2022 AED Team
* Last modified: lms 2022-10-20
*
* NAME
*   ev2el
*
* DESCRIPTION
*   Main program for lab guide
*   - read edge vector,
*   - write edge lists
*
* COMMENTS
*   Code for internal testing - do not distribute
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"LinkedList.h"
#include"queue.h"


typedef struct _twint {
  int n2;
  int wt;
} twint;


typedef struct _nodeS {
  int node;
  /* could add additional information here */
} NodeS;



/******************************************************************************
* usage ()
*
* Arguments: nomeProg - name of executable
* Returns: (void)
* Side-Effects: none
*
* Description: message function when arguments are missing
*****************************************************************************/

void usage(char *nomeProg)
{
  printf("Usage: %s filename\n", nomeProg);
  printf("  reads graph edges vector, writes edge lists\n");
  exit(1);
}


/******************************************************************************
* memoryError ()
*
* Arguments: msg - message to output to stderr
* Returns: (void)
* Side-Effects: none
*
* Description: exit with error message to stderr
*****************************************************************************/

void memoryError(char *msg) {

  fprintf(stderr, "Error during memory reserve attempt.\n");
  fprintf(stderr, "Msg: %s\n",msg);
  fprintf(stderr, "Exit Program due to unmanaged error.\n");

  exit(1);
}



/******************************************************************************
* doBFS ()
*
* Arguments: listv - data structure for graph list of adjacencies
*            sn - starting node
*            nv - number of nodes in graph
* Returns: (void)
* Side-Effects: none
*
* Description: does a BFS on the graph described by the list of adjacencies
*              reachable through listv and prints nodes as it finds them
*****************************************************************************/

void doBFS(LinkedList **listv, int sn, int nv) {
  int numInqueue = 0, ni;
  int *inqueue;
  NodeS *fakeNodes, *Ns;
  LinkedList *lp;
  twint *pint;
  Queue *BFSqueue;

  inqueue = (int*) malloc(nv * sizeof(int));
  if (inqueue == ((int*)NULL))
    memoryError("Cannot allocate memory for inqueue nodes.");
  for (ni = 0; ni < nv; ni++)
    inqueue[ni] = 0;

  fakeNodes = (NodeS*) malloc(nv * sizeof(NodeS));
  if (fakeNodes == ((NodeS*)NULL))
    memoryError("Cannot allocate memory for fake nodes.");
  for (ni = 0; ni < nv; ni++)
    fakeNodes[ni].node = ni;

  BFSqueue = newQueue(nv);

  /* put starting node in queue */
  insertQueue(BFSqueue, (Item) &fakeNodes[sn]);
  inqueue[sn] = 1;
  fprintf(stdout, "%d ", sn);
  numInqueue++;
  for ( ; numInqueue < nv; ) {
    /* get first element in queue, tells us node being visited */
    Ns = /* -----------  COMPLETE --------------- */
    if (Ns == ((NodeS*) NULL))
      break;
    /* process that node's adjacency list */
    lp = /* -----------  COMPLETE --------------- */
    while (lp != NULL) {
      /* for every element in the adjacency list */
      /* check if it has been queued; if not, put it in the queue */
      /* and print it to stdout */

      /* -----------  COMPLETE --------------- */

      lp = getNextNodeLinkedList(lp);
    }
  }
  fprintf(stdout, "\n");

  return;
}


/******************************************************************************
* main ()
*
* Arguments: argc - number of command-line arguments
*            argv - table of pointers for string arguments
* Returns: int status
* Side-Effects: none
*
* Description: main Program
*****************************************************************************/

int main(int argc, char *argv[])
{
  int     i, k;
  int     nv, ne;     /* V and E counts */
  int     n1, n2, wt;
  int     sn;
  char    extIn[] = ".edge";
  char    extOut[] = ".ladj";
  char    *nomeFicheiroIn, *nomeFicheiroOut;
  twint   *pint1, *pint2;

  LinkedList **listv, *lp;
  FILE    *fpIn,*fpOut;

  if(argc < 2)
    usage(argv[0]);

  nomeFicheiroIn = argv[1];

  nomeFicheiroOut =
    (char *) malloc((strlen(nomeFicheiroIn)-strlen(extIn)+strlen(extOut)+1) *
                    sizeof(char));
  if(nomeFicheiroOut == NULL)
    memoryError("Memory allocation for nomeFicheiroOut in main" );

  strcpy(nomeFicheiroOut, nomeFicheiroIn);
  nomeFicheiroOut[strlen(nomeFicheiroIn)-strlen(extIn)] = '\0';
  strcat(nomeFicheiroOut, extOut);

  /* open input file */
  fpIn  = fopen(nomeFicheiroIn,"r");
  if(fpIn == NULL) {
    printf("ERROR cannot read input file %s\n", nomeFicheiroIn);
    exit(2);
  }

  /* read input file, read nv and ne */
  k = fscanf(fpIn, "%d", &nv);
  if(k < 1) {
    printf("ERROR cannot read V number from input file %s\n",
           nomeFicheiroIn);
    exit(2);
  }
  k = fscanf(fpIn, "%d", &ne);
  if(k < 1) {
    printf("ERROR cannot read E number from input file %s\n",
           nomeFicheiroIn);
    exit(2);
  }

  /* create vector for adjacency lists, one per node */
  listv = (LinkedList**) malloc(nv * sizeof (LinkedList*));
  if (listv == ((LinkedList**) NULL))
    memoryError("memory allocation for adjacency lists vector in main");

  /* read ne edges from file, each triple n1, n2, weight */
  for(i = 0; i < ne; i++) {
    k = fscanf(fpIn, "%d %d %d", &n1, &n2, &wt);
    if(k < 3) {
      printf("ERROR cannot read edge triple from input file %s\n",
             nomeFicheiroIn);
      exit(2);
    }
    /*  DEBUG
        printf("%d %d %d\n", n1, n2, wt); */
    pint1 = (twint *) malloc(sizeof(twint));
    if (pint1 == ((twint*) NULL)) {
      memoryError("memory allocation for edge structure in main");
    }
    pint2 = (twint *) malloc(sizeof(twint));
    if (pint2 == ((twint*) NULL)) {
      memoryError("memory allocation for edge structure in main");
    }
    pint1->n2 = n2;
    pint1->wt = wt;
    pint2->n2 = n1;
    pint2->wt = wt;
    if (listv[n1] == NULL){
      listv[n1] = initLinkedList();
    }
    if (listv[n2] == NULL){
      listv[n2] = initLinkedList();
    }

    /*********** INSERT EDGE STRUCTURES IN EACH APPROPRIATE LIST ***********/
    listv[n1] = /* -----------  COMPLETE --------------- */
    listv[n2] = /* -----------  COMPLETE --------------- */

  }


  /* Compute de degree of every nome and the average edge density */

  /* -----------  COMPLETE --------------- */


  /* open output file */
  fpOut = fopen (nomeFicheiroOut, "w");
  if(fpOut == NULL) {
    printf("ERROR cannot write output file %s\n", nomeFicheiroOut);
    exit(3);
  }

  /*  print out edge vectors (.ldaj file) */
  fprintf(fpOut, "%d\n", nv);
  for(i = 0; i < nv; i++) {
    lp = listv[i];
    while (lp != NULL) {
      pint1 = (twint *) getItemLinkedList(lp);
      lp = getNextNodeLinkedList(lp);
      /* print the node and the respective weight */
      /* -----------  COMPLETE --------------- */
    }
    fprintf(fpOut, " -1\n");
  }

  /* -- close all open files -- */
  fclose(fpIn);
  fclose(fpOut);

  /****************** read path to find ************************************/
  fprintf(stdout,
          "Input node number to do a BFS from that node: ");
  fscanf(stdin, "%d", &sn);
  fprintf(stdout, "\n");
  if (sn >= nv) {
    fprintf(stderr,
            "node number outside of range of nodes in graph. Exiting.\n");
    exit(1);
  }

  /************ add code to do a BFS in graph from node en to node sn *********/
  doBFS(listv, sn, nv);

  /* -- free any memory you have allocated -- */

  exit(0);
}
