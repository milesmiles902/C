#include <iostream>
#include <vector>
using namespace std;

int vectsum(vector<int> numVect){
  if(numVect.size()<=1){
    return numVect[0];
  }
  else {
    vector<int> slice(numVect.begin() + 1, numVect.begin()+numVect.size());
    return numVect[0] + vectsum(slice);
  }
}

int main(){
  int arr2[] = {1,3,5,7,9};
  vector<int> numVect(Arr2, arr2 + {sizeof(arr2) / sizeof(arr2[0])));
  cout << vectsum(numVect) << endl;
  return 0;
}
