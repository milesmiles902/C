#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

string infixToPostfix(string infixexpr){
  unordered_map<char,int> prec;
  prec['*']=3;
  prec['/']=3;
  prec['+']=2;
  prec['-']=2;
  prec['(']=1;
  stack<char> opStack;
  vector<char> postfixVector;
  string letsnums="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  for(char token:infixexpr){
    if(token==' '){
      continue;
    }
    else if(letsnums.find(token)<=letsnums.length()){
      postfixVector.emplace_back(token);
    } else if(token='('){
      opStack.push(token); 
    } else if(token==')'){
      char topToken;
      topToken = opStack.top();
      opStack.pop();
      while(topToken!='('){
        postfixVector.emplace_back(topToken);
        topToken=opStack.top();
        opStack.pop();
      }
    } else {
      while(!opStack.empty() && (prec[opStack.top()]>=prec[token])){
        postfixVector.emplace_back(opStack.top());
        opStack.pop();
      }
      opStack.push(token);
    }
  }
  while(!opStack.empty()){
    postfixVector.emplace_back(opStack.top());
    opStack.pop();
  }
  string s(postfixVector.begin(),postfixVector.end());
  return s;
}

int main(){
  cout <<"infix A*B+C*D\n" << "postfix: ";
  cout << infixToPostfix("A*B+C*D")<<endl;
}
