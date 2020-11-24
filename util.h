#ifndef PROJECT3_UTIL_H
#define PROJECT3_UTIL_H
#include "graph.h"
#include "main.h"

void INIT_SINGLE_SOURCE(Graph *G, Vertex *s);

void Relax(Vertex* u, Vertex &v, Edge w);

Vertex* Dijkstra(Graph *G, Vertex *s);
#endif //PROJECT3_UTIL_H
