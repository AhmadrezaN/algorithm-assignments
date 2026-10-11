#include <iostream>
#include <stack>
#include <vector>
#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> Input;
    std::cin.ignore();
    for (int i=0;i<n;i++) {
        std::string r;
        std::getline(std::cin,r, '\n');
        Input.push_back(r);
    }
    std::string goal;
    std::cin >> goal;

    auto *Rules = new std::vector<std::string>[n];
    int idx = 0;
    for (const auto & j : Input) {
        std::string s;
        std::stringstream ss(j);
        while (std::getline(ss, s, ' ')) {
            Rules[idx].push_back(s);
        }
        idx++;
    }

    std::stack<std::string> Q;
    Q.push(Rules[0][0]);
    bool Answer = false;
    while (!Q.empty()) {
        std::string str = Q.top();
        std::string temp = str;
        Q.pop();
        if (temp.length()>goal.length()) {
            continue;
        }
        if (temp==goal) {
            Answer = true;
            break;
        }
        else {
            for (int i=0;i<str.length();i++) {
                if (str[i]>='A' && str[i]<='Z') {
                    for (int j=0;j<n;j++) {
                        std::string sub = str.substr(i,1);
                        str = temp;
                        if (Rules[j][0]==sub) {
                            for (int k=1;k<Rules[j].size();k++) {
                                std::string add = str.replace(i,1,Rules[j][k]);
                                Q.push(add);
                                str = temp;
                            }
                        }
                    }
                }
            }
        }
    }
    if (Answer) std::cout << "yes";
    else std::cout << "no";
    delete [] Rules;
}
