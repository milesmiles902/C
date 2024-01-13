#include <iostream>
using namespace std;

double squareroot(double n){
  double root = n/2;
  for(int i=0;i<20;i++){
    root=(0.5)*(root+(n/root));
  }
  return root;
}

int main(){
  cout << squareroot(9) << endl;
  cout << squareroot(4563) << endl;
  return 0;
}
