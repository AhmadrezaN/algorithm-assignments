#include <iostream>

bool Hamsan(std::string A, std::string B,int lena, int lenb) {
    if (lena != lenb) {
        return false;
    }

    bool flag = true;
    for (int i=0;i<lena;i++) {
        if (A[i] != B[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        return true;
    }

    else {
        if (lena % 2 == 1) {
            return false;
        }
        int nln = lena/2;
        std::string A1,A2,B1,B2;
        A1 = A.substr(0,nln);
        A2 = A.substr(nln,lena);
        B1 = B.substr(0,nln);
        B2 = B.substr(nln,lena);

        flag = ( Hamsan(A1,B1,nln,nln) && Hamsan(A2,B2,nln,nln) ) ||
            ( Hamsan(A1,B2,nln,nln) && Hamsan(A2,B1,nln,nln) );
        return flag;
    }
}

int main() {
    std::string A,B;
    std::cin >> A;
    std::cin >> B;

    if (Hamsan(A,B,A.length(),B.length())) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
}
