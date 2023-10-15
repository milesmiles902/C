#include <iostream>
#include <string>
using namespace std;

string toStr(int n, int base){
  string convertString = "0123456789ABCDEF";
  if(n<base){
    return string(1,convertString[n]);
  } else {
    return toStr(n/base,base)+convertString[n%base];
  }
}

int main(){
  cout << toStr(1453,16);
}
