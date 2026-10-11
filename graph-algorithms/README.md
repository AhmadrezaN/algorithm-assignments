Here is a short summary of questions and solutions.

## Simple Paths
#### Problem Description
Given an undirected simple graph with $V$ vertices and $E$ edges where the degree of each vertex is at most 10, write a program to find the total number of simple paths (paths with no repeated vertices) starting from vertex 1. If the total number of simple paths $S$ exceeds $10^6$, the output should be capped at $\min(S, 10^6)$.
* **Time Limit:** 2 seconds
* **Memory Limit:** 1024 MB
* **Constraints:** $1 \le V \le 2 \cdot 10^{5}$, $0 \le E \le \min(2 \cdot 10^{5}, \binom{n}{2})$

#### Approach
This problem is solved using a **Depth-First Search (DFS) / Backtracking graph traversal** (`BackTrack` function):
1. **Graph Representation:** Vertices are modeled using a custom `Vertex` class tracking labels and neighbor lists.
2. **Path Exploration:** Starting from vertex 1, the recursive DFS explores valid unvisited neighbor vertices to count simple paths.
3. **Capping & Backtracking:** The visited state is dynamically toggled (marked true upon entry and reset upon return), and path counts are accumulated up to a ceiling limit of $10^6$ to prevent unnecessary overflow.

#### Complexity Analysis
* **Time Complexity:** Exponential in the worst case based on the number of simple paths, though bounded by vertex degree constraints ($\le 10$) and the $10^6$ output ceiling cap.
* **Space Complexity:** $O(V + E)$ auxiliary space to store graph vertices, neighbor vectors, and the visited tracker array.

#### C++ Solution Highlights
```cpp
int BackTrack(Vertex graph[], bool visited[], int vertex) {
    int count = 1;
    visited[vertex-1] = true;
    std::vector<int> neighbors = graph[vertex-1].getNeighbors();
    for (int & n : neighbors) {
        if (!visited[n-1]) {
            visited[n-1] = true;
            count += BackTrack(graph, visited, n);
            if (count >= 1000000) {
                return 1000000;
            }
            visited[n-1] = false;
        }
    }
    return count;
}

```
## Elephant Journey
#### Problem Description
You are positioned at starting coordinates $(x_1, y_1)$ on an $N \times N$ chessboard and need to reach a target destination at $(x_2, y_2)$ using only **bishop moves** (diagonal movements across any number of unoccupied squares). Some squares contain obstacles (`#`) which cannot be crossed or removed, while open squares are represented by (`.`). The objective is to find the minimum number of moves required to reach the destination, or output `-1` if reaching it is impossible.
* **Time Limit:** 6 seconds
* **Memory Limit:** 1024 MB
* **Constraints:** $2 \le N \le 1500$, $1 \le x_1, x_2, y_1, y_2 \le N$

#### Approach
This problem is solved using a **Breadth-First Search (BFS)** shortest path strategy on a grid:
1. **Parity Pre-check:** Before exploring paths, the code checks the Manhattan-like diagonal parity between the start and end coordinates. If their parities mismatch, a bishop can never bridge the gap, allowing for an immediate `-1` result.
2. **Queue-Based Graph Traversal:** Using a `std::queue<Coordinate>`, the algorithm explores diagonal directions (up-left, up-right, down-left, down-right) dynamically across possible distances $d$ up to $N$.
3. **Obstacle & State Marking:** Visited cells and obstacles (`#`) are tracked and managed to find the minimum steps toward the target coordinate.

#### Complexity Analysis
* **Time Complexity:** $O(N^3)$ or optimized grid traversal depending on diagonal step propagation across the $N \times N$ board.
* **Space Complexity:** $O(N^2)$ auxiliary space to store the grid matrix (`Greed`) and visit tracker flags (`Visit`).

#### C++ Solution Highlights
```cpp
if (std::abs(Si - Ei) % 2 != std::abs(Sj - Ej) % 2) {
    Min = -1;
} else {
    Greed[Midx(Si - 1, Sj - 1, n)] = 0;
    std::queue<Coordinate> Q;
    Q.push(S);

    while (!Q.empty()) {
        Coordinate curr = Q.front();
        Q.pop();
        // Traverse diagonal directions for bishop movements...
    }
    Min = Greed[Midx(Ei - 1, Ej - 1, n)];
}

```
## Advanced Transportation
#### Problem Description
Mr. Sanchez is designing a network of intercity transportation portals for Iran. The network needs to be fully connected with no cycles (a Minimum Spanning Tree - MST), and the company requires that for each portal (edge) in the graph, we must determine the minimum energy cost of an MST that *strictly includes* that specific portal.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $0 < n \le 3000$, $0 < m \le 2 \cdot 10^{5}$, $n - 1 \le m$, $0 < w \le 10^{9}$

