#include <iostream>
#include <vector>
#include <stack>

void quicksort(std::pair<int,int> A[], int start, int end) {
    int i=start, j=end;
    int p = A[start+(end-start)/2].second;
    while (i<=j) {
        while (A[i].second>p) i++;
        while (A[j].second<p) j--;
        if (i<=j) {
            std::swap(A[i],A[j]);
            i++;
            j--;
        }
    }
    if (start<j) quicksort(A,start,j);
    if (i<end) quicksort(A,i,end);
}

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

void DFS(std::vector<Vertex> &G, std::pair<int,int> f[], int color[], int n) {
    int time = 1;
    for(int i=0;i<n;i++) {
        if(color[i]==0) {
            std::stack<int> S;
            S.push(i);
            while (!S.empty()) {
                int cidx = S.top();
                time++;
                color[cidx] = 1;
                std::vector<int> neighbors = G[cidx].getNeighbors();
                bool isEnd = true;
                for(int & j : neighbors) {
                    if (color[j-1]==0) {
                        color[j-1] = 1;
                        S.push(j-1);
                        isEnd = false;
                    }
                }
                if (isEnd) {
                    color[cidx] = 2;
                    S.pop();
                    f[cidx].second = time;
                }
            }
        }
    }
}

std::vector<std::vector<int>> SCC(std::vector<Vertex> &G, std::vector<Vertex> &T, int n) {
    std::vector<std::vector<int>> Answer;

    // dfs on G:
    auto *f = new std::pair<int,int> [n];
    int *color = new int[n];
    for (int i=0;i<n;i++) {
        f[i].first = i;
        f[i].second = 0;
        color[i] = 0;
    }
    DFS(G,f,color,n);
    quicksort(f,0,n-1);

    // dfs on G transpose
    for (int i=0;i<n;i++) {
        color[i] = 0;
    }
    for(int k=0;k<n;k++) {
        int i = f[k].first;
        if (color[i]!=0) continue;
        std::vector<int> scc;
        scc.clear();
        std::stack<int> S;
        S.push(i);
        while (!S.empty()) {
            int cidx = S.top();
            color[cidx] = 1;
            std::vector<int> neighbors = T[cidx].getNeighbors();
            bool isEnd = true;
            for(int & j : neighbors) {
                if (color[j-1]==0) {
                    color[j-1] = 1;
                    S.push(j-1);
                    isEnd = false;
                }
            }
            if (isEnd) {
                color[cidx] = 2;
                scc.push_back(cidx);
                S.pop();
            }
        }
        Answer.push_back(scc);
    }
    delete [] color;
    delete [] f;

    return Answer;
}

int main() {
    int n;
    std::cin >> n;
    int max = 0;
    std::vector<int> Cost(n,-1);
    for (int i=0;i<n;i++) {
        std::cin >> Cost[i];
        if (Cost[i]>max) {
            max = Cost[i];
        }
    }
    std::vector<Vertex> G;
    G.resize(n);
    std::vector<Vertex> G_T;
    G_T.resize(n);

    int m;
    std::cin >> m;
    for (int i=0;i<m;i++) {
        int a,b;
        std::cin >> a >> b;
        G[a-1].AddNeighbor(b);
        G_T[b-1].AddNeighbor(a);
    }
    int mod = 1000000007;
    std::vector<std::vector<int>> scc = SCC(G,G_T,n);


    long long Sum = 0;
    long long Count = 1;
    for (const auto& s : scc) {
        int min = max;
        for (int j : s) {
            if (Cost[j]<=min) {
                min = Cost[j];
            }
        }
        Sum += min;
        Sum %= mod;
        int count = 0;
        for (int j : s) {
            if (Cost[j]==min) {
                count++;
            }
        }
        Count *= count;
        Count %= mod;
    }
    std::cout << Sum << " " << Count;
}
