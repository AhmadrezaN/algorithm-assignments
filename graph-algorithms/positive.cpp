#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> Adj;
    Adj.resize(n);
    bool isBig = true;

    for (int i=0;i<n;i++) {
        Adj[i].resize(n);
        for (int j=0;j<n;j++) {
            int a;
            std::cin >> a;
            if (a!=0) Adj[i][j] = a;
            else {
                Adj[i][j] = INF;
                isBig = false;
            }
        }
    }

    std::vector<std::vector<int>> Curr = Adj;
    for (int k=0;k<n;k++) {
        if (isBig) break;
        isBig = true;

        std::vector<std::vector<int>> Next = Curr;
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                int min = std::min(Curr[i][j],Curr[i][k]+Curr[k][j]);
                Next[i][j] = min;
                if (min==INF) isBig = false;
            }
        }
        Curr = Next;
    }

    if (!isBig) {
        std::cout << "NO";
    }
    else std::cout << "YES";
}
