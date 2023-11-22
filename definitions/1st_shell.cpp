#include <iostream>
#include <vector>
using namespace std;

void print1(vector<int> avector){
  for(unsigned int i=0;i<avector.size();i++){
    cout << avector[i] << " ";
  }
  cout << endl;
}

vector<int> gapInsertionSort(vector<int> avector, int start, int gap){
  for(unsigned int i = start + gap; i < avector.size(); i+= gap){
    int currentvalue = avector[i];
    int position = i;
    while(position >= gap && avector[position-gap] > currentvalue){
      avector[position] = avector[position-gap];
      position-=gap;
    }
    avector[position]=currentvalue;
  }
  return avector;
}

vector<int> shellSort(vector<int> avector){
  int subvectorcount = avector.size()/2;
  while(subvectorcount > 0){
    for(int startposition = 0; startposition < subvectorcount; startposition++){
      avector = gapInsertionSort(avector,startposition,subvectorcount);
    }
    cout << "After increments of size " << subvectorcount << " The vector is: " << endl;
    print1(avector);
    subvectorcount = subvectorcount/2;
  }
  return avector;
}

int main(){
  static const int arr[] = {5,16,20,12,3,8,9,17,19,7};
  vector<int> avector (arr, arr+sizeof(arr)/sizeof(arr[0]));
  print1(shellSort(avector));
  return 0;
}
