#include <iostream>
using namespace std;

int sumOfN(int n){
  int theSum = 0;
  for (int i=0; i<n+1; i++){
    theSum = theSum + i;
  }
  return theSum;
}

int main(){
  cout << sumOfN(10);
  return 0;
}
