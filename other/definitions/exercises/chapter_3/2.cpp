#include <iostream>
#include <stack>
#include <string>

using namespace std;

int doMath(char op, int op1, int op2){
  if(op=='*'){
    return (op1*op2);
  } else if(op=='/'){
    return (op1/op2);
  } else if(op=='+'){
    return (op1+op2);
  } else {
    return (op1-op2);
  }
}

int postfixEval(string postfixExpr){
  try {
    if(postfixExpr.size() == 0){throw string("Input is of zero charactes");}
  } catch (const std::exception& e){
    std::cout << "Error"<<endl;
  }
  stack<int> operandStack;
  string nums = "0123456789";
  for(char i: postfixExpr){
    if((nums.find(i) <= nums.length())) {
      operandStack.push(int(i)-48);
    } else if(i!=' '){
      int operand2=operandStack.top();
      operandStack.pop();
      int operand1=operandStack.top();
      operandStack.pop();
      int results = doMath(i,operand1,operand2);
      operandStack.push(results);
    }
  }
  return operandStack.top();
}

int main(){
  cout << "7 8 _ 3 2 + /" << endl;
  cout << postfixEval("7 8 + 3 2 + /") << endl;
}
