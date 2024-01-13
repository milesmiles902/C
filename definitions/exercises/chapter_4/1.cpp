#include <iostream>
#include <stack>
#include <string>

using namespace std;

void stackEval(int stackExpr){
  try {
    if(!stackExpr){throw string("Input is of zero charactes");}
  } catch (const std::exception& e){
    std::cout << "Error"<<endl;
  }
  stack<int> operandStack;
  while(stackExpr/2){
    if(stackExpr%2==0) {
      stackExpr/=2;
      operandStack.push(stackExpr);
    } else {
      stackExpr=(stackExpr-1)/2;
      operandStack.push(stackExpr);
    }
  }
  while(!operandStack.empty()){
    cout << operandStack.top() << endl;
    operandStack.pop();
  }
  cout << endl;
  return;
}

int main(){
  cout << "17" << endl;
  stackEval(17);
  cout << "45" << endl;
  stackEval(45);
  cout << "96" << endl;
  stackEval(96);
}
