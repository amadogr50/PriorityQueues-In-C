#ifndef PQ_H_
#define PQ_H_

typedef void * Type;
typedef enum {FALSE, TRUE} Bool;
typedef struct strPriorityQueue * PriorityQueue;
typedef int (*CompareFunc) (Type, Type);
typedef void (*DestroyFunc) (Type);

PriorityQueue priorityqueue_create(DestroyFunc dF, CompareFunc cF, int capacity, Bool isMinHeap);
void priorityqueue_destroy(PriorityQueue);
int priorityqueue_size(PriorityQueue);
void priorityqueue_offer(PriorityQueue, Type);
Type priorityqueue_peek(PriorityQueue);
Type priorityqueue_poll(PriorityQueue);

#endif