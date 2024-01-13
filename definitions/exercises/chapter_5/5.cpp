#include <iostream>
using namespace std;

int fibonacci(int n){
  if(n==0) return 0;
  if(n==1) return 1;
  if(n==2) return 2;
  return fibonacci(n-1)+fibonacci(n-2);
}

int main(){
  int fib = 10;
  cout << "The sum of " << fib << " Fibonacci steps is: " << fibonacci(fib) << endl;
  return 0;
}
