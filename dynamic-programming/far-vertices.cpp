#include <iostream>

void POWER2(long long list[],int N,int M) {
    list[0] = 1;
    for (int i=1;i<=N;i++) {
        list[i] = 2*list[i-1];
        list[i]%=M;
    }
}

int Cidx(int i, int j, int N) {
    return (i)*(N+1) + (j);
}

void C(long long list[],int N, int M) {
    for (int i=0;i<=N;i++){
        for (int j=0;j<=N;j++) {
            list[Cidx(i,j,N)] = 0;
        }
    }
    for (int i=0;i<=N;i++){
        for (int j=0;j<=i;j++) {
            if (j == 0 || j == i)
                list[Cidx(i,j,N)] = 1;
            else
                list[Cidx(i,j,N)] = (list[Cidx(i-1,j-1,N)]+list[Cidx(i-1,j,N)])%M;;
        }
    }
}

int Midx(int h,int l,int N) {
    return (h-1)*(N-2)+(l-1);
}

void Match(long long Matrix[], long long power2[], int N, int M) {
    for (int j=0;j<=N;j++){
        for (int i=0;i<=N;i++) {
            if (j==0)
                Matrix[Cidx(i,j,N)] = 1;
            else if (j==1)
                Matrix[Cidx(i,j,N)] = (power2[i]-1)%M;
            else
                Matrix[Cidx(i,j,N)] = 0;
        }
    }
    for (int j=2;j<=N;j++){
        for (int i=1;i<=N;i++) {
            Matrix[Cidx(i,j,N)] = (Matrix[Cidx(i,j-1,N)]*Matrix[Cidx(i,1,N)])%M;
        }
    }
}

int main() {
    int n, mod;
    std::cin >> n >> mod;

    auto *power2 = new long long[n*n+1];
    auto *nCk = new long long[(n+1)*(n+1)];
    auto *match = new long long[(n+1)*(n+1)];

    POWER2(power2,n*n,mod);
    C(nCk,n,mod);
    Match(match,power2,n,mod);

    auto *DP = new long long[(n-2)*(n-2)];
    DP[Midx(1,1,n)] = 1;

    for (int h=1;h<=n-2;h++) {

        for (int l=1;l<=n-2;l++) {

            if (l>h) {
                DP[Midx(h,l,n)] = 0;
            }

            else if(l==h) {
                DP[Midx(h,l,n)] = power2[(h*(h-1))/2];
                DP[Midx(h,l,n)] %= mod;
            }

            else {
                DP[Midx(h,l,n)] = 0;
                int p = h-l;
                long long Sum = nCk[Cidx(h,l,n)];
                Sum %= mod;
                Sum *= power2[l*(l-1)/2];
                Sum %= mod;
                for (int i=1;i<=p;i++) {
                    long long sum = DP[Midx(p,i,n)];
                    sum %= mod;
                    sum *= match[Cidx(i,l,n)];
                    sum %= mod;
                    sum *= Sum;
                    sum %= mod;
                    DP[Midx(h,l,n)] += sum;
                }
            }
        }
    }

    long long Ans=0;
    for (int l=1;l<=n-2;l++) {
        long long sum =DP[Midx(n-2,l,n)];
        sum %= mod;
        sum *= match[Cidx(l,1,n)];
        sum %= mod;
        Ans += sum;
        Ans %= mod;
    }

    std::cout << Ans;

    delete [] match;
    delete [] DP;
    delete [] power2;
    delete [] nCk;
}
