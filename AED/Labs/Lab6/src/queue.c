/******************************************************************************
 *
 * File Name: queue.c
 *	      (c) 2022 AED
 * Author:    AED team
 * Revision:  v1.0 AED Team, Oct. 2022
 *
 * NAME
 *     queue.c - management of a queue of elements
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include "queue.h"
 *     #include "tree.h"
 *
 * DESCRIPTION
 *     Functions for creating and managing a queue of elements.
 *     Implementation via vector
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"


typedef struct _queueElem {
  Item elem;
} QueueElem;


struct _queue {
  int size;
  int head;
  int tail;
  int elem;
  QueueElem *qt;
};



/******************************************************************************
 * newQueue()
 *
 * Arguments: (none)
 * Returns: Pointer to new queue, i.e. pointer to structure with queue info
 *          or NULL if allocation failed
 * Side-Effects: queue gets created
 *
 * Description: allocates space for a new queue
 *
 *****************************************************************************/

Queue *newQueue(int size)
{
  Queue *queue;

  queue = (Queue*) malloc(sizeof(Queue));
  if (queue == ((Queue*) NULL)) {
    return((Queue*)NULL);
  }

  queue->qt = (QueueElem*) malloc(size * sizeof(QueueElem));
  if (queue->qt == ((QueueElem*) NULL)) {
    return((Queue*)NULL);
  }
  queue->head = 0;
  queue->tail = -1;
  queue->size = size;
  queue->elem = 0;

  return(queue);
}


/******************************************************************************
 * getfirstQueue()
 *
 * Arguments: queue - pointer to queue
 * Returns: first element of queue or NULL if queue empty
 * Side-Effects: first element is taken from queue, first position increased
 *               in table, number of elements decreased
 *
 * Description: return  first element of the queue
 *
 *****************************************************************************/

Item getfirstQueue(Queue *queue)
{
  Item first;

  /* are there any elements in queue? */
  if (queue->elem == 0) {
    return((Item)NULL);
  }
  /* queue not empty */
  first = queue->qt[queue->head].elem;
  queue->head = (queue->head + 1) % queue->size;
  queue->elem--;

  /* for simplicity, not really necessary */
  if (queue->elem == 0) {
    queue->head = 0;
    queue->tail = -1;
  }

  return (first);
}


/******************************************************************************
 * insertQueue()
 *
 * Arguments: queue - pointer to queue
 *            elem - element to add to queue
 * Returns: 0 if successfull, -1 if insertion failed
 * Side-Effects: none
 *
 * Description: insertion of element at the "end" of queue, meaning next
 *              available slot in table
 *
 *****************************************************************************/

int insertQueue(Queue *queue, Item elem)
{
  int location = (queue->tail + 1) % queue->size;

  /* check if queue is full */
  if (queue->elem == queue->size)
    return(-1);

  /* we have space, insert */
  queue->qt[location].elem = elem;
  queue->tail = location;
  queue->elem++;

  return(0);
}


/******************************************************************************
 * isemptyQueue()
 *
 * Arguments: queue - pointer to queue
 * Returns: 0 if queue is not empty, 1 if it is
 * Side-Effects: none
 *
 * Description: checks if queue is empty
 *
 *****************************************************************************/

int isemptyQueue(Queue *queue)
{
  if (queue->elem == queue->size)
    return(1);
  else
    return (0);
}


/******************************************************************************
 * freeQueue()
 *
 * Arguments: queue - pointer to queue to be freed
 * Returns: (void)
 * Side-Effects: queue is freed
 *
 * Description: frees memory for the queue and associated elements
 *
 *****************************************************************************/

void freeQueue(Queue *queue, void (* freeItemFnt)(Item))
{
  int i, loc;

  for (loc = queue->head, i = 0; i < queue->elem; i++) {
    loc = (loc+1) & queue->size;
    freeItemFnt((Item)queue->qt[loc].elem);
  }
  free(queue->qt);
  free(queue);

  return;
}


