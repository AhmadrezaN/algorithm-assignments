#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#define INF 0x3f3f3f3f

struct Neighbor {
    int ID;
    int weight;
    Neighbor() {
        this->ID = -1;
        this->weight = -1;
    }
    Neighbor(int Name, int Length) {
        this->ID = Name;
        this->weight = Length;
    }
};

void Dijkstra(const std::vector<std::vector<Neighbor>>&G  ,int s, std::vector<long long> &dist) {
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        for (const Neighbor& neighbor : G[u]) {
            int v = neighbor.ID;
            int weight = neighbor.weight;
            if (currentDist + weight < dist[v]) {
                dist[v] = currentDist + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

long long BFS(int S, std::vector<std::vector<Neighbor>> &G,std::vector<long long> &P,int n,int m, long long l) {
    long long count = 0;

    // count vertex
    for (int i=0;i<n;i++) {
        if (P[i] == l) {
            //std::cout << 1;
            count++;
        }
    }

    // count edge
    std::queue<int> Q;
    Q.push(S);
    std::vector VisitedVertex(n,0);
    while (!Q.empty()) {
        int curr = Q.front();
        Q.pop();
        VisitedVertex[curr] = 2;

        for (const Neighbor& N  : G[curr]) {
            if (VisitedVertex[N.ID]==2) continue;
            if (VisitedVertex[N.ID]==0) {
                VisitedVertex[N.ID] = 1;
                Q.push(N.ID);
            }

            if (P[curr]>=l && P[N.ID]<l) {
                long long dist = l-P[N.ID];
                if (dist < N.weight) {
                    count++;
                }
            }

            else if (P[curr]<l && P[N.ID]>=l) {
                long long dist = l-P[curr];
                //std::cout << dist << "g\n";
                if (dist < N.weight) {
                    count++;
                }
            }

            else if (P[curr]<l && P[N.ID]<l) {
                long long distN = l-P[N.ID];
                long long distC = l-P[curr];
                if (distN<N.weight && distC<N.weight) {
                    if (distC+distN<N.weight &&
                        P[N.ID]+distN<P[curr]+N.weight-distN &&
                        P[curr]+distC<P[N.ID]+N.weight-distC){
                        count+=2;
                    }
                    else  if (distN+distC==N.weight){
                        count++;
                    }
                }
                else if (distN<N.weight && distC>N.weight) {
                    long long dist = N.weight-distN;
                    if (P[N.ID]+distN < P[curr]+dist) {
                        count++;
                    }
                }
                else if (distN>N.weight && distC<N.weight) {
                    long long dist = N.weight-distC;
                    if (P[curr]+distC < P[N.ID]+dist) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}


int main() {
    int n,m,s,l;
    std::cin >> n >> m >> s;
    std::vector<std::vector<Neighbor>> Graph;
    Graph.resize(n);
    for (int i=0;i<m;i++) {
        int a,b,w;
        std::cin >> a >> b >> w;
        a--; b--;
        Graph[a].push_back(Neighbor(b,w));
        Graph[b].push_back(Neighbor(a,w));
    }
    std::cin >> l;
    s--;
    std::vector<long long> SP(n, INF);
    Dijkstra(Graph,s,SP);
    std::cout << BFS(s,Graph,SP,n,m,l);

}
