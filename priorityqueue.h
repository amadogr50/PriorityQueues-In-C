#ifndef PQ_H_
#define PQ_H_

typedef void * Type;
typedef enum {FALSE, TRUE} Bool;
typedef struct strPriorityQueue * PriorityQueue;
typedef struct strGraph * Graph;
typedef struct strList * List;
typedef int (*CompareFunc) (Type, Type);
typedef void (*DestroyFunc) (Type);

PriorityQueue priorityqueue_create(DestroyFunc dF, CompareFunc cF, int capacity, Bool isMinHeap);
void priorityqueue_destroy(PriorityQueue);
int priorityqueue_size(PriorityQueue);
void priorityqueue_offer(PriorityQueue, Type);
Type priorityqueue_peek(PriorityQueue);
Type priorityqueue_poll(PriorityQueue);

List list_create(void (*destructor)(Type));
void list_destroy(List);
int  list_size(List);
void list_add(List, Type);
Type list_get(List, int p);
void list_set(List, Type, int p);
Type list_remove(List, int p);

Graph graph_create(PrintFunc printer, DestroyFunc destructor);
void graph_destroy(Graph g);
void graph_addVertex(Graph g, Type u);
void graph_deleteVertex(Graph g, Type v);
void graph_addEdge(Graph g, Type u, Type v, double weight);
void graph_deleteEdge(Graph g, Type u, Type v);

void BFS(Graph g, Type start);
void DFS(Graph g);
void dijkstra(Graph g, Type start);

#endif
