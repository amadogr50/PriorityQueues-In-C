#include "priorityqueue.h"
#include <stdio.h>
#include <stdlib.h>

struct strPriorityQueue 
{
  Type * queue;
  int size;
  int capacity;
  Bool isMinHeap;
  DestroyFunc destroyFunc;
  CompareFunc compareFunc;
};

PriorityQueue priorityqueue_create(DestroyFunc dF, CompareFunc cF, int capacity, Bool isMinHeap)
{
  PriorityQueue pq = (PriorityQueue) malloc(sizeof(struct strPriorityQueue));
  pq->queue = (Type *) malloc ( capacity * sizeof(Type));
  pq->size = 0;
  pq->capacity = capacity;
  pq->isMinHeap = isMinHeap;
  pq->compareFunc = cF;
  pq->destroyFunc = dF;
}

void priorityqueue_destroy(PriorityQueue pq)
{
  //Confirm pq is valid
  if (pq == NULL)
    return;

  if (pq->destroyFunc != NULL) {
    for (int i = 0; i < pq->size; i++) {
      pq->destroyFunc(pq->queue[i]);
    }
  }

  free(pq->queue);
  free(pq);
}

int priorityqueue_size(PriorityQueue pq)
{
  //Confirm pq is valid
  if (pq == NULL || pq->size == 0)
    return 0;
  
  return pq->size;
}

Bool isValidIndex(PriorityQueue q, int index)
{
  return index < q->size;
}

int parentIndex(int index)
{
  return (1/2)*(index - 1);
}

int leftChildIndex(int index)
{
  return 2*index + 1;
}

int rightChildIndex(int index)
{
  return 2*index + 2;
}

void priorityqueue_offer(PriorityQueue pq, Type t)
{
  //Confirm pq is valid
  if (pq == NULL) 
    return;

  //Case when queue is empty
  if (pq->size == 0) {
    pq->queue[0] = t;
    pq->size++;
    return;
  }

  //Any other case: First add the data in the queue size index
  pq->queue[pq->size] = t;
  pq->size++;

  //Min binary heap has priority in smaller values so...
  //Verify if the child is greater than its parent, otherwise, switch them
  //Repeat the process till there´s not smaller parent and cIndex is not the root
  int cIndex = pq->size - 1;
  int pIndex = parentIndex(cIndex);

  if (pq->isMinHeap) {
    while (pq->compareFunc(t, pq->queue[pIndex]) < 0  && cIndex != 0) {
      Type temp = pq->queue[pIndex];
      pq->queue[pIndex] = pq->queue[cIndex];
      pq->queue[cIndex] = temp;

      cIndex = pIndex;
      pIndex = parentIndex(pIndex);
    }
  } else {
    while (pq->compareFunc(t, pq->queue[pIndex]) > 0  && cIndex != 0) {
      Type temp = pq->queue[pIndex];
      pq->queue[pIndex] = pq->queue[cIndex];
      pq->queue[cIndex] = temp;

      cIndex = pIndex;
      pIndex = parentIndex(pIndex);
    }   
  }
}

Type priorityqueue_peek(PriorityQueue pq)
{
  //Confirm pq is valid
  if (pq == NULL || pq->size == 0) 
    return NULL;

  return pq->queue[0];
}

Type priorityqueue_poll(PriorityQueue pq)
{
  //Confirm pq is valid
  if (pq == NULL || pq->size == 0) 
    return NULL;

  Type data = pq->queue[0];

  pq->queue[0] = pq->queue[pq->size - 1];
  pq->queue[pq->size -1] = NULL; 
  pq->size--;

  int lcIndex = leftChildIndex(0);
  int rcIndex = rightChildIndex(0);
  
  if (pq->isMinHeap) {
    Bool leftIsSmaller = FALSE;
    Bool rightIsSmaller = FALSE;

    if (isValidIndex(pq, lcIndex)) 
      leftIsSmaller = pq->compareFunc(pq->queue[lcIndex], pq->queue[0]) < 0;
    
    if (isValidIndex(pq, rcIndex)) 
      rightIsSmaller = pq->compareFunc(pq->queue[rcIndex], pq->queue[0]) < 0;

    int smallerIndex;

    if (leftIsSmaller && rightIsSmaller) {
      smallerIndex = (pq->compareFunc(pq->queue[lcIndex], pq->queue[rcIndex]) > 0 ) ? rcIndex : lcIndex;
    } else if (!leftIsSmaller && !rightIsSmaller) {
      smallerIndex = 0;
    } else if (leftIsSmaller) {
      smallerIndex = lcIndex; 
    } else {
      smallerIndex = rcIndex;
    }

    while ( smallerIndex ) {
      Type aux = pq->queue[0];
      pq->queue[0] = pq->queue[smallerIndex];
      pq->queue[smallerIndex] = aux;

      leftIsSmaller = FALSE;
      Bool rightIsSmaller = FALSE;

      if (isValidIndex(pq, lcIndex)) 
        leftIsSmaller = pq->compareFunc(pq->queue[lcIndex], pq->queue[0]) < 0;

      if (isValidIndex(pq, rcIndex)) 
        rightIsSmaller = pq->compareFunc(pq->queue[rcIndex], pq->queue[0]) < 0;

      if (leftIsSmaller && rightIsSmaller) {
        smallerIndex = (pq->compareFunc(pq->queue[lcIndex], pq->queue[rcIndex]) > 0 ) ? rcIndex : lcIndex;
      } else if (!leftIsSmaller && !rightIsSmaller) {
        smallerIndex = 0;
      } else if (leftIsSmaller) {
        smallerIndex = lcIndex; 
      } else {
        smallerIndex = rcIndex;
      }
    }
  } else {
    Bool leftIsGreater = FALSE;
    Bool rightIsGreater = FALSE;

    if (isValidIndex(pq, lcIndex)) 
      leftIsGreater = pq->compareFunc(pq->queue[lcIndex], pq->queue[0]) > 0;
    
    if (isValidIndex(pq, rcIndex)) 
      rightIsGreater = pq->compareFunc(pq->queue[rcIndex], pq->queue[0]) > 0;
      
    int greaterIndex;

    if (leftIsGreater && rightIsGreater) {
      greaterIndex = (pq->compareFunc(pq->queue[rcIndex], pq->queue[lcIndex]) > 0 ) ? rcIndex : lcIndex;
    } else if (!leftIsGreater && !rightIsGreater) {
      greaterIndex = 0;
    } else if (leftIsGreater) {
      greaterIndex = lcIndex; 
    } else {
      greaterIndex = rcIndex;
    }

    while ( greaterIndex ) {
      Type aux = pq->queue[0];
      pq->queue[0] = pq->queue[greaterIndex];
      pq->queue[greaterIndex] = aux;

      leftIsGreater = FALSE;
      rightIsGreater = FALSE;

      if (isValidIndex(pq, lcIndex)) 
        leftIsGreater = pq->compareFunc(pq->queue[lcIndex], pq->queue[0]) > 0;
      
      if (isValidIndex(pq, rcIndex)) 
        rightIsGreater = pq->compareFunc(pq->queue[rcIndex], pq->queue[0]) > 0;
    
      if (leftIsGreater && rightIsGreater) {
        greaterIndex = (pq->compareFunc(pq->queue[rcIndex], pq->queue[lcIndex]) > 0 ) ? rcIndex : lcIndex;
      } else if (!leftIsGreater && !rightIsGreater) {
        greaterIndex = 0;
      } else if (leftIsGreater) {
        greaterIndex = lcIndex; 
      } else {
        greaterIndex = rcIndex;
      }
    }
  }

  return data;
}


