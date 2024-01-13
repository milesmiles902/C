#include <iostream>
#include <vector>

using namespace std;

vector<int> shortBubbleSort(vector<int> avector){
  bool exchanges = true;
  int passnum = avector.size();
  while(passnum > 0 && exchanges){
    exchanges = false;
    for(int i=0;i<passnum;i++){
      if(avector[i] > avector[i+1]){
        exchanges = true;
        int temp = avector[i];
        avector[i] = avector[i+1];
        avector[i+1] = temp;
      }
    }
    passnum = passnum -1;
  }
  return avector;
};

int main(){
  static const int arr[] = {20,30,90,50,50,22,11,100};
  vector<int> avector (arr, arr + sizeof(arr)/sizeof(arr[0]));
  vector<int> bvector = shortBubbleSort(avector);
  for(unsigned int i = 0;i<bvector.size();i++){
    cout << bvector[i] << " ";
  }
  return 0;
}
