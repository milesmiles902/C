#include <iostream>
using namespace std;

unsigned int ackermann(unsigned int m, unsigned int n){
  if(m==0){
    return n+1;
  }
  if(n==0){
    return ackermann(m-1,1);
  }
  return ackermann(m-1,ackermann(m,n-1));
}

int main(){
  cout << ackermann(1,2) << endl;
  return 0;
}
