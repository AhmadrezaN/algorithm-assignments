#include <iostream>

long gcd(long A, long B) {
    if (B>A) std::swap(A,B);
    long c;
    while (B>0) {
        c = A%B;
        A = B;
        B = c;
    }
    return A;
}

int main() {
    int n;
    std::cin >> n;

    long *list = new long[n];

    for (int i=0;i<n;i++) {
        std::cin >> list[i];
    }

    long g = gcd(list[0],list[1]);
    for (int i=2;i<n;i++) {
        g = gcd(g,list[i]);
    }

    if (g>1) {
        std::cout << "YES" << std::endl << 0;
    }
    else {
        bool *isEven = new bool[n];

        for (int i=0;i<n;i++) {
            if (list[i]%2==0) {
                isEven[i] = true;
            }
            else {
                isEven[i] = false;
            }
        }
        int count = 0;

        for (int i=0;i<n-1;i++) {
            if (!isEven[i] && !isEven[i+1]) {
                count++;
                isEven[i] = true;
                isEven[i+1] = true;
            }
        }
        for (int i=0;i<n-1;i++) {
            if ((!isEven[i] && isEven[i+1])||(isEven[i] && !isEven[i+1])) {
                count+=2;
                isEven[i+1] = true;
            }

        }
        std::cout << "YES\n" << count;
        delete [] isEven;
    }

    delete [] list;
}
