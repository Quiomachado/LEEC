/******************************************************************************
 *
 * File Name: queue.h
 *	      (c) 2022 AED
 * Author:    AED team
 * Revision:  v1.0 AED Team, Oct. 2022
 *
 * NAME
 *     queue.h - prototypes
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *
 * DESCRIPTION
 *		Definitions useful to implement breath scan
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#include "defs.h"

typedef struct _queue Queue;

Queue *newQueue(int size);                 /* creates empty queue of size elements */
Item getfirstQueue(Queue* queue);          /* get first element of the queue */
int insertQueue(Queue* queue, Item item);  /* insertion at the end of queue */
int isemptyQueue(Queue*queue);             /* check if queue is empty */
void freeQueue(Queue *queue, void (* freeItemFnt)(Item));
