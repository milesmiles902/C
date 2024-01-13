#include <iostream>
#include <stack>
#include <string>

using namespace std;

string baseConverter(int decNumber, int base){
  string digits[]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
  
  stack<int> remstack;
  while(decNumber>0){
    int rem = decNumber % base;
    remstack.push(rem); 
    decNumber=decNumber/base;
  }
  string newString=""; 
  while(!remstack.empty()){
    newString.append(digits[remstack.top()]);
    remstack.pop();
  }
  return newString;
}

int main(){
  int mynum=25;
  cout << baseConverter(mynum,2) << endl;
  cout << baseConverter(mynum,16) << endl;
  cout << baseConverter(mynum,8) << endl;
  cout << baseConverter(256,16) << endl;
  cout << baseConverter(26,26) << endl;
  return 0;
}