#### Approach
This problem is solved using a combination of **Kruskal's Algorithm** and **Binary Lifting / Lowest Common Ancestor (LCA)**:
1. **Base MST Construction:** Kruskal's algorithm is first executed to find the global Minimum Spanning Tree and compute its base total cost (`MinCost`).
2. **Path Maximum Queries via LCA:** For any edge not currently in the MST, adding it creates a cycle. To maintain a spanning tree with minimum cost while forcing this edge, we must remove the maximum-weight edge along the unique path between its endpoints in the MST. This is efficiently computed using binary lifting and LCA tracking (`LCA` and `dfs` functions).
3. **Cost Evaluation:** If the edge is already part of the MST, the cost remains `MinCost`. Otherwise, the new MST cost is `MinCost - max_weight_on_path + edge_weight`.

#### Complexity Analysis
* **Time Complexity:** $O(m \log m + m \log n)$ due to sorting the edges for Kruskal's algorithm followed by LCA queries for each of the $m$ edges using binary lifting.
* **Space Complexity:** $O(n \log n + m)$ auxiliary space to store the graph structures, binary lifting parent/max tables, and edge collections.

#### C++ Solution Highlights
```cpp
// Kruskal's Algorithm for Base MST
EdgeSort(Sorting, 0, m - 1);
long long MinCost = 0;
DisjointSet A(n);
for (int i = 0; i < m; i++) {
    int weight = Sorting[i].first.first;
    int u = Sorting[i].second.first;
    int v = Sorting[i].second.second;
    if (A.Find(u) != A.Find(v)) {
        MinCost += weight;
        InMST[Sorting[i].first.second] = true;
        A.Union(u, v);
        MST[u].push_back({v, weight});
        MST[v].push_back({u, weight});
    }
}
dfs(n, 0, MST, Parent, DEPTH, MAX);

```
## Checkpoint
#### Problem Description
Your city has $n$ intersections and $m$ one-way roads. To ensure security, you need to build police checkpoints. A checkpoint at intersection $i$ can secure intersection $j$ if $i = j$ or if a police patrol car can travel from $i$ to $j$ and back to $i$. Given the different construction costs for a checkpoint at each intersection, find the **minimum total cost** to guarantee security for all intersections, along with the **number of ways** to achieve this minimum cost using the minimum number of checkpoints, modulo $10^9 + 7$.
* **Time Limit:** 2 seconds
* **Memory Limit:** 256 MB
* **Constraints:** $1 \le n \le 10^5$, $0 \le m \le 3 \times 10^5$

#### Approach
This problem is solved using **Strongly Connected Components (SCC)**:
1. **Condensation via Kosaraju's Algorithm:** Find all strongly connected components in the directed graph using a two-pass DFS (on graph $G$ and its transpose $G^T$). Intersections within the same SCC can mutually secure each other.
2. **Minimum Cost per Component:** For each SCC, identify the minimum construction cost among its member nodes. Sum these minimum costs to get the total minimum cost.
3. **Combinatorial Count:** Within each SCC, count how many intersections share this minimum cost. Multiply these counts together modulo $10^9 + 7$ to find the total number of optimal deployment combinations.

#### Complexity Analysis
* **Time Complexity:** $O(n + m)$ due to linear-time DFS traversals for finding strongly connected components and transposing the graph.
* **Space Complexity:** $O(n + m)$ auxiliary space to store the graph structures, color arrays, finish times, and component stacks.

#### C++ Solution Highlights
```cpp
std::vector<std::vector<int>> scc = SCC(G, G_T, n);

long long Sum = 0;
long long Count = 1;
int mod = 1000000007;

for (const auto& s : scc) {
    int min = max;
    for (int j : s) {
        if (Cost[j] <= min) min = Cost[j];
    }
    Sum += min;
    Sum %= mod;
    
    int count = 0;
    for (int j : s) {
        if (Cost[j] == min) count++;
    }
    Count *= count;
    Count %= mod;
}
std::cout << Sum << " " << Count;

```
## Server Optimization
#### Problem Description
A large data center consists of servers connected in a network with varying communication delays. To optimize energy consumption and improve performance, the management plans to sequentially turn off servers in a specified order. Before shutting down each server, the management needs to calculate the total sum of shortest communication paths between all remaining active servers.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $0 < n \le 500$ servers, and $n$ stages of server removal

#### Approach
This problem is solved efficiently using a **Reverse Floyd-Warshall Algorithm**:
1. **Incremental Processing (Backward Approach):** Instead of recalculating shortest paths after each deletion, the algorithm processes the deletion sequence in **reverse order** (from the last server to be removed back to the first).
2. **Dynamic Inclusion of Vertices:** Adding a vertex back into the network corresponds to a single step of the Floyd-Warshall all-pairs shortest path update.
3. **Summation over Active Nodes:** At each step, after updating shortest path distances (`Next`), it accumulates the sum of shortest paths exclusively among the currently active (turned on) servers.

