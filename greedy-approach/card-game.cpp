#include <iostream>

struct Char {
    int count = 0;
    char C;
};

void quicksort(Char A[], int start, int end) {
    int i=start, j=end;
    int p = A[start+(end-start)/2].count;
    while (i<=j) {
        while (A[i].count<p) i++;
        while (A[j].count>p) j--;
        if (i<=j) {
            std::swap(A[i],A[j]);
            i++;
            j--;
        }
    }
    if (start<j) quicksort(A,start,j);
    if (i<end) quicksort(A,i,end);
}

int main() {
    int n,k;
    std::cin >> n >> k;
    std::string str;
    std::cin >> str;

    Char *list = new Char[n];
    int len = 0;

    for (int i=0;i<n;i++) {
        //
        int idx = -1;
        for (int j=0;j<len;j++) {
            if (str[i]==list[j].C) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            idx = len;
            len++;
        }

        list[idx].C = str[i];
        list[idx].count++;
    }
    quicksort(list,0,len-1);

    int K = k;
    int idx = len-1;
    int Sum = 0;
    while (K>0) {
        if (K>list[idx].count) {
            K -= list[idx].count;
            Sum += (list[idx].count*list[idx].count);
            idx--;
        }
        else {
            Sum += (K*K);
            break;
        }
    }

    std::cout << Sum;

    delete [] list;

}
