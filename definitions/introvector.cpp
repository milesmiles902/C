#include <iostream>
#include <vector>
using namespace std;

int main(){
  vector<int> intvector;
  intvector.reserve(50);
  
  for(int i=0;i<50;i++){
    intvector.push_back(i*i);
    cout << intvector[i] << endl;
  }
  return 0;
}
