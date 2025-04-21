#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <map>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

// Forward declaration
class Vertex;

// Edge class representing an undirected edge between two vertices
class Edge {
public:
    unsigned long weight;   // Weight of the edge
    Vertex* vertex1;        // One end of the edge
    Vertex* vertex2;        // Other end of the edge

    Edge(unsigned long w, Vertex* v1, Vertex* v2) : weight(w), vertex1(v1), vertex2(v2) {}
};

// Vertex class representing a vertex in the graph
class Vertex {
public:
    string name;                     // Name/label of the vertex
    list<Edge*> edges;              // List of edges connected to this vertex

    Vertex(const string& label) : name(label) {}
};

// Graph class implementing the Graph ADT
class Graph {
public:
    ~Graph(); // Destructor

    // Graph methods
    void addVertex(string label);
    void removeVertex(string label);
    void addEdge(string label1, string label2, unsigned long weight);
    void removeEdge(string label1, string label2);
    unsigned long shortestPath(string startLabel, string endLabel, vector<string>& path);

private:
    vector<Vertex*> vertices;        // List of all vertices
    vector<Edge*> edges;             // List of all edges

    // Helper functions
    Vertex* findVertex(const string& label);
    Edge* findEdge(Vertex* v1, Vertex* v2);
};

#endif
