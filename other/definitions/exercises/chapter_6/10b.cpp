#include <iostream>
#include <vector>
using namespace std;

vector<int> bubbleSort(vector<int> avector){
  for(int passnum = avector.size()-1;passnum>0;passnum-=1){
    for(int i=0;i<passnum;i++){
      if(avector[i]>avector[i+1]){
        int temp = avector[i];
        avector[i] = avector[i+1];
        avector[i+1] = temp;
      }
    }
  }
  return avector;
}

int main(){
  static const int arr[] = {25,23,12,56,1,123,6,2};
  vector<int> avector (arr,arr+sizeof(arr)/sizeof(arr[0]));
  
  vector<int> bvector = bubbleSort(avector);
  for(unsigned int i=0;i<bvector.size();i++){
    cout<<bvector[i]<< " ";
  }
  cout << endl;
  return 0;
}
