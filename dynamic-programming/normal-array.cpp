#include <iostream>

int MatrixIndex(int Nidx,int Kidx,int K) {
    return Nidx*K + Kidx;
}

void MatrixInitializer(unsigned long long Matrix[], int N,int K) {
    for (int i=0;i<N;i++) {
        for (int j=0;j<K;j++) {
            Matrix[MatrixIndex(i,j,K)] = 0;
        }
    }
    for (int i=1;i<N;i++) {
        long long unsigned x = (N-1)/i;
        Matrix[MatrixIndex(i,1,K)] = x;
    }
}

void FillMatrix(unsigned long long Matrix[], int N,int K) {
    for (int j=2;j<K;j++) {
        for (int i=1;i<N;i++) {
            for (int l=i;l<N;l+=i) {
                Matrix[MatrixIndex(i,j,K)] += Matrix[MatrixIndex(l,j-1,K)];
                Matrix[MatrixIndex(i,j,K)] %= 1000000007;
            }
        }
    }
}

int main() {
    int n,k;
    std::cin >> n >> k;
    int N = n+1, K = k+1;
    auto *matrix = new unsigned long long[N*K];

    MatrixInitializer(matrix,N,K);
    FillMatrix(matrix,N,K);

    std::cout << matrix[MatrixIndex(1,k,K)];

    delete [] matrix;
}
