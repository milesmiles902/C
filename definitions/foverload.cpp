#include <iostream>
using namespace std;

void myfunct(int n){
  cout << "1 parameter: " << n << endl;
}

void myfunct(int n,int m){
  cout << "2 parameters: " << n;
  cout << " and " << m << endl;
}

int main(){
  myfunct(4);
  myfunct(5,6);
  myfunct(100);
  return 0;
}
