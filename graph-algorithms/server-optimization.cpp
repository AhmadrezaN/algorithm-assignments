#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> Adj;
    Adj.resize(n);
    for (int i=0;i<n;i++) {
        Adj[i].resize(n);
        for (int j=0;j<n;j++) {
            std::cin >> Adj[i][j];
        }
    }
    std::vector<int> Order(n,-1);
    for (int i=0;i<n;i++) {
        std::cin >> Order[i];
    }

    //Initializing
    std::vector<std::vector<int>> Curr,Next;;
    Curr.resize(n);
    Next.resize(n);
    for (int i=0;i<n;i++) {
        Curr[i].resize(n);
        Next[i].resize(n);
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            Curr[i][j] = Adj[i][j];
        }
    }

    std::vector<long long> Answer(n,-1);
    std::vector<bool> Turnedoff(n,false);

    for (int q=n-1;q>=0;q--) {
        int k = Order[q]-1;
        Turnedoff[k] = true;
        long long ans = 0;
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                int min = std::min(Curr[i][j],Curr[i][k]+Curr[k][j]);
                Next[i][j] = min;
            }
        }
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                if (Turnedoff[i] && Turnedoff[j]) {
                    ans+=Next[i][j];
                }
            }
        }
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                Curr[i][j] = Next[i][j];
            }
        }
        Answer[q] = ans;
    }
    for (int i=0;i<n;i++) {
        std::cout << Answer[i] << " ";
    }
}
