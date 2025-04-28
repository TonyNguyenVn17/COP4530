#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <limits> // Include for std::numeric_limits

#include "Hashmap.hpp"
#include "PriorityQueue.hpp"
#include "Graph.hpp"

// Define EdgeStruct here if it's specific to main or in a shared header if used elsewhere
struct EdgeStruct {
    std::string from;
    std::string to;
    unsigned long weight;
};

// Overload printGraph to accept vertices and edges directly for printing
void printGraphDetails(const std::string& graphName,
                       const std::vector<std::string>& vertices,
                       const std::vector<std::tuple<std::string, std::string, unsigned long>>& edges)
{
    std::cout << "--- Graph: " << graphName << " ---\n";
    std::cout << "Vertices: ";
    for (size_t i = 0; i < vertices.size(); ++i) {
        std::cout << vertices[i] << (i == vertices.size() - 1 ? "" : ", ");
    }
    std::cout << "\nEdges:\n";
    for (const auto& [from, to, weight] : edges) {
        std::cout << "  " << from << " -> " << to << " (" << weight << ")\n";
    }
    std::cout << "---------------------\n\n";
}

// Overload for the struct-based edge list
void printGraphDetails(const std::string& graphName,
                       const std::vector<std::string>& vertices,
                       const std::vector<EdgeStruct>& edges) // Use the defined struct
{
    std::cout << "--- Graph: " << graphName << " ---\n";
    std::cout << "Vertices: ";
    for (size_t i = 0; i < vertices.size(); ++i) {
        std::cout << vertices[i] << (i == vertices.size() - 1 ? "" : ", ");
    }
    std::cout << "\nEdges:\n";
    for (const auto& e : edges) {
        std::cout << "  " << e.from << " -> " << e.to << " (" << e.weight << ")\n";
    }
    std::cout << "---------------------\n\n";
}

int main() {
    // Test Dijkstra - 1
    Graph g1;

    std::vector<std::string> vertices1 = { "1", "2", "3", "4", "5", "6" };
    std::vector<std::tuple<std::string, std::string, unsigned long>> edges1 = {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15},
        {"3", "4", 11}, {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9}
    };

    // Print Graph 1 details
    printGraphDetails("G1", vertices1, edges1);

    for (const std::string& v : vertices1) {
        g1.addVertex(v);
    }

    for (const auto& [from, to, weight] : edges1) {
        g1.addEdge(from, to, weight);
    }

    // test path 1
    std::vector<std::string> path1;
    unsigned long dist1 = g1.shortestPath("1", "5", path1);

    std::cout << "--- Test Results for G1 ---\n"; // Added separator
    std::cout << "Test 1 (1 to 5):\n"; 
    std::cout << "Distance: " << dist1 << '\n';
    std::cout << "Path: ";
    for (const auto& v : path1) {
        std::cout << v << " ";
    }
    std::cout << "\n\n"; 

    // Test Dijkstra - 2
    Graph g2;

    std::vector<std::string> vertices2 {
        "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"
    };

    std::vector<EdgeStruct> edges2 {
        {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355}, {"SUN", "SUB", 1265},
        {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885},
        {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}
    };

    // Print Graph 2 details
    printGraphDetails("G2", vertices2, edges2);

    for (const auto& v : vertices2) {
        g2.addVertex(v);
    }
    for (const auto& e : edges2) {
        g2.addEdge(e.from, e.to, e.weight);
    }

    // Test path 2
    std::vector<std::string> path2;
    unsigned long dist2 = g2.shortestPath("ENB", "SUN", path2);

    std::cout << "--- Test Results for G2 ---\n"; // Added separator
    std::cout << "Test 2 (ENB to SUN):\n"; 
    std::cout << "Distance: " << dist2 << '\n'; 
    std::cout << "Path: ";
    for (const auto& v : path2) {
        std::cout << v << " ";
    }
    std::cout << "\n\n"; 

    // Test path 3
    std::vector<std::string> path3;
    unsigned long dist3 = g2.shortestPath("LIB", "CAS", path3);

    // No separator needed here as it's the same graph (G2)
    std::cout << "Test 3 (LIB to CAS):\n"; 
    std::cout << "Distance: " << dist3 << '\n'; 
    std::cout << "Path: ";
    for (const auto& v : path3) {
        std::cout << v << " ";
    }
    std::cout << "\n\n"; 
    
    // Test Dijkstra - 3 (Dense graph with multiple paths)
    Graph g3;
    std::vector<std::string> vertices3 = {"A", "B", "C", "D", "E", "F"};
    std::vector<std::tuple<std::string, std::string, unsigned long>> edges3 = {
        {"A", "B", 5}, {"A", "C", 10}, {"A", "D", 15}, 
        {"B", "C", 2}, {"B", "E", 20}, 
        {"C", "D", 3}, {"C", "E", 12},
        {"D", "E", 4}, {"D", "F", 8},
        {"E", "F", 5}
    };

    // Print Graph 3 details
    printGraphDetails("G3", vertices3, edges3);

    for (const auto& v : vertices3) {
        g3.addVertex(v);
    }
    for (const auto& [from, to, weight] : edges3) {
        g3.addEdge(from, to, weight);
    }

    // Test path 4 (Testing longer path through multiple vertices)
    std::vector<std::string> path4;
    unsigned long dist4 = g3.shortestPath("A", "F", path4);

    std::cout << "--- Test Results for G3 ---\n"; // Added separator
    std::cout << "Test 4 (A to F):\n";
    std::cout << "Distance: " << dist4 << '\n';
    std::cout << "Path: ";
    for (const auto& v : path4) {
        std::cout << v << " ";
    }
    std::cout << "\n\n"; 

    // Test Dijkstra - 4 (Graph with different structure)
    Graph g4;
    std::vector<std::string> vertices4 = {"P", "Q", "R", "S", "T"};
    std::vector<std::tuple<std::string, std::string, unsigned long>> edges4 = {
        {"P", "Q", 8}, {"P", "R", 15}, 
        {"Q", "R", 2}, {"Q", "S", 5},
        {"R", "S", 10}, {"R", "T", 12},
        {"S", "T", 4}
    };

    // Print Graph 4 details
    printGraphDetails("G4", vertices4, edges4);

    for (const auto& v : vertices4) {
        g4.addVertex(v);
    }
    for (const auto& [from, to, weight] : edges4) {
        g4.addEdge(from, to, weight);
    }

    // Test path 5 (Test another path calculation)
    std::vector<std::string> path5;
    unsigned long dist5 = g4.shortestPath("P", "T", path5);

    std::cout << "--- Test Results for G4 ---\n"; // Added separator
    std::cout << "Test 5 (P to T):\n";
    std::cout << "Distance: " << dist5 << '\n';
    std::cout << "Path: ";
    for (const auto& v : path5) {
        std::cout << v << " ";
    }
    std::cout << "\n\n"; 

    return 0; 
}