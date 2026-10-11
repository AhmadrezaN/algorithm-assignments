#include <iostream>

long long mod(long long a, int b, int N) {
    long long r = 1;
    while (b>0) {
        if (b%2==1) {
            r = (r*a)%N;
        }
        a = (a*a)%N;
        b/=2;
    }
    return r;
}

int main() {
    int n;
    std::cin >> n;
    int *list = new int[n];
    for (int i=0;i<n;i++) {
        std::cin >> list[i];
    }
    int N = 998244353;
    long long p = 0, q = 1;
    long long I = 1;
    for (int i=0;i<n;i++) {
        p = (q+p)%N;
        p = (p*100)%N;
        q = (q*list[i])%N;
    }
    I = mod(q,N-2,N);
    long long J = I*p;
    J %= N;

    std::cout << J;

    delete [] list;
}
