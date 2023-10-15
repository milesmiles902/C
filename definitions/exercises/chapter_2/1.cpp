#include <iostream>
#include <vector>
using namespace std;

int main(){
  int cnt,i=0;
  vector<int> myints = {1,2,3};
  for(i=0;i<myints.size();i++){
    cnt++;
    cout << "Operations: " <<  cnt << " for indice: " << myints[i] << endl;
    cnt--;
  }
  return 0;
}
