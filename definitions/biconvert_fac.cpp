#include <iostream>
#include <stack>
#include <string>

using namespace std;

string divideBy2(int decNumber){
  stack<int> remstack;
  while(decNumber>0){
    int rem=decNumber%2;
    remstack.push(rem);
    decNumber=decNumber/2;
  }

  string binString="";
  while(!remstack.empty()){
    binString.append(to_string(remstack.top()));
    remstack.pop();
  }
  return binString;
}

int main(){
  cout << divideBy2(42) << endl;
  return 0;
}
