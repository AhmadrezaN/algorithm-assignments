#include <iostream>
#include <set>

long long CPUScheduling(long long Pros[],long long core[],int k,int f, int n,long long min,int idx){
    if (f==n || core[idx] > min){
        return core[idx];
    }
    std::set<long long> S;
    for (int i=0;i<k;i++) {
        if (S.find(core[i])==S.end()) {
            core[i] += Pros[f];
            int jdx;
            if (idx!=i && core[idx]<core[i]) {
                jdx = i;
            }
            else {
                jdx = idx;
            }
            long long sub = CPUScheduling(Pros,core,k,f+1,n,min,jdx);
            if (sub<min) {
                min = sub;
            }
            core[i]-=Pros[f];
            S.insert(core[i]);
        }
    }
    return min;
}

int main() {
    int n,k;
    std::cin >> n >> k;
    auto *list = new long long[n];
    long long Max = 0;
    for (int i=0;i<n;i++) {
        std::cin >> list[i];
        Max+=list[i];
    }
    auto *Core = new long long[k];
    for (int i=0;i<k;i++) {
        Core[i] = 0;
    }
    Core[0] = list[0];
    std::cout << CPUScheduling(list,Core,k,1,n,Max,0);
    delete [] Core;
    delete [] list;
}
