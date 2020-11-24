#include <iostream>
#include <string>

#include "graph.h"
#include "util.h"
#include "main.h"
#include "heap.h"

using namespace std;

// We are creating global variables. These will be implemented all througout the program and are made global in the main.h file.
int n;
int m;
int MAX;

int main()
{
    // The first line of the inputted file is captured and set to string nm
    string nm;
    getline(cin, nm);

    // Since the first line contains our vertices and edges, we need to separate them. We will use strings x and y for this.
    string x;
    string y;
    for(int i = 0; i < nm.length(); i++)
    {
        // When a space is found in string nm, this indicates that we have gotten the first number, and can move on to get the next one.
        if(nm[i] == ' ')
        {
            // Since we found the breaking point of the string nm, the rest of the string contains the values for the number of edges.
            for(int j = i + 1; j < nm.length(); j++)
            {
                y += nm[j];
            }
            break;
        }

        // x appends each character of nm which is the number of vertices.
        x += nm[i];
    }

    // We convert x and y into integers for the vertices (n), and the edges (m).
    n = stoi(x);
    m = stoi(y);

    // We create and initialize an array of adjacency lists, one for each vertex.
    struct adjList **list = new adjList*[m];
    for(int i = 0; i < m; i++)
    {
        list[i] = nullptr;
    }

    // We are creating an array of Edge structs and Vertex structs. These will be used to create a Graph struct.
    Edge *edges = new Edge[m];
    Vertex *vertices = new Vertex[n];
    for(int i = 0; i < n; i ++)
    {
        // We assign each vertex a number.
        vertices[i].num = (i + 1);
    }

    // The for loop will iterate m times for the amount of edges that we have.
    for(int i = 0; i < m; i++)
    {
        // Since the next m lines contain values for the vertices, edges, and weights, we will capture the next m lines.
        string edge;
        getline(cin, edge);

        // Strings a, b, and c will be used to separate the string edge
        string a;
        string b;
        string c;

        // The nested for loop will act similarly to the one used to capture the values for n and m.
        for(int j = 0; j < edge.length(); j++)
        {
            // A blank space indicates that the string a has been captured.
            if(edge[j] == ' ')
            {
                for(int k = j + 1; k < edge.length(); k++)
                {
                    // A blank space indicates that the string b has been captured.
                    if(edge[k] == ' ')
                    {
                        for(int l = k + 1; l < edge.length(); l++)
                        {
                            // The string c is captured which means that all values have been captured now. We can break from all of the for loops now.
                            c += edge[l];
                        }
                        break;
                    }
                    b += edge[k];
                }
                break;
            }
            a += edge[j];
        }

        // We convert a, b, and c into integers named u, v, and w respectively.
        int u = stoi(a);
        int v = stoi(b);
        int w = stoi(c);

        // We initialize all the values of our edges such as the values for u, v, and weight.
        edges[i].u = u;
        edges[i].v = v;
        edges[i].weight = w;

        // We insert these edges into our adjacency list.
        insertAtHead(&list[u - 1], v, w);
    }

    // We continue reading the file until it reads stop.
    while(!cin.eof())
    {
        // A string called line will contain the line that is read from the file.
        string line;
        getline(cin, line);

        // String variables first, last, and bin will contain numeric values assuming the command is one of the find queries.
        string command;
        string first;
        string last;
        string bin;

        // This nested for loop will only go to the other for loops if the string command isn't "write" or "stop".
        for(int i = 0; i < line.length(); i++)
        {
            // A space in the string line indicates that the rest of the string contains numbers.
            if(line[i] == ' ')
            {
                for(int j = i + 1; j < line.length(); j++)
                {
                    if(line[j] == ' ')
                    {
                        for(int k = j + 1; k < line.length(); k++)
                        {
                            if(line[k] == ' ')
                            {
                                // bin contains the flag value for the command "find s t flag".
                                bin = line[k + 1];
                                break;
                            }

                            // last contains the ending vertex of Dijkstra's algorithm.
                            last += line[k];
                        }
                        break;
                    }

                    // first contains the starting vertex of Dijkstra's algorithm.
                    first += line[j];
                }
                break;
            }

            // Command will contain what the user wants to do specifically.
            command += line[i];
        }

        // If the command is equal to write, then the adjacency list is printed out for every vertex.
        if(command == "write")
        {
            cout << "Command: write" << endl;

            // the amount of vertices and edges are printed.
            cout << n << " " << m << endl;

            // We print the adjacency list using the printList() function.
            for(int i = 0; i < n; i++)
            {
                cout << (i + 1) << " : ";
                printList(list[i]);
            }
        }
        // If the command is equal to stop, the program is terminated and we have finished receiving commands.
        else if(command == "stop")
        {
            cout << "Command: stop" << endl;
            break;
        }
        // If the program goes here, that means that the find command has been called.
        else if(command == "find")
        {
            // The global variable MAX is initialized to one so that the queue in dijkstra's algorithm has at least one element.
            MAX = 1;

            // Since the find command was called, we know that the strings first, last, and bin were initialized. We now convert those values into integers.
            int start = stoi(first);
            int end = stoi(last);
            int flag = stoi(bin);

            // The command is printed.
            cout << "Command: " << line << endl;

            // If any of these conditions are met, it means that the user is trying to find the shortest distance from a starting vertex or end vertex that does not exist.
            if(end > n || end < 1 || start < 1 || start > n)
            {
                cout << "Error: one or more invalid nodes" << endl;

                // We will also check to see if the flag value the user inputted is valid as well. If not, an error message is printed.
                if(flag != 0 && flag != 1)
                {
                    cout << "Error: invalid flag value" << endl;
                }
            }
            // If the program goes here, that means the user has inputted valid starting and ending vertices.
            else
            {
                // We check to see which flag value the user inputs. This will determine if we print just the distance, or the actual path. If neither, an error message is printed.
                if(flag == 0)
                {
                    // If the requested vertices are the same, that means that the path is simply the node itself.
                    if(start == end)
                    {
                        cout << "Path: " << start << endl;
                    }
                    else
                    {
                        // We create a Graph struct which we initialize with out edges and vertices array.
                        auto *G = new Graph();
                        G->edges = edges;
                        G->vertices = vertices;

                        // We create a Vertex struct which will be our starting node.
                        auto *s = new Vertex();
                        s->num = start;

                        // An array of vertices SSS is created which will contain the shortest path to the ending vertex.
                        auto *SSS = new Vertex[n];

                        // We call Dijkstra(), and have it return a vertex array containing the shortest path to each node.
                        SSS = Dijkstra(G, s);

                        // The variable length will be set to zero, and we will initialize it to the length of the shortest path by using a loop.
                        int length = 0;
                        for(int i = n; i > 0; i--)
                        {
                            // If we have found the ending vertex, we set the length to the distance of the vertex node.
                            if(SSS[i].num == end)
                            {
                                length = SSS[i].dist;
                            }
                        }

                        // If the length is 999, that means that the node is unreachable, therefore we print an error message.
                        if(length == 999)
                        {
                            cout << "Error: node " << end << " not reachable from node " << start << endl;
                        }
                        else
                        {
                            // If the node is reachable, we will create an array of integers that will hold the vertex numbers.
                            int *arr = new int[25];

                            // Increment will be used to add a new value into the arr array.
                            int increment = 0;

                            // This for loop will move backwards so that we can find the ending vertex, and go to the predecessor of that vertex.
                            for(int i = n; i > 0; i--)
                            {
                                if(SSS[i].num == end)
                                {
                                    // We set this vertex number to the array, increment variable increment, and set end to the predecessor of the vertex.
                                    arr[increment] = SSS[i].num;
                                    increment++;
                                    end = SSS[i].pred;
                                }
                            }

                            // The last element of the array is the starting index.
                            arr[increment] = start;

                            // We print the path by using an array incrementing backwards, so that we print the path from thr starting vertex to the ending vertex.
                            cout << "Path: ";
                            for(int i = increment; i > 0; i--)
                            {
                                cout << arr[i] << ";";
                            }
                            cout << arr[0] << endl;

                            delete[] arr;
                        }

                        delete[] SSS;
                        delete G;
                    }
                }
                else if(flag == 1)
                {

                    // If the requested vertices are the same, that means that the length is 0.
                    if(start == end)
                    {
                        cout << "Length: 0" << endl;
                    }
                    else
                    {
                        // We create a Graph struct which we initialize with out edges and vertices array.
                        auto *G = new Graph();
                        G->edges = edges;
                        G->vertices = vertices;

                        // We create a Vertex struct which will be our starting node.
                        auto *s = new Vertex();
                        s->num = start;

                        // An array of vertices SSS is created which will contain the shortest path to the ending vertex.
                        auto *SSS = new Vertex[n];

                        // We call Dijkstra(), and have it return a vertex array containing the shortest path to each node.
                        SSS = Dijkstra(G, s);

                        // The variable length will be set to zero, and we will initialize it to the length of the shortest path by using a loop.
                        int length = 0;

                        // We capture the length of the path by finding the distance of the ending vertex.
                        for(int i = n; i > 0; i--)
                        {
                            if(SSS[i].num == end)
                            {
                               length = SSS[i].dist;
                            }
                        }

                        // If the length is 999, that means that the path is unreachable from the starting node.
                        if(length == 999)
                        {
                            cout << "Error: node " << end << " not reachable from node " << start << endl;
                        }
                        else
                        {
                            // We print the length of the path.
                            cout << "Length: " << length << endl;
                        }

                        delete[] SSS;
                        delete G;
                    }
                }
                else
                {
                    // If the nodes are valid but the flag value is incorrect, we will go to here.
                    cout << "Error: invalid flag value" << endl;
                }
            }
        }
        // If none of the proper commands are inputted, the program wil go here.
        else
        {

        }
    }

    return 0;
}
