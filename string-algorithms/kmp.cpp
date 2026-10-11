#include <iostream>
#include <vector>

int main() {
    std::string S,T;
    std::cin >> S;
    std::cin >> T;
    int n = S.length();
    int m = T.length();

    std::vector P(m,-1);
    std::vector<std::pair<int,int>> Ans;
    P[0] = 0;
    int k = 0;
    for (int q=1;q<m;q++) {
        while (k > 0 && T[k]!=T[q]) {
            k = P[k-1];
        }
        if (T[k]==T[q]) {
            k++;
        }
        P[q] = k;
    }

    //KMP
    int q = 0, count = 0;
    for (int i=0;i<n;i++) {

        while (q>0 && T[q]!=S[i]) {
            q = P[q-1];
        }
        if (T[q]==S[i]) {
            q++;
        }
        if (q==m) {
            count++;
            Ans.push_back({i-m+1,i});
            q = P[q-1];
        }
    }

    int sol = 0;
    std::pair last = Ans[0];
    for (int i=1;i<Ans.size();i++) {
        std::pair curr = Ans[i];
        if (curr.first<=last.second) {
            sol++;
        }
        else {
            last = curr;
        }
    }
    std::cout << count-sol;
}
