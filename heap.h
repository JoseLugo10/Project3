#ifndef PROJECT3_HEAP_H
#define PROJECT3_HEAP_H
#include "graph.h"

void Insert(Vertex* &Q, Vertex *x);

Vertex* ExtractMin(Vertex* &Q);

void minHeapify(Vertex* &Q, int m, int n);

void buildHeap(Vertex* &Q, int n);

void DecreaseKey(Vertex* &Q, Vertex *v, int distance);

#endif //PROJECT3_HEAP_H
