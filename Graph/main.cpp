#include <iostream>
#include <tuple> // Only for testing

#include "Hashmap.hpp"
#include "PriorityQueue.hpp"
#include "Graph.hpp"

int main() {
    // Test Dijkstra - 1
    Graph g1;

    std::vector<std::string> vertices1 = { "1", "2", "3", "4", "5", "6" };
    std::vector<std::tuple<std::string, std::string, unsigned long>> edges1 = {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15},
        {"3", "4", 11}, {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9}
    };

    for (std::string& v : vertices1) {
        g1.addVertex(v);
    }

    for (auto& [from, to, weight] : edges1) {
        g1.addEdge(from, to, weight);
    }

    // test path 1
    std::vector<std::string> path1;
    unsigned long dist1 = g1.shortestPath("1", "5", path1);

    std::cout << "Distance: " << dist1 << '\n';
    std::cout << "Path: ";
    for (const auto& v : path1) {
        std::cout << v << " ";
    }
    std::cout << '\n';

    // Test Dijkstra - 2
    Graph g2;

    std::vector<std::string> vertices2 {
        "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"
    };

    struct EdgeStruct {
        std::string from;
        std::string to;
        unsigned long weight;
    };

    std::vector<EdgeStruct> edges2 {
        {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355}, {"SUN", "SUB", 1265},
        {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885},
        {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}
    };

    for (const auto& v : vertices2) {
        g2.addVertex(v);
    }
    for (const auto& e : edges2) {
        g2.addEdge(e.from, e.to, e.weight);
    }

    // Test path 2
    std::vector<std::string> path2;
    unsigned long dist2 = g2.shortestPath("ENB", "SUN", path2);

    std::cout << "Dist: " << dist2 << '\n';
    std::cout << "Path: ";
    for (const auto& v : path2) {
        std::cout << v << " ";
    }
    std::cout << '\n';

    // Test path 3
    std::vector<std::string> path3;
    unsigned long dist3 = g2.shortestPath("LIB", "CAS", path3);

    std::cout << "Dist: " << dist3 << '\n';
    std::cout << "Path: ";
    for (const auto& v : path3) {
        std::cout << v << " ";
    }
    std::cout << '\n';
}