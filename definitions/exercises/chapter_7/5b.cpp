#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

void print1(vector<int> avector){
  for(unsigned int i=0;i<avector.size();i++){
    cout << avector[i] << " ";
  }
}

vector<int> gapInsertionSort(vector<int> avector, int start, int gap){
  for(unsigned int i = start + gap; i < avector.size(); i+=gap){
    int currentvalue = avector[i];
    int position = i;
    while(position>=gap && avector[position-gap] > currentvalue){
      avector[position] = avector[position-gap];
      position -= gap;
    }
    avector[position] = currentvalue;
  }
  return avector;
}

vector<int> shellSort(vector<int> avector){
  int subvectorcount = avector.size()/2;
  chrono::time_point<chrono::system_clock> start,end;
  while(subvectorcount>0){
    start=chrono::system_clock::now();
    for(int startposition = 0; startposition<subvectorcount; startposition++){
      avector = gapInsertionSort(avector,startposition, subvectorcount);
    }
    cout << "After increments of size " << subvectorcount << " The vector is: " << endl;
    print1(avector);
    cout << endl;
    subvectorcount = subvectorcount/2;
    end=chrono::system_clock::now();
    chrono::duration<double> elapsed_sec = end-start;
    cout << "The duration was: " << elapsed_sec.count() << " seconds." << endl; 
  }
  return avector;
}

int main(){
  static const int arr[] = {2,23,534,64,56,33,21,34,5};
  vector<int> avector(arr,arr+sizeof(arr)/sizeof(arr[0]));
  print1(shellSort(avector));
  return 0;
}
