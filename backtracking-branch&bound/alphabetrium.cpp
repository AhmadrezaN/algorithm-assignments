#include <iostream>
#include <stack>

struct Word {
    int idx;
    int parent;
    int mark;

    Word() {
        this->idx = -2;
        this->parent = -2;
        this->mark = 0;
    }
};

bool isDiffis1(std::string A, std::string B) {
    if (A.length() != B.length()) return false;
    int diff = 0;
    for (int i=0;i<A.length();i++) {
        if (A[i]!=B[i]) diff++;
    }
    if (diff==1) return true;
    return false;
}

void Print(std::string word[],Word Idx[], int index, int n) {
    if (index == n) {
        return;
    }
    Print(word,Idx,Idx[index].parent,n);
    std::cout << word[index] << " ";
}

int main() {
    std::string Start,Goal;
    int n;
    std::cin >> Start >> Goal >> n;
    auto *Words = new std::string[n+1];
    Word *WordIdx = new Word[n+1];
    Words[n] = Start;
    for (int i=0;i<n;i++) {
        std::cin >> Words[i];
        WordIdx[i].idx = i;
    }
    WordIdx[n].idx = n;
    WordIdx[n].parent = -1;
    WordIdx[n].mark = 1;

    bool Answer = false;
    std::stack<Word> Stack;
    Stack.push(WordIdx[n]);
    Word answer;
    while (!Stack.empty()) {
        Word top = Stack.top();
        Stack.pop();

        if (Words[top.idx] == Goal) {
            Answer = true;
            answer.idx = top.idx;
            answer.parent = top.parent;
            answer.mark = top.mark;
            break;
        }

        for (int i=0;i<n;i++) {
            if (WordIdx[i].mark==0 && isDiffis1(Words[i],Words[top.idx])) {
                WordIdx[i].mark = 1;
                WordIdx[i].parent = top.idx;
                Stack.push(WordIdx[i]);
            }
        }
        WordIdx[top.idx].mark = 2;
    }

    if (Answer) {
        std::cout << Start << " ";
        Print(Words,WordIdx,answer.idx,n);
    }


    delete [] WordIdx;
    delete [] Words;
}
