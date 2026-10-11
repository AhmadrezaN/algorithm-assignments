#include <iostream>

bool Barabar(int X[],int Y[],int start, int end){

    if (end-start == 1) {
        if (X[start]==Y[start]) return true;
        else return false;
    }

    if (end-start == 2) {
        if ((X[start]==Y[start]) && (X[start+1])==Y[start+1]) {
            return true;
        }
        else return false;
    }

    if (end-start == 3) {
        int flag = 0,flaq = -1 ,flap = -1;
        for (int i=start;i<end;i++) {
            if (X[i] == Y[i]) {
                flag++;
            }
            else {
                bool k = false;
                for (int j=start;j<end;j++) {
                    if (X[i]==Y[j]) {
                        k = true;
                    }
                    if ((X[i]==X[j]) && (i!=j) && flaq<0) {
                        flaq = X[i];
                    }
                    if ((Y[i]==Y[j]) && (i!=j) && flap<0) {
                        flap = Y[i];
                    }
                }
                if (!k) return false;
            }
        }
        if (flap==flaq && (flap>0)) return true;
        if ((flag == 3) || (flag==0 && flap<0)) {
            return true;
        }
        else return false;
    }

    if (X[start] == Y[start]) {
        return Barabar(X,Y,start+1,end);
    }

    int j = -1;
    for (int i=start;i<end;i++) {
        if (X[start]==Y[i]) {
            j = i;
            break;
        }
    }
    if (j==-1) {
        return false;
    }

    for (int i=j;i>start;i--) {
        std::swap(Y[i],Y[i-1]);
    }

    int dist = j - start;

    if (dist%2==1) {
        std::swap(X[start+1],X[start+2]);
    }
    return Barabar(X,Y,start+1,end);
}

int main(){
    int n;
    std::cin >> n;

    int *X = new int[n];
    int *Y = new int[n];

    for (int i=0;i<n;i++) {
        std::cin >> X[i];
    }
    for (int i=0;i<n;i++) {
        std::cin >> Y[i];
    }

    if (Barabar(X,Y,0,n)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }

    delete [] X;
    delete [] Y;
}

