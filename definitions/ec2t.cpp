#include <iostream>
#include <ctime>
using namespace std;

int sumofN2(int n){
  clock_t begin = clock();
  int theSum = 0;
  for(int i = 0;i<n+1;i++){
    theSum = theSum + i;
  }
  clock_t end = clock();
  double elapsed_sec = double(end-begin)/CLOCKS_PER_SEC;
  cout << fixed << endl;
  cout << "Sum is " << theSum << " required "<< elapsed_sec << " seconds" << endl;
  return theSum;
}

int main(){
  for(int i = 0; i < 6; i++){
    sumofN2(10000);
  }
  return 0;
}
