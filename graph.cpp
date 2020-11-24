#include <iostream>
#include "graph.h"

using namespace std;

void insertAtHead(adjList **list, int v, int weight)
{
    adjList *adj= new adjList();
    adj->vertex = v;
    adj->weight = weight;
    adj->next = *list;
    *list = adj;
}

void printList(adjList *list)
{
    while(list != nullptr)
    {
        cout << list->vertex << ";" << list->weight << " ";
        list = list->next;
    }
    cout << endl;
}