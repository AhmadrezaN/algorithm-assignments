#include <cmath>
#include <iostream>

int main() {
    long long a,b;
    std::cin >> a >> b;

    int binA[512];
    int binB[512];

    int idx = 0;
    while (a>0) {
        int pos = a&1;
        binA[idx] = pos;
        a >>= 1;
        idx++;
    }

    int jdx = 0;
    while (b>0) {
        int pos = b&1;
        binB[jdx] = pos;
        b >>= 1;
        jdx++;
    }

    for (int i=idx;i<jdx;i++) {
        binA[i] = 0;
    }

    long long Max = 1;
    int I=-1;
    for (long i=jdx-1;i>=0;i--) {
        if (binA[i]!=binB[i]) {
            I = i;
            break;
        }
    }
    for (int i=0;i<=I;i++) {
        Max <<= 1;
    }

    std::cout << Max-1;

}
