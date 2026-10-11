#include <iostream>
#include <queue>

struct Coordinate {
    int x;
    int y;
    int path;
    Coordinate(int a, int b) {
        this->x = a;
        this->y = b;
        this->path = -2;
    }
};

int Midx(int i, int j, int N) {
    return (i*N)+j;
}

int main() {
    int n;
    int Si,Sj,Ei,Ej;
    std::cin >> n;
    std::cin >> Si >> Sj;
    std::cin >> Ei >> Ej;

    Coordinate S(Si-1,Sj-1);
    S.path = 0;

    int *Greed = new int[n*n];
    bool *Visit = new bool[n*n];

    for (int i=0;i<n;i++) {
        std::string line;
        std::cin >> line;
        for (int j=0;j<line.length();j++) {
            if (line[j]=='.') {
                Greed[Midx(i,j,n)] = -1;
                Visit[Midx(i,j,n)] = true;
            }
            else if(line[j]=='#') {
                Greed[Midx(i,j,n)] = -2;
                Visit[Midx(i,j,n)] = false;
            }
        }
    }

    int Min = 0;
    if (std::abs(Si-Ei)%2 != std::abs(Sj-Ej)%2) {
        Min = -1;
    }
    else {
        Greed[Midx(Si-1,Sj-1,n)] = 0;
        std::queue<Coordinate> Q;
        Q.push(S);

        while (!Q.empty()) {
            Coordinate curr = Q.front();
            Q.pop();
            Visit[Midx(curr.x,curr.y,n)] = false;

            if (curr.x==Ei-1 && curr.y==Ej-1) break;

            //down right
            for (int d=1;d<n;d++) {
                int I = curr.x+d , J = curr.y+d;
                if (I<0 || J<0 || I>=n || J>=n || Greed[Midx(I,J,n)]==-2) {
                    break;
                }
                if (Greed[Midx(curr.x,curr.y,n)]==Greed[Midx(I,J,n)]) {
                    break;
                }
                if (Greed[Midx(I,J,n)]==-1) {
                    Greed[Midx(I,J,n)] = curr.path+1;
                    Coordinate next = Coordinate(I,J);
                    next.path = Greed[Midx(I,J,n)];
                    Q.push(next);
                }
            }

            //up left
            for (int d=1;d<n;d++) {
                int I = curr.x-d , J = curr.y+d;
                if (I<0 || J<0|| I>=n || J>=n || Greed[Midx(I,J,n)]==-2) {
                    break;
                }
                if (Greed[Midx(curr.x,curr.y,n)]==Greed[Midx(I,J,n)]) {
                    break;
                }
                if (Greed[Midx(I,J,n)]==-1) {
                    Greed[Midx(I,J,n)] = curr.path+1;
                    Coordinate next = Coordinate(I,J);
                    next.path = Greed[Midx(I,J,n)];
                    Q.push(next);
                }
            }

            //down right
            for (int d=1;d<n;d++) {
                int I = curr.x+d , J = curr.y-d;
                if (I<0 || J<0|| I>=n || J>=n || Greed[Midx(I,J,n)]==-2) {
                    break;
                }
                if (Greed[Midx(curr.x,curr.y,n)]==Greed[Midx(I,J,n)]) {
                    break;
                }
                if (Greed[Midx(I,J,n)]==-1) {
                    Greed[Midx(I,J,n)] = curr.path+1;
                    Coordinate next = Coordinate(I,J);
                    next.path = Greed[Midx(I,J,n)];
                    Q.push(next);
                }
            }

            //up left
            for (int d=1;d<n;d++) {
                int I = curr.x-d , J = curr.y-d;
                if (I<0 || J<0|| I>=n || J>=n || Greed[Midx(I,J,n)]==-2) {
                    break;
                }
                if (Greed[Midx(curr.x,curr.y,n)]==Greed[Midx(I,J,n)]) {
                    break;
                }
                if (Greed[Midx(I,J,n)]==-1) {
                    Greed[Midx(I,J,n)] = curr.path+1;
                    Coordinate next = Coordinate(I,J);
                    next.path = Greed[Midx(I,J,n)];
                    Q.push(next);
                }
            }
        }
        Min = Greed[Midx(Ei-1,Ej-1,n)];
    }

    std::cout << Min;

    delete [] Greed;
    delete [] Visit;
}
