#include <iostream>
#include <string>

#include "graph.h"
#include "util.h"
#include "main.h"
#include "heap.h"

using namespace std;

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
    MAX = 1;
    m = stoi(y);

    // We create and initialize an array of adjacency lists, one for each vertex.
    struct adjList **list = new adjList*[m];
    for(int i = 0; i < m; i++)
    {
        list[i] = nullptr;
    }

    // We create an array of edges and vertices based off the amount that has been inputted by the user. This will be used in the actual graph implementation.
    Edge **edges = new Edge*[m];
    for(int i = 0; i < m; i++)
    {
        edges[i] = nullptr;
    }

    Vertex **vertices = new Vertex*[n];
    for(int i = 0; i < n; i++)
    {
        vertices[i] = new Vertex();
        vertices[i]->num = (i + 1);
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

        edges[i] = new Edge();

        edges[i]->u = u;
        edges[i]->v = v;
        edges[i]->weight = w;

        insertAtHead(&list[u - 1], v, w);
    }

    auto *G = new Graph();
    G->edges = edges;
    G->vertices = vertices;

    auto *s = new Vertex();
    s->num = 1;

    int num = 0;

    Dijkstra(G, s, num);

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
            for(int i = 0; i < n; i++)
            {
                cout << "Vertex " << (i + 1) << ": ";
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
            // Since the find command was called, we know that the strings first, last, and bin were initialized. We now convert those values into integers.
            int start = stoi(first);
            int end = stoi(last);
            int flag = stoi(bin);

            cout << command << " " << start << " " << end << " " << flag << endl;

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

                }
                else if(flag == 1)
                {

                }
                else
                {
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
