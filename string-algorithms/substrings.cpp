#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    std::string S;
    char T[26];
    std::cin >> S;
    std::cin >> T;
    int n = S.length();
    int k;
    std::cin >> k;

    std::vector<int> Array(n);
    std::vector Cost(n,std::vector(n,0));

    for (int i=0;i<n;i++) {
        int a = S[i]-97;
        if (T[a]=='1') {
            Array[i] = 0;
        }
        else {
            Array[i] = 1;
        }
    }

    for (int i=0;i<n;i++) {
        int flag = 0;
        for (int j=i;j<n;j++) {
            flag+=Array[j];
            Cost[i][j] = flag;
        }
    }

    int count = 0;
    std::unordered_set<std::string> dictionary;
    for (int l=1;l<=n;l++) {
        for (int i=0;i+l<=n;i++){
            if (Cost[i][i+l-1]>k) continue;
            std::string sub = S.substr(i,l);
            if (dictionary.find(sub)==dictionary.end()) {
                dictionary.insert(sub);
                count++;
            }
        }
        dictionary.clear();
    }

    std::cout << count;

}
