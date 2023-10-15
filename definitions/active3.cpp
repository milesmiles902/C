#include <iostream>
using namespace std;
#include <ctime>

int sumOfN3(int n){
  int sum_n = n*(n+1)/2;
  return sum_n;
}

int main(){
  cout << sumOfN3(10);
  return 0;
}
