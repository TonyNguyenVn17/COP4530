#include <iostream>
#include <vector>
#include <string>
#include "Graph.hpp"  // Ensure this path is correct based on your project structure

int main() {
    /* GRAPH 1*/
    Graph g;
    std::vector<std::string> path;
    
    // Adding vertices
    g.addVertex("1");
    g.addVertex("2");
    g.addVertex("3");
    g.addVertex("4");
    g.addVertex("5");
    g.addVertex("6");

    // Adding edges
    g.addEdge("1", "2", 7);
    g.addEdge("1", "3", 9);
    g.addEdge("1", "6", 14);
    g.addEdge("2", "3", 10);
    g.addEdge("2", "4", 15);
    g.addEdge("3", "4", 11);
    g.addEdge("3", "6", 2);
    g.addEdge("4", "5", 6);
    g.addEdge("5", "6", 9);

    // Test Case 1: Shortest path from "1" to "5"
    std::cout << "Test case 1: Shortest path from 1 to 5\n";
    unsigned long distance = g.shortestPath("1", "5", path);

    if (distance != ULONG_MAX) {
        std::cout << "The shortest path from 1 to 5 is: " << distance << ".\n";
        std::cout << "Path: { ";

        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i != path.size() - 1) {  // If not the last element, print a comma
                std::cout << ", ";
            }
        }
        std::cout << " }\n";
    } else {
        std::cout << "No path exists from 1 to 5.\n";
    }

    path.clear(); // Clear the path vector for the next test case

    // Test Case 2: Shortest path from "1" to "4"
    std::cout << "\nTest case 2: Shortest path from 1 to 4\n";
    distance = g.shortestPath("1", "4", path);

    if (distance != ULONG_MAX) {
        std::cout << "The shortest path from 1 to 4 is: " << distance << ".\n";
        std::cout << "Path: { ";

        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i != path.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }\n";
    } else {
        std::cout << "No path exists from 1 to 4.\n";
    }

    path.clear();

    /* GRAPH 2 */
    Graph g2;
    std::vector<std::string> path2;

    // Adding vertices
    g2.addVertex("BSN");
    g2.addVertex("LIB");
    g2.addVertex("ENB");
    g2.addVertex("MSC");
    g2.addVertex("CAS");
    g2.addVertex("SUB");
    g2.addVertex("SUN");

    // Adding edges
    g2.addEdge("BSN", "LIB", 871);
    g2.addEdge("BSN", "CAS", 1672);
    g2.addEdge("BSN", "MSC", 2355);
    g2.addEdge("SUN", "SUB", 1265);
    g2.addEdge("LIB", "MSC", 1615);
    g2.addEdge("LIB", "SUN", 1847);
    g2.addEdge("ENB", "SUN", 2885);
    g2.addEdge("ENB", "CAS", 454);
    g2.addEdge("ENB", "LIB", 1078);

    // Test Case 1: Shortest path from "ENB" to "SUN"
    std::cout << "\nTest case 1: Shortest path from ENB to SUN\n";
    unsigned long distance2 = g2.shortestPath("ENB", "SUN", path2);

    if (distance2 != ULONG_MAX) {
        std::cout << "The shortest path from ENB to SUN is: " << distance2 << ".\n";
        std::cout << "Path: { ";
        for (size_t i = 0; i < path2.size(); ++i) {
            std::cout << path2[i];
            if (i != path2.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }\n";
    } else {
        std::cout << "No path exists from ENB to SUN.\n";
    }

    path2.clear();

    // Test Case 2: Shortest path from "LIB" to "CAS"
    std::cout << "\nTest case 2: Shortest path from LIB to CAS\n";
    distance2 = g2.shortestPath("LIB", "CAS", path2);

    if (distance2 != ULONG_MAX) {
        std::cout << "The shortest path from LIB to CAS is: " << distance2 << ".\n";
        std::cout << "Path: { ";
        for (size_t i = 0; i < path2.size(); ++i) {
            std::cout << path2[i];
            if (i != path2.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }\n";
    } else {
        std::cout << "No path exists from LIB to CAS.\n";
    }

    path2.clear();
    
    return 0;
}
