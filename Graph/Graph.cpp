#include "Graph.hpp"

// Constructor & destructor
Graph::Graph() {
    
}

Graph::~Graph() {

}

void Graph::addVertex(std::string label) {
    distance.insert(label, ULONG_MAX);
}

void Graph::removeVertex(std::string label) {
    if (distance.contains(label)) {
        for (dest neighbor: neighborMap.getValue(label)) {
            // remove all mention of label from neighbors of that label
            std::vector<dest>& neighborNeighbors = neighborMap.getValue(neighbor.label);
            int idx = -1;
            for (int i = 0; i < (int) neighborNeighbors.size(); i++) {
                if (neighborNeighbors[i].label == label) {
                    idx = i;
                }
            }
            neighborNeighbors.erase(neighborNeighbors.begin() + idx);
        }
        distance.remove(label);
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    if (label1 == label2) { return; } // no self-loop
    if (!distance.contains(label1) || !distance.contains(label2)) { return; } // vertices dont exist

    // create in neighborMap if not created
    if (!neighborMap.contains(label1)) {
        neighborMap.insert(label1, std::vector<dest>());
    }
    if (!neighborMap.contains(label2)) {
        neighborMap.insert(label2, std::vector<dest>());
    }

    // add label2 to label1's neighbors if not already there
    std::vector<dest>& neighbors1 = neighborMap.getValue(label1);
    bool found1 = false;
    for (int i = 0; i < (int) neighbors1.size(); i++) {
        if (neighbors1[i].label == label2) {
            found1 = true;
            break;
        }
    }
    if (!found1) {
        neighbors1.push_back({label2, weight});
    }

    // add label1 to label2's neighbors if not already there
    std::vector<dest>& neighbors2 = neighborMap.getValue(label2);
    bool found2 = false;
    for (int i = 0; i < (int) neighbors2.size(); i++) {
        if (neighbors2[i].label == label1) {
            found2 = true;
            break;
        }
    }
    if (!found2) {
        neighbors2.push_back({label1, weight});
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    if (neighborMap.contains(label1)) {
        std::vector<dest>& neighbors1 = neighborMap.getValue(label1);
        int idx1 = -1;

        // find the index of label 2 in label 1 neighbor list - if it exist
        for (int i = 0; i < (int) neighbors1.size(); i++) {
            if (neighbors1[i].label == label2) {
                idx1 = i;
                break;
            }
        }
        if (idx1 != -1) {
            neighbors1.erase(neighbors1.begin() + idx1);
        }
    }

    if (neighborMap.contains(label2)) {
        std::vector<dest>& neighbors2 = neighborMap.getValue(label2);
        int idx2 = -1;

        // find the index of label 1 in label 2 neighbor list - if it exist
        for (int i = 0; i < (int) neighbors2.size(); i++) {
            if (neighbors2[i].label == label1) {
                idx2 = i;
                break;
            }
        }
        if (idx2 != -1) {
            neighbors2.erase(neighbors2.begin() + idx2);
        }
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    path.clear(); // clear the path first

    if (!distance.contains(startLabel) || !distance.contains(endLabel)) {
        return ULONG_MAX; // one of the nodes doesn't exist
    }

    // reset all distances to max
    for (std::string label : distance.getKeys()) {
        distance.insert(label, ULONG_MAX);
    }

    // create predecessor map to reconstruct path
    HashMap<std::string, std::string> previous;

    // set distance to startLabel as 0
    distance.insert(startLabel, 0);
    pq.push({startLabel, 0});

    // djikstra loop
    while (!pq.empty()) {
        toEdge current = pq.top(); // get closest node (based on distance)
        pq.pop();

        if (!current.Valid(distance)) {
            continue; // skip outdated distances
        }

        std::string u = current.vertexName;
        unsigned long distanceToU = current.currentDist;

        if (!neighborMap.contains(u)) { continue; } // u isn't here

        std::vector<dest>& neighbors = neighborMap.getValue(u);
        for (int i = 0; i < (int) neighbors.size(); i++) {
            // get label and weight of neighbors
            std::string v = neighbors[i].label;
            unsigned long weight = neighbors[i].weight;
            
            // test a new path - relaxation
            unsigned long alternateDist = distanceToU + weight;
            if (alternateDist < distance.getValue(v)) { // if new path is shorter than current path to v then replace it
                distance.insert(v, alternateDist);
                previous.insert(v, u);
                pq.push({v, alternateDist});
            }
        }
    }

    // reconstruct path
    if (distance.getValue(endLabel) == ULONG_MAX) {
        return ULONG_MAX; // no path exists
    }

    std::string current = endLabel;
    std::vector<std::string> tempPath; // contain the tempPathorary path
    while (current != startLabel) { // retrace the previous hashmap to reconstruct path
        tempPath.push_back(current);
        current = previous.getValue(current);
    }
    tempPath.push_back(startLabel);

    // reverse the path
    for (int i = tempPath.size() - 1; i >= 0; i--) {
        path.push_back(tempPath[i]);
    }

    return distance.getValue(endLabel);
}