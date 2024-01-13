#include <iostream>
using namespace std;

int factorial(int fac){
  if(fac==1){
    return fac;
  }
  return factorial(fac-1)*fac;
}

int main(){
  int value = 5;
  cout << "The factorial of " << value << " is: " << endl;
  cout << factorial(value) << endl;
}
