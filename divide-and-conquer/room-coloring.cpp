#include <iostream>
#include <cmath>

void quicksort(int A[], int start, int end) {
    int i=start, j=end;
    int p = A[start+(end-start)/2];
    while (i<=j) {
        while (A[i]<p) i++;
        while (A[j]>p) j--;
        if (i<=j) {
            std::swap(A[i],A[j]);
            i++;
            j--;
        }
    }
    if (start<j) quicksort(A,start,j);
    if (i<end) quicksort(A,i,end);
}

int binarysearch(int P[], int K, int value, bool B) {
    int start=0,end=K;
    while (start<end) {
        int mid = start+(end-start)/2;
        if (B) {
            if (P[mid] <= value) {
                start = mid + 1;
            }
            else {
                end = mid;
            }
        }
        else {
            if (P[mid] < value) {
                start = mid + 1;
            } else {
                end = mid;
            }
        }

    }
    return start;
}

long MinCost (int P[], long start, long end, int K, int X, int Y){
    long mid = start + (end-start)/2;
    int k_s = binarysearch(P, K, start, false);   // Lower bound
    int k_e = binarysearch(P, K, end-1, true);
    int sick = k_e - k_s;

    if (end - start == 1) {
        if (sick == 0) return X;
        else return sick*Y;
    }

    if (sick == 0) {
        return X;
    }

    long mul = (end-start)*sick*Y;
    long sub = MinCost(P,start,mid,K,X,Y) + MinCost(P,mid,end,K,X,Y);
    if (mul < sub) return mul;
    else return sub;
}

int main() {
    int n,k,X,Y;
    std::cin >> n >> k >> X >> Y;
    int *patient = new int[k];
    for (int i=0;i<k;i++) {
        std::cin >> patient[i];
        patient[i]--;
    }
    quicksort(patient, 0, k - 1);
    std::cout << MinCost(patient, 0, 1 << n, k, X, Y);

    delete[] patient;

}
