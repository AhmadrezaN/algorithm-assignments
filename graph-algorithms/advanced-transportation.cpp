#include <iostream>
#include <vector>
#include <cmath>

struct Pair {
    int first;
    int second;
};

class DisjointSet {
public:
    std::vector<int> Parent;
    int size;
    DisjointSet(int n) {
        Parent.resize(n);
        this->size = n;
        for (int i = 0; i < this->size; i++) {
            Parent[i] = i;
        }
    }
    int Find(int i) {
        if (Parent[i] != i) {
            Parent[i] = Find(Parent[i]);
        }
        return Parent[i];
    }
    void Union(int i, int j) {
        int irep = this->Find(i);
        int jrep = this->Find(j);
        this->Parent[irep] = jrep;
    }
};

void EdgeSort(std::vector<std::pair<Pair, Pair>> &E, int start, int end) {
    int i = start, j = end;
    int p = E[start + (end - start) / 2].first.first;
    while (i <= j) {
        while (E[i].first.first < p) i++;
        while (E[j].first.first > p) j--;
        if (i <= j) {
            std::swap(E[i], E[j]);
            i++;
            j--;
        }
    }
    if (start < j) EdgeSort(E, start, j);
    if (i < end) EdgeSort(E, i, end);
}

long long LCA(int u, int v, std::vector<int> &depth, std::vector<std::vector<long long>> &Max ,std::vector<std::vector<int>> &parent) {
    long long ans = -1;
    if (depth[u] != depth[v]) {
        if (depth[u] < depth[v]) std::swap(u, v);
        int k = depth[u] - depth[v];
        for (int i = 0; (1 << i) <= k; i++) {
            if ((k >> i) & 1) {
                ans = std::max(ans, Max[u][i]);
                u = parent[u][i];
            }
        }
    }
    if (u == v) return ans;
    int k = log2(depth[u]);
    for (int i = k; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            ans = std::max(Max[u][i], ans);
            ans = std::max(Max[v][i],ans);
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    ans = std::max(Max[u][0], ans);
    ans = std::max(Max[v][0],ans);
    return ans;
}

void dfs(int n, int u, std::vector<std::vector<Pair>> &Graph, std::vector<std::vector<int>> &parent, std::vector<int> &depth,std::vector<std::vector<long long>> &max) {
    for (auto x : Graph[u]) {
        int v = x.first;
        int weight = x.second;
        if (v == parent[u][0]) continue;
        parent[v][0] = u;
        max[v][0] = weight;
        depth[v] = depth[u] + 1;
        for (int j=1;j<=n;j++) {
            if (parent[v][j-1] == -1) continue;
            parent[v][j] = parent[parent[v][j - 1]][j - 1];
            max[v][j] = std::max(max[parent[v][j - 1]][j - 1], max[v][j - 1]);
        }
        dfs(n,v, Graph, parent, depth, max);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<Pair, Pair>> Sorting, Edges;
    std::vector<bool> InMST(m, false); // Fixed Syntax

    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--; v--;
        Edges.push_back({{w, i}, {u, v}});
        Sorting.push_back({{w, i}, {u, v}});
    }

    std::vector Parent(n,std::vector<int>(n+1,-1));
    std::vector MAX(n,std::vector<long long>(n+1,-1));
    std::vector DEPTH(n,0);
    std::vector<std::vector<Pair>> MST(n);

    // Kruskal
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

    dfs(n,0, MST, Parent, DEPTH, MAX);

    for (int i = 0; i < m; i++) {
        int weight = Edges[i].first.first;
        int u = Edges[i].second.first;
        int v = Edges[i].second.second;
        if (InMST[Edges[i].first.second]) {
            std::cout << MinCost << std::endl;
        }
        else {
            std::cout << MinCost - LCA(u, v, DEPTH, MAX, Parent) + weight << std::endl;
        }
    }
}
