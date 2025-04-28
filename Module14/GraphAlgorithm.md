# Graph Algorithm

# Dijkstra
- Complexity: O(V + E Log V)
- Implemtation
- Procedure: For finding a path from U to V (given no negative cyc;es in G):
    1. Maintain d[W] - distance from U to all vertices W. Initially, d[U] = 0 and d[W] = inf
    2. Procefss the vertices one by one in some order. Processing a vertex W means finding a new path by iterating over all edges of W and seeing if we can "relax" them to make a better d[W]. I.e. if ``current d[W] > d[z] + weight of edge X``, where X is the current edge between W and Z, we update ``d[W] = d[Z] + weight[X]``
    