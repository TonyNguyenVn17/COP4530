#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <vector>
#include <iostream>

#include "Hashmap.hpp"
#include "PriorityQueue.hpp"
#include "GraphBase.hpp"

const int MAXN = 100000;

class Graph : public GraphBase {
    public:
        Graph();
        ~Graph();
        void addVertex(std::string label) override;
        void removeVertex(std::string label) override;
        void addEdge(std::string label1, std::string label2, unsigned long weight) override;
        void removeEdge(std::string label1, std::string label2) override;
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) override;

    private:
        struct toEdge {
            std::string vertexName;
            unsigned long currentDist;
            
            bool operator<(const toEdge& other) const {
                return currentDist > other.currentDist; // for priority_queue to behave as min-heap
            }
            
            bool Valid(HashMap<std::string, unsigned long>& distanceMap) {
                return currentDist == distanceMap.getValue(vertexName); 
                // decides if distance of current vertex
                // if yes, it should be discarded
            }
        };

        struct dest {
            std::string label;
            unsigned long weight;
        };

        // variables
        HashMap<std::string, unsigned long> distance;
        HashMap<std::string, std::vector<dest>> neighborMap;

        PriorityQueue<toEdge> pq;
};

#endif