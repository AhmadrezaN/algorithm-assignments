#include <iostream>

int main() {
    std::string str;
    std::cin >> str;
    int len = str.length();
    char L[3] = {'a','b','c'};

    for (int i=1;i<len;i++) {
        if (str[i]==str[i-1]) {
            for (int j=0;j<3;j++) {
                if (str[i] != L[j] && str[i+1] != L[j]) {
                    str[i] = L[j];
                    break;
                }
            }
        }
    }

    std::cout << str;

}
