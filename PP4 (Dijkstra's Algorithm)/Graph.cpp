#include "Graph.hpp"

// Destructor: Cleans up all dynamically allocated memory
Graph::~Graph() {
    // Delete all Edge objects
    for (Edge* edge : edges) {
        delete edge;
    }

    // Delete all Vertex objects
    for (Vertex* vertex : vertices) {
        delete vertex;
    }
}

// Helper function to find a vertex by label
Vertex* Graph::findVertex(const string& label) {
    for (Vertex* vertex : vertices) {
        if (vertex->name == label) {
            return vertex;
        }
    }
    return nullptr;
}

// Helper function to find an edge between two vertices
Edge* Graph::findEdge(Vertex* v1, Vertex* v2) {
    for (Edge* edge : edges) {
        if ((edge->vertex1 == v1 && edge->vertex2 == v2) ||
            (edge->vertex1 == v2 && edge->vertex2 == v1)) {
            return edge;
        }
    }
    return nullptr;
}

// Adds a vertex to the graph
void Graph::addVertex(string label) {
    if (findVertex(label) != nullptr) {
        // Vertex already exists; do not add duplicate
        return;
    }
    Vertex* v = new Vertex(label);
    vertices.push_back(v);
}

// Removes a vertex and all associated edges from the graph
void Graph::removeVertex(string label) {
    Vertex* vertexToRemove = findVertex(label);
    if (vertexToRemove == nullptr) {
        // Vertex does not exist
        return;
    }

    // Iterate through a copy of the edge list to avoid modification during iteration
    vector<Edge*> edgesCopy(edges);
    for (Edge* edge : edgesCopy) {
        if (edge->vertex1 == vertexToRemove || edge->vertex2 == vertexToRemove) {
            removeEdge(edge->vertex1->name, edge->vertex2->name);
        }
    }

    // Remove the vertex from the vertices list
    vertices.erase(remove(vertices.begin(), vertices.end(), vertexToRemove), vertices.end());

    // Delete the vertex
    delete vertexToRemove;
}

// Adds an edge between two vertices with the specified weight
void Graph::addEdge(string label1, string label2, unsigned long weight) {
    if (label1 == label2) {
        // No self-loops allowed
        return;
    }

    Vertex* v1 = findVertex(label1);
    Vertex* v2 = findVertex(label2);

    if (v1 == nullptr || v2 == nullptr) {
        // Both vertices must exist
        return;
    }

    if (findEdge(v1, v2) != nullptr) {
        // Edge already exists
        return;
    }

    // Create a new edge and add it to the edges list
    Edge* newEdge = new Edge(weight, v1, v2);
    edges.push_back(newEdge);

    // Add the edge to both vertices' adjacency lists
    v1->edges.push_back(newEdge);
    v2->edges.push_back(newEdge);
}

// Removes the edge between two vertices
void Graph::removeEdge(string label1, string label2) {
    Vertex* v1 = findVertex(label1);
    Vertex* v2 = findVertex(label2);

    if (v1 == nullptr || v2 == nullptr) {
        // Both vertices must exist
        return;
    }

    Edge* edgeToRemove = findEdge(v1, v2);
    if (edgeToRemove == nullptr) {
        // Edge does not exist
        return;
    }

    // Remove the edge from both vertices' adjacency lists
    v1->edges.remove(edgeToRemove);
    v2->edges.remove(edgeToRemove);

    // Remove the edge from the edges list
    edges.erase(remove(edges.begin(), edges.end(), edgeToRemove), edges.end());

    // Delete the edge
    delete edgeToRemove;
}

// Computes the shortest path between two vertices using Dijkstra's Algorithm
unsigned long Graph::shortestPath(string startLabel, string endLabel, vector<string>& path) {
    Vertex* start = findVertex(startLabel);
    Vertex* end = findVertex(endLabel);

    if (start == nullptr || end == nullptr) {
        // One or both vertices do not exist
        return ULONG_MAX;
    }

    // Initialize maps for Dijkstra's algorithm
    map<Vertex*, bool> visited;
    map<Vertex*, unsigned long> distances;
    map<Vertex*, Vertex*> previous;

    // Initialize all distances to infinity and visited to false
    for (Vertex* vertex : vertices) {
        distances[vertex] = ULONG_MAX;
        visited[vertex] = false;
    }

    // Distance to the start vertex is 0
    distances[start] = 0;

    // Priority queue to select the vertex with the smallest tentative distance
    priority_queue<pair<unsigned long, Vertex*>, vector<pair<unsigned long, Vertex*>>, std::greater<pair<unsigned long, Vertex*>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        pair<unsigned long, Vertex*> currentPair = pq.top();
        pq.pop();

        unsigned long currentDistance = currentPair.first;
        Vertex* currentVertex = currentPair.second;

        if (visited[currentVertex]) {
            continue;
        }

        visited[currentVertex] = true;

        // If we've reached the destination, we can stop
        if (currentVertex == end) {
            break;
        }

        // Iterate through all adjacent edges
        for (Edge* edge : currentVertex->edges) {
            Vertex* neighbor = (edge->vertex1 == currentVertex) ? edge->vertex2 : edge->vertex1;

            if (!visited[neighbor]) {
                unsigned long newDistance = currentDistance + edge->weight;
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    previous[neighbor] = currentVertex;
                    pq.push({newDistance, neighbor});
                }
            }
        }
    }

    // If the end vertex was not reached, return infinity
    if (distances[end] == ULONG_MAX) {
        return ULONG_MAX;
    }

    // Reconstruct the shortest path
    path.clear();
    Vertex* current = end;
    while (current != start) {
        path.push_back(current->name);
        current = previous[current];
    }
    path.push_back(start->name);
    std::reverse(path.begin(), path.end()); // Use std::reverse from the standard library

    return distances[end];
}
