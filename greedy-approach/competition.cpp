#include <iostream>

int main() {
    int n;
    std::cin >> n;
    long *Y = new long[n];
    for (int i=0;i<n;i++) {
        std::cin >> Y[i];
    }
    std::string X;
    std::cin >> X;

    long x = 0;

    for (int i=0;i<n;i++) {
        if (X[i] == '0') {
            if (x == Y[i] || x == 0) {
                x = 0;
            }
            else {
                x ^= Y[i];
            }
        }
        else {
            if (x == 0 && Y[i]==0) {
                x = 0;
            }
            else {
                x ^= Y[i];
            }

        }
    }

    if (x==0) std::cout << "0";
    else std::cout << "1";

    delete [] Y;
}

