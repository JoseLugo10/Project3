#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H

struct Edge
{
    int u;
    int v;
    int weight;
};

struct Vertex
{
    int num;
    int pred;
    int dist;
};

struct adjList
{
    int vertex;
    int weight;
    struct adjList *next;
};

struct Graph
{
    struct Vertex **vertices;
    struct Edge **edges;
};

void insertAtHead(adjList **list, int v, int weight);

void printList(adjList *list);

#endif //PROJECT3_GRAPH_H
