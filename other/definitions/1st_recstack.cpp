#include <iostream>
#include <string>
#include <stack>
using namespace std;

stack<char> rStack;

string toStr(int n, int base){
  string convertString = "0123456789ABCDEF";
  while(n>0){
    if(n<base){
      rStack.push(convertString[n]);
    } else {
      rStack.push(convertString[n % base]);
    }
    n=n/base;
  }
  string res;
  while(!rStack.empty()){
    res = res + (string(1,rStack.top()));
    rStack.pop();
  }
  return res;
}

int main(){
  cout << toStr(1453,16);
}


