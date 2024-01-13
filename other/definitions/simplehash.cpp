#include <iostream>
#include <string>
using namespace std;

int hashfunc(string a, int tablesize){
  int sum=0;
  for(unsigned int pos=0; pos<a.length();pos++){
    sum+=int(a[pos]);
  }
  return sum%tablesize;
}

int main(){
  cout<<hashfunc("First!",10)<<endl;
  cout<<hashfunc("Second!",10)<<endl;
  cout<<hashfunc("Third!",10)<<endl;
}


