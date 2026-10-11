#include <iostream>
#include <vector>
#include <stack>

int main() {
    std::string G,A,P;
    std::cin >> G;
    std::cin >> A;
    std::cin >> P;
    int glen = G.length();
    int alen = A.length();
    int m = P.length();

    //LCS
    std::vector C(glen+1,std::vector(alen+1,0));
    std::vector B(glen+1,std::vector(alen+1,0));
    // 1 for up
    // 2 for left
    // 3 for up-left
    // 4 for up or left
    for (int i=1;i<=glen;i++) {
        for (int j=1;j<=alen;j++) {
            if (G[i-1]==A[j-1]) {
                C[i][j] = C[i-1][j-1] + 1;
                B[i][j] = 3;
            }
            else if (C[i-1][j]>C[i][j-1]) {
                C[i][j] = C[i-1][j];
                B[i][j] = 1;
            }
            else if (C[i-1][j]<C[i][j-1]) {
                C[i][j] = C[i][j-1];
                B[i][j] = 2;
            }
            else if(C[i-1][j]==C[i][j-1]){
                C[i][j] = C[i-1][j];
                B[i][j] = 4;
            }
        }
    }

    std::string Solution;
    std::stack<std::pair<std::string,std::pair<int,int>>> plans;
    plans.push({"",{glen,alen}});
    while (!plans.empty()) {
        std::pair curr = plans.top();
        plans.pop();
        int i = curr.second.first;
        int j = curr.second.second;
        std::string s = curr.first;
        if (i==0 || j ==0) {
            Solution = s;
            break;
        }
        if (B[i][j]==4) {
            plans.push({s,{i-1,j}});
            plans.push({s,{i,j-1}});
        }
        else if (B[i][j]==2) {
            plans.push({s,{i,j-1}});
        }
        else if (B[i][j]==1) {
            plans.push({s,{i-1,j}});
        }
        else {
            s.push_back(G[i-1]);
            plans.push({s,{i-1,j-1}});
        }
    }
    if (Solution.empty()) {
        std::cout << 0;
    }
    else {
        int n = Solution.length();
        std::string solution;
        for (int i=0;i<n;i++) {
            solution.push_back(Solution[n-i-1]);
        }
        Solution = solution;

        if (n>=m) {
            bool v = true;
            while (v) {
                v = false;
                for (int i=0;i+m<n;i++) {
                    std::string sub = Solution.substr(i,m);
                    if (sub==P) {
                        Solution.erase(i,1);
                        v = true;
                        break;
                    }
                }
            }
            std::cout << Solution;
        }
        else {
            std::cout << Solution;
        }
    }
}
