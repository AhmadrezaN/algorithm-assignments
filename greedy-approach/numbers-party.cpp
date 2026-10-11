#include <iostream>

int main() {
    int n;
    std::cin >> n;
    long *list = new long[n];

    long long Sum = 0;
    for (int i=0;i<n;i++) {
        std::cin >> list[i];
        Sum += list[i];
    }

    long long SubSum = 0;
    long long answer = 0;
    if (n<2 || Sum%3!=0) {

    }

    else if (Sum != 0) {
        Sum /= 3;
        long long first = 0;

        for (int i=0;i<n;i++) {
            SubSum += list[i];

            if (SubSum == Sum) {
                first++;
            }
            if (SubSum == 2*Sum) {
                answer+=first;
            }
        }
    }

    else {
        long ZeroCount = 0;
        for (int i=0;i<n;i++) {
            SubSum+=list[i];
            if (SubSum==0) {
                ZeroCount++;
            }
        }
        answer = (ZeroCount-1)*(ZeroCount-2)/2;
    }

    std::cout << answer;


    delete [] list;
}
