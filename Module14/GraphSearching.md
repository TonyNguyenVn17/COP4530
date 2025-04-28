# Graph Searching
## Some Definitions
- Subgraph: A subgraph S of graph G is a graph such that
    - Vertices of S i subset of vertices of G
    - Edges of S is subset of edges of G
- A **connected graph** is a graph where there exist a path between any pair of vertices.
    - Tree: trees are undirected connected graph with no cycle
    - Forest: a graph consisting of trees
    - Spanning tree: A spanning tree of a connected graph G is a subgraph S which is also a tree (no cycle). S is not unique unless G is also a tree

## DFS
- Time Complexity: O(V + E)
- The algorith traverses in prefix recursion (exploring a whole branch until a final node is reached) before backtracking
```
    bool visited[n+1];
    void dfs(int u) {
        if (visited[u]) retur;
        visited[u] = true;

        // visited subgraph recursively
        for (int v: neighbors[u]) { // assuming an adjacency list is used
            dfs(v);
        }
    }
```

## BFS
- Time Complexity: O(V + E)
- The algorithm traveres a whole level first before visiting the children. We use a queue to store nodes not visited
```
    // Assume 'neighbor' is an adjacency list: vector<vector<int>> neighbor;
    // Assume 'n' is the number of nodes (1-based index)

    bool visited[n + 1];  // Keeps track of which nodes we've already visited

    void bfs(int start) {
        queue<int> q;           // Create a queue for BFS
        visited[start] = true;  // Mark the starting node as visited
        q.push(start);          // Put the starting node into the queue

        while (!q.empty()) {    // Keep going while there are nodes to process
            int curNode = q.front();  // Look at the front node in the queue
            q.pop();                  // Remove it from the queue

            for (int v : neighbor[curNode]) {  // Check all neighbors of current node
                if (!visited[v]) {             // If neighbor hasn't been visited yet
                    visited[v] = true;         // Mark it as visited
                    q.push(v);                 // Add it to the queue to process later
                }
            }
        }
    }
```
**NOTE**: BFS can be used to find the shortes path between U & V in an unweighted graph G

## BFS vs DFS

| Applications | DFS | BFS |
| --- | ---| ---|
| Spanning forest, connected components, paths, cycles | yes | yes |
| Shortes paths |  | yes |
| Biconnected components | yes | |