#### Complexity Analysis
* **Time Complexity:** $O(n^3)$ total time since running the all-pairs shortest path updates across $n$ reverse inclusion steps takes $O(n^2)$ per step, matching the efficiency of Floyd-Warshall.
* **Space Complexity:** $O(n^2)$ auxiliary space to maintain the adjacency matrix and distance matrices (`Curr`, `Next`).

#### C++ Solution Highlights
```cpp
for (int q = n - 1; q >= 0; q--) {
    int k = Order[q] - 1;
    Turnedoff[k] = true;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int min = std::min(Curr[i][j], Curr[i][k] + Curr[k][j]);
            Next[i][j] = min;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Turnedoff[i] && Turnedoff[j]) {
                ans += Next[i][j];
            }
        }
    }
    // Update current matrix and store answer...
    Answer[q] = ans;
}

```
## Dudan
#### Problem Description
The country of Dudan consists of $n$ cities connected by bidirectional roads with specific lengths. Secret documents reveal that missile silos are located at any position—either a city or a point along a road—such that the shortest path distance from that location to the capital (located at city $s$) is exactly equal to $l$. The objective is to calculate the total number of missile silos present in Dudan.
* **Time Limit:** 2 seconds
* **Memory Limit:** 256 MB
* **Constraints:** $2 \le n, m \le 10^5$, $n-1 \le m \le n(n-1)/2$, $1 \le s \le n$, $1 \le w_i \le 1000$, $0 \le l \le 10^9$

#### Approach
This problem is solved using a combination of **Dijkstra's Algorithm** and **Breadth-First Search (BFS)** traversal:
1. **Shortest Paths Calculation:** Run Dijkstra's algorithm from the capital city $s$ to compute the shortest path distance from the capital to every other city in the graph.
2. **Vertex Silo Counting:** Directly count how many cities have a shortest path distance equal to $l$.
3. **Edge Silo Counting:** Traverse the edges using a BFS approach to check whether any points along the roads satisfy the exact distance requirement $l$ from the capital, accounting for edge weights and endpoint distances.

#### Complexity Analysis
* **Time Complexity:** $O(m \log n)$ due to Dijkstra's priority queue implementation, followed by a linear traversal over vertices and edges.
* **Space Complexity:** $O(n + m)$ auxiliary space to store the graph adjacency list, distance vectors, and traversal queues.

#### C++ Solution Highlights
```cpp
std::vector<long long> SP(n, INF);
Dijkstra(Graph, s, SP);
std::cout << BFS(s, Graph, SP, n, m, l);

```
## Positive Matrix (`Positive`)
#### Problem Description
You are given an $n \times n$ matrix $a$ with non-negative integers where the sum of its diagonal elements is greater than 0. A matrix $b$ is called strictly positive if every element $b_{ij} > 0$. The task is to determine whether there exists an integer $k \ge 1$ such that the matrix power $a^k$ is strictly positive, and output `YES` or `NO` accordingly.
* **Time Limit:** 1 second
* **Memory Limit:** 256 MB
* **Constraints:** $2 \le n \le 2000$, $0 \le a_{ij} \le 50$

#### Approach & Methodology
This problem is solved using a graph-based reachability and shortest-path-like relaxation approach (similar to Floyd-Warshall logic):
1. **Matrix Mapping & Initialization:** Zero entries in the matrix are treated as infinity (`INF`) to represent the absence of a direct connection, while non-zero values are tracked.
2. **Path Relaxation:** Using iterative updates similar to the Floyd-Warshall algorithm, the code checks whether all pairs of vertices can eventually reach each other with finite positive costs (i.e., whether paths exist between all node pairs).
3. **Reachability Verification (`isBig`):** If all entries become reachable (i.e., not equal to `INF`), it outputs `YES`; otherwise, it outputs `NO`.

#### Complexity Analysis
* **Time Complexity:** $O(n^3)$ in the worst case due to the triple-nested loops iterating up to $n$ for path relaxations.
* **Space Complexity:** $O(n^2)$ auxiliary space to store the adjacency and intermediate matrices (`Curr` and `Next`).

#### C++ Solution Highlights
```cpp
std::vector<std::vector<int>> Curr = Adj;
for (int k = 0; k < n; k++) {
    if (isBig) break;
    isBig = true;

    std::vector<std::vector<int>> Next = Curr;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int min = std::min(Curr[i][j], Curr[i][k] + Curr[k][j]);
            Next[i][j] = min;
            if (min == INF) isBig = false;
        }
    }
    Curr = Next;
}

if (!isBig) {
    std::cout << "NO";
} else {
    std::cout << "YES";
}

```
