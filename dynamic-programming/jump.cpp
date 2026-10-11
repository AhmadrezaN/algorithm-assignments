#include <iostream>

int main() {
    int n,k;
    int max = 0;
    std::cin >> n >> k;
    int *list = new int[n];
    for (int i=0;i<n;i++) {
        std::cin >> list[i];
        max+=list[i];
    }

    int *array = new int[n];
    array[0] = 0;
    array[1] = abs(list[1] - list[0]);

    for (int i=2;i<n;i++){
        int min = max;
        for (int j=1;j<=k;j++) if (i>=j){
            int jump = array[i-j] + abs(list[i]-list[i-j]);
            if (jump < min) {
                min = jump;
            }
        }
        array[i] = min;
    }

    std::cout << array[n-1];

    delete [] array;
    delete [] list;
}
