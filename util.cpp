#include <iostream>
#include "graph.h"
#include "main.h"
#include "heap.h"

using namespace std;

int arrSize(Vertex **v)
{
    int amount = 0;
    while(v[amount] != nullptr)
    {
        amount++;
    }
    return amount;
}

int arrAmount(Edge **e)
{
    int amount = 0;
    while(e[amount] != nullptr)
    {
        amount++;
    }
    return amount;
}

void INIT_SINGLE_SOURCE(Graph *G, Vertex *s)
{
    for(int i = 0; i < arrSize(G->vertices); i++)
    {
        G->vertices[i]->dist = 999;
        G->vertices[i]->pred = -1;
    }
    s->dist = 0;
}

void Relax(Vertex* u, Vertex &v, Edge *w)
{
    cout << "v dist: " << v.dist << "\tu dist: " << u->dist << "\tweight: " << w->weight << endl;
    if(v.dist > u->dist + w->weight)
    {
        int sum = u->dist + w->weight;
        v.dist = sum;
        cout << "NEW V DIST: " << v.dist << endl;
        v.pred = u->num;
    }
}

void Dijkstra(Graph *G, Vertex *s, int i)
{
    INIT_SINGLE_SOURCE(G, s);
    Vertex *S = new Vertex[n];

    Vertex *Q = new Vertex[1];
    Q[0].dist = s->dist;
    Q[0].num = s->num;
    Q[0].pred = s->pred;

    for(int i = 0; i < n; i++)
    {
        if(G->vertices[i]->num != Q[0].num)
        {
            Insert(Q, G->vertices[i]);
        }
    }

    int index = 0;
    while(Q[0].num != 0)
    {
        Vertex *u = new Vertex();
        u = ExtractMin(Q);
        S[index] = *u;
        for(int i = 0; i < m; i++)
        {
            if(G->edges[i]->u == S[index].num)
            {
                int mark = 0;
                for(int j = 0; j < n; j++)
                {
                    if(G->vertices[j]->num == G->edges[i]->v)
                    {
                        break;
                    }
                    mark++;
                }

                int temporary = G->vertices[mark]->dist;
                cout << "Temporary Before: " << temporary << endl;
                cout << "Relaxation on vertex " << S[index].num << endl;
                Relax(&S[index], *G->vertices[mark], G->edges[i]);
                cout << "Temporary After: " << temporary << endl;
                break;


                if(temporary < G->vertices[mark]->dist)
                {
                    DecreaseKey(Q, G->vertices[mark], temporary);
                }
            }
        }
        break;
        index++;
    }

    for(int i = 0; i < n; i++)
    {
        cout << "S[" << i << "]: " << S[i].num << " ";
    }
    cout << endl;
}