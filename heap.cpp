#include <iostream>
#include "heap.h"
#include "util.h"
#include "main.h"

using namespace std;

void Insert(Vertex* &Q, Vertex *x)
{
    Vertex *temp = new Vertex[MAX + 1];
    for(int i = 0; i < MAX; i++)
    {
        temp[i].num = Q[i].num;
        temp[i].dist = Q[i].dist;
        temp[i].pred = Q[i].pred;
    }
    delete[] Q;
    Q = temp;
    Q[MAX].num = x->num;
    Q[MAX].pred = x->pred;
    Q[MAX].dist = x->dist;
    MAX++;
}

Vertex* ExtractMin(Vertex* &Q)
{
    Vertex *temp = new Vertex();
    *temp = Q[0];
    Q[0] = Q[MAX - 1];
    MAX--;

    if(MAX == 0)
    {
        return &Q[0];
    }
    else
    {
        Vertex *temp2 = new Vertex[MAX];
        for(int i = 0; i < MAX; i++)
        {
            temp2[i] = Q[i];
        }
        delete[] Q;

        Q = temp2;
        return temp;
    }
}

void minHeapify(Vertex* &Q, int m, int n)
{
    int t = Q[m].dist;
    int j = 2 * m;
    while(j <= n)
    {
        if(j < n && Q[j + 1].dist < Q[j].dist)
        {
            j = j + 1;
        }
        if(t < Q[j].dist)
        {
            break;
        }
        else if(t >= Q[j].dist)
        {
            Q[j / 2].dist = Q[j].dist;
            j = 2 * j;
        }
        Q[j / 2].dist = t;
    }
    return;
}

void buildHeap(Vertex* &Q, int n)
{
    int k;
    for(k = n/2; k >= 0; k--)
    {
        minHeapify(Q, k, n);
    }
}

void DecreaseKey(Vertex* &Q, Vertex *v, int distance)
{
    int mark = 0;
    while(Q[mark].num != v->num)
    {
        mark++;
    }

    Q[mark].dist = distance;
    buildHeap(Q, n - 1);
}