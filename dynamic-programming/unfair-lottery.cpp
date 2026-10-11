#include <iomanip>
#include <iostream>

int getIndex(int n, int a3, int a2, int a1) {
    return n*n*a3 + n*a2 + a1;
}

int main() {
    int n;
    int A0=0,A1=0,A2=0,A3=0;
    std::cin >> n;
    for (int i=0;i<n;i++) {
        int a;
        std::cin >> a;
        switch (a) {
            case 0: A0++; break;
            case 1: A1++; break;
            case 2: A2++; break;
            case 3: A3++; break;
            default:      break;
        }
    }

    int N = n+1;

    double *Matrix = new double[N*N*N];

    Matrix[getIndex(N,0,0,0)] = 0;

    bool solution = false;

    for (int a3=0; a3<=A3; a3++) {
        for (int a2=0; a2<=A2+A3; a2++) {
            for (int a1=0; a1<=A1+A2+A3; a1++) {
                int a0 = n - (a1+a2+a3);
                if (a0<0 || a0==n) continue;
                Matrix[getIndex(N,a3,a2,a1)] = (double)(n)/(n-a0);
                if (a3>0) {
                    Matrix[getIndex(N,a3,a2,a1)] +=  (((double)a3/(n-a0))*Matrix[getIndex(N,a3-1,a2+1,a1)]);
                }
                if (a2>0) {
                    Matrix[getIndex(N,a3,a2,a1)] += (((double)a2/(n-a0))*Matrix[getIndex(N,a3,a2-1,a1+1)]);
                }
                if (a1>0) {
                    Matrix[getIndex(N,a3,a2,a1)] += (((double)a1/(n-a0))*Matrix[getIndex(N,a3,a2,a1-1)]);
                }


                if (a3==A3 && a2==A2 && a1==A1) {
                    solution = true;
                    break;
                }
            }

            if (solution) break;
        }

        if (solution) break;
    }

    std::cout << std::fixed << std::setprecision(9) << Matrix[getIndex(N,A3,A2,A1)];



    delete [] Matrix;
}

