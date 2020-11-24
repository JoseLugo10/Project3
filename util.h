#ifndef PROJECT3_UTIL_H
#define PROJECT3_UTIL_H
#include "graph.h"
#include "main.h"

void INIT_SINGLE_SOURCE(Graph *G, Vertex *s);

int arrSize(Vertex **v);

int arrAmount(Edge **e);

void Relax(Vertex* u, Vertex &v, Edge *w);

void Dijkstra(Graph *G, Vertex *s, int i);
#endif //PROJECT3_UTIL_H
