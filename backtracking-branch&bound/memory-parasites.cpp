#include <iostream>

int Midx(int Idx,int Jdx,int N) {
    return N*Idx + Jdx;
}

int  Max(int Matrix[],int Mark[], int n, int k) {
    if (k<0) {
        for (int i=0;i<n;i++) {
            if (Mark[i]==1){
                for (int j=0;j<n;j++) {
                    if (Mark[j]==1 && Matrix[Midx(i,j,n)]==0) {
                        return 0;
                    }
                    if (Mark[j]==0 && Matrix[Midx(i,j,n)]==1) {
                        return 0;
                    }
                }
            }
        }
        int sum = 0;
        for (int i=0;i<n;i++) {
            if (Mark[i]==1) {
                sum++;
            }
        }
        return sum;
    }
    int sum1=0,sum2=0;
    Mark[k] = 1;
    sum1 = Max(Matrix, Mark, n, k-1);
    Mark[k] = 0;
    sum2 = Max(Matrix, Mark, n, k-1);
    if (sum1<sum2) return sum2;
    return sum1;
}

int main() {
    int n;
    std::cin >> n;
    int *matrix = new int[n*n];
    int *mark = new int[n];

    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            std::cin >> matrix[Midx(i,j,n)];
        }
        mark[i] = -1;
    }

    std::cout << Max(matrix,mark,n,n-1);

    delete [] matrix;
    delete [] mark;
}
