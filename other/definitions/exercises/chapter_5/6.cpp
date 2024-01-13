#include <iostream>
#include <stack>
using namespace std;

void moveDisk(stack<int> &fp, stack<int> &tp){
   fp.push(1);    
   tp.pop();
}

void moveTower(int height, stack<int> fromPole, stack<int> withPole, stack<int> toPole){
    if (height >= 1){
        moveTower(height-1, fromPole, withPole, toPole); //Recursive call
        moveDisk(fromPole, toPole);
        moveTower(height-1, withPole, toPole, fromPole); //Recursive call
    }
}

int main() {
    int height;
    stack<int> A;
    stack<int> B;
    stack<int> C;
    moveTower(height, A, B, C);
}
