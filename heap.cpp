#include <iostream>
#include "heap.h"
#include "util.h"
#include "main.h"

using namespace std;


// the function Insert() will insert a vertex into the queue Q.
void Insert(Vertex* &Q, Vertex *x)
{
    // A temp Vertex array is created with a size of MAX + 1
    Vertex *temp = new Vertex[MAX + 1];
    for(int i = 0; i < MAX; i++)
    {
        // We initialize all the values of Q into the temp array.
        temp[i].num = Q[i].num;
        temp[i].dist = Q[i].dist;
        temp[i].pred = Q[i].pred;
    }
    // We then delete the memory of Q
    delete[] Q;

    // We set Q equal to temp, and make the last value of Q set to the values of the inserted vertex.
    Q = temp;
    Q[MAX].num = x->num;
    Q[MAX].pred = x->pred;
    Q[MAX].dist = x->dist;
    MAX++;
}

// The ExtractMin function will remove and return the element in Q with the shortest distance.
Vertex* ExtractMin(Vertex* &Q)
{
    // A temp Vertex is created.
    Vertex *temp = new Vertex();

    // The two integer varaibles pick and choice will help us in finding the element in Q with the shortest distance.
    int pick = 1000;
    int choice = 0;
    for(int i = 0; i < MAX; i++)
    {
        // If the distance in the node of Q is smaller than pick we initialize pick to that value, and the variable choice is set to i.
        if(Q[i].dist < pick)
        {
            pick = Q[i].dist;
            choice = i;
        }
    }

    // The values of Q in the index choice are copied onto the temp Vertex.
    *temp = Q[choice];
    Q[choice] = Q[MAX - 1];
    MAX--;

    // If we have gone through all but one element in the queue Q, we simply return the node Q[0].
    if(MAX == 0)
    {
        return &Q[0];
    }
    else
    {
        // Now that we have removed the element with the smallest distance, we can make Q smaller and have it only contain the values that have not been removed.
        Vertex *temp2 = new Vertex[MAX];
        for(int i = 0; i < MAX; i++)
        {
            if(Q[i].num != temp->num)
            {
                temp2[i] = Q[i];
            }
        }
        delete[] Q;

        // Q is set equal to temp2, and we return the vertex temp.
        Q = temp2;
        return temp;
    }
}


// minHeapify is used to make the queue Q into a min-heap priority queue.
void minHeapify(Vertex* &Q, int m, int n)
{
    // Using variables r and l, we will sort the queue Q into a min-heap, based off the distance values of the vertex.
    int r = Q[m].dist;
    int l = 2 * m;
    while(l <= n)
    {
        if(l < n && Q[l + 1].dist < Q[l].dist)
        {
            l = l + 1;
        }
        if(r < Q[l].dist)
        {
            break;
        }
        else if(r >= Q[l].dist)
        {
            Vertex *temp = new Vertex();
            temp = &Q[m];
            Q[l / 2] = Q[m];
            l = 2 * l;
        }
        Q[l / 2] = Q[m];
    }
    return;
}

// buildHeap() utilizes minHeapify() by looping through index of floor(n/2) until the last element of the queue.
void buildHeap(Vertex* &Q, int n)
{
    int k;
    for(k = n/2; k >= 0; k--)
    {
        minHeapify(Q, k, n);
    }
}

// DecreaseKey() is used to decrease the distance field of a vertex in Q.
void DecreaseKey(Vertex* &Q, Vertex v, int distance)
{
    // The variable mark is used to find the index of Q which contains the vertex that we want to decrease.
    int mark = 0;
    while(Q[mark].num != v.num)
    {
        mark++;
    }

    // We initialize the new distance.
    Q[mark].dist = distance;

    // Since we have altered the queue, we must use the buildHeap function in order to maintain the heap property.
    buildHeap(Q, MAX - 1);
}