#include <iostream>
#include <vector>
using namespace std;

int main(){
  vector<int> intvector;
  for(int i=0;i<50;i++){
    intvector.push_back(i*i);
    cout << intvector[i] << endl;
    cout << "capacity: " << intvector.capacity() << endl;
  }
  return 0;
}
