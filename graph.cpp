#include <iostream>
#include "graph.h"

using namespace std;

// The insertAtHead() function is used to created linked lists of each vertex, that contains the edges for that vertex.
void insertAtHead(adjList **list, int v, int weight)
{
    // We create a new adjList and intialize its values to insert at the head of this linked list.
    adjList *adj= new adjList();
    adj->vertex = v;
    adj->weight = weight;
    adj->next = *list;
    *list = adj;
}

// The printList() function is used to print all the edges that exist for each vertex.
void printList(adjList *list)
{
    // The variable a will be used so that we do not print an extra semicolon in our output.
    int a = 0;
    while(list != nullptr)
    {
        // If a is not equal to 0, then a semicolon is printed.
        if(a != 0)
        {
            cout << "; ";
        }
        cout << "(" << list->vertex << "; " << list->weight << ")";
        list = list->next;
        a++;
    }
    cout << endl;
}