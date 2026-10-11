#include <iostream>
#include <vector>

class Vertex {
private:
    int label;
    std::vector<int> neighbors;

public:
    Vertex() {
        this->label = -1;
        this->neighbors.clear();
    }
    void SetLable(int K) {
        this->label = K;
    }
    void AddNeighbor(int K) {
        this->neighbors.push_back(K);
    }
    std::vector<int> getNeighbors() {
        return this->neighbors;
    }
};

int BackTrack(Vertex graph[], bool visited[], int vertex) {
    int count = 1;
    visited[vertex-1] = true;
    std::vector<int> neighbors = graph[vertex-1].getNeighbors();
    for (int & n : neighbors) {
        if (!visited[n-1]) {
            visited[n-1] = true;
            count += BackTrack(graph,visited,n);
            if (count >= 1000000) {
                return 1000000;
            }
            visited[n-1] = false;
        }
    }
    return count;
}

int main() {
    int V,E;
    std::cin >> V >> E;

    auto *Graph = new Vertex[V];

    for (int i=0;i<E;i++) {
        int a,b;
        std::cin >> a >> b;
        Graph[a-1].SetLable(a);
        Graph[b-1].SetLable(b);
        Graph[a-1].AddNeighbor(b);
        Graph[b-1].AddNeighbor(a);
    }

    bool *Visited = new bool[V];
    for (int i=0;i<V;i++) {
        Visited[i] = false;
    }

    std::cout << BackTrack(Graph,Visited,1);

    delete [] Visited;
    delete [] Graph;
}
