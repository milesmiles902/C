#include <iostream>
using namespace std;

int vectsum(int numVect[]){
  int theSum = 0;
  for(int i=0;i<5;i++){
    theSum+=numVect[i];
  }
  return theSum;
}

int main(){
  int numVect[5] = {1,3,5,7,9};
  cout << vectsum(numVect) << endl;
  return 0;
}
