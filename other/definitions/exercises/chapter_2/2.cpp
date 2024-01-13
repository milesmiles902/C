#include <iostream>
#include <unordered_map>

using namespace std;

int main(){
  int cnt,i=0;
  unordered_map<int,int> myints;
  for(i=0;i<3;i++){
    cnt++;
    myints.insert(make_pair(i,i));
    cout<< "Operations to insert a value into an unordered map: " << cnt << endl;
    cnt--;
    cnt++;
    if(myints.find(i)==myints.end()){
      cout << "Operations to find a value in an unordered map: " << cnt << " for hashtable value: " << i << endl;
    } else {
      cout << "Operations to find a value in an unordered map: " << cnt << " for hashtable value: " << i << endl;
    }
    cnt--;
  }
  return 0;
}
