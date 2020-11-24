#include <iostream>
#include "graph.h"
#include "main.h"
#include "heap.h"

using namespace std;

// This function will initialize all the distances of the vertices of the Graph to infinity (999), and their predecessors to -1.
void INIT_SINGLE_SOURCE(Graph *G, Vertex *s)
{
    for(int i = 0; i < n; i++)
    {
        G->vertices[i].dist = 999;
        G->vertices[i].pred = -1;
    }
    // We also set the distance of the starting node to 0.
    s->dist = 0;
}

// The relax function is used to find the shortest path between 2 nodes.
void Relax(Vertex* u, Vertex &v, Edge w)
{
    // If the distance to vertex v is greater than the weight function plus the distance to vertex u, we initialize the distance to v to the shorter path.
    if(v.dist > u->dist + w.weight)
    {
        int sum = u->dist + w.weight;
        v.dist = sum;
        v.pred = u->num;
    }
}

// Dijkstra's algorithm uses a lot of the functions that we created earlier, and creates the shortest path between two vertices.
Vertex* Dijkstra(Graph *G, Vertex *s)
{
    // We call INIT_SINGLE_SOURCE() to set the distances of the vertices to 999, and their predecessors to -1.
    INIT_SINGLE_SOURCE(G, s);

    // The Vertex array will contain the nodes of the shortest path.
    auto *S = new Vertex[n];

    // Our queue Q is initalized to a Vertex array of one, because we will insert the elements inside using the Insert() function.
    auto *Q = new Vertex[1];

    // Since the starting node is the shortest path, we set the first element of Q to our starting node.
    Q[0].dist = s->dist;
    Q[0].num = s->num;
    Q[0].pred = s->pred;

    // The for loop will insert all of the vertices from the Graph G into the queue Q.
    for(int i = 0; i < n; i++)
    {
        if(G->vertices[i].num != Q[0].num)
        {
            Insert(Q, &G->vertices[i]);
        }
    }

    // The while loop will go until the value of index is equal to n - 1. Throughout the loop will find find the shortest path of every single vertex.
    int index = 0;
    while(Q[0].num != 0)
    {
        // We create a Vertex called u that will be initalized to the minumum value of the queue Q.
        auto *u = new Vertex();
        u = ExtractMin(Q);

        // The index element of S is initialized to the Vertex u.
        S[index] = *u;

        // If we have used up all of the vertices in Q, we will break from the loop.
        if(index == n - 1)
        {
            break;
        }

        // This for loop will iterate through all of the edges in G to find the shortest paths from the vertex in S.
        for(int i = 0; i < m; i++)
        {
            // We want to find an edge that has a value of u equal to the vertex in S, and the value u that isn't equal to the vertex in S.
            if(G->edges[i].u == S[index].num && G->edges[i].v != S[index].num)
            {
                // The variable mark will be used to help find the vertices in G that corresponds to the edge that we have found.
                int mark = 0;
                for(int j = 0; j < n; j++)
                {
                    // If we have found the vertex that is equal to the end of the edge, then we will break from the loop.
                    if(G->vertices[j].num == G->edges[i].v)
                    {
                        break;
                    }
                    mark++;
                }

                // The variable temporary will contain the minimum distance of the Vertex and will hold onto that value.
                int temporary = G->vertices[mark].dist;

                // The Relax function is called to find the shortest path of a vertex.
                Relax(&S[index], G->vertices[mark], G->edges[i]);

                // If the distance of the vertex is shorter than temporary, we can then decrease its distance value in Q.
                if(temporary > G->vertices[mark].dist)
                {
                    // The for loop will go through each element in Q until it finds the vertex, and its values are updated.
                    for(int p = 0; p < MAX; p++)
                    {
                        if(Q[p].num == G->vertices[mark].num)
                        {
                            Q[p].dist = G->vertices[mark].dist;
                            Q[p].pred = G->vertices[mark].pred;
                        }
                    }
                }
            }
        }
        // We increment index.
        index++;
    }

    // We return the Vertex array S.
    return S;
}