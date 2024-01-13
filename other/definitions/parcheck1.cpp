#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool parChecker(string symbolString){
  stack<string> s;
  bool balanced = true;
  int index = 0;
  int str_len = symbolString.length();
  
  while(index < str_len && balanced){
    string symbol;
    symbol = symbolString[index];
    if(symbol=="("){
      s.push(symbol);
    } else {
        if(s.empty()){
          balanced = false;
        } else {
          s.pop();
        }
    }
  index = index + 1;
  }
  if(balanced&& s.empty()){
    return true;
  } else {
    return false;
  }
}

int main(){
  cout << parChecker("((()))") << endl;
  cout << parChecker("(()")<<endl;
}
