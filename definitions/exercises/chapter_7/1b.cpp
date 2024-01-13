#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

vector<int> bubbleSort(vector<int> avector){
  for(int passnum = avector.size()-1;passnum>0;passnum-=1){
    for(int i=0;i<passnum;i++){
      if(avector[i]>avector[i+1]){
        int temp = avector[i+1];
        avector[i] = avector[i+1];
        avector[i+1]=temp;
      }
    }
  }
  return avector;
};

vector<int> insertionSort(vector<int> avector) {
    for (unsigned int index=1; index<avector.size(); index++) {

        int currentvalue = avector[index];
        int position = index;

        while (position>0 && avector[position-1]>currentvalue) {
            avector[position] = avector[position-1];
            position--;
        }

        avector[position] = currentvalue;
    }

    return avector;
}

int main(){
  int i,size = 500;
  int arr[size];
  for(i=0;i<size;i++){
    arr[i]=rand();
  }
  vector<int> avector (arr,arr+sizeof(arr)/sizeof(arr[0]));
  chrono::time_point<std::chrono::system_clock> start,end;
  start = chrono::system_clock::now();
  vector<int> bvector = bubbleSort(avector);
  end = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end-start;
  cout << "The duration to sort a list of 500 integers with bubble sort was: " << elapsed_seconds.count() << endl;

  for(i=0;i<size;i++){
    arr[i]=rand();
  }
  vector<int> ivector (arr,arr+sizeof(arr)/sizeof(arr[0]));
  start = chrono::system_clock::now();
  vector<int> kvector = insertionSort(ivector);
  end = chrono::system_clock::now();
  elapsed_seconds = end-start;
  cout << "The duration to sort a list of 500 integers with insertion sort was: " << elapsed_seconds.count() << endl;
   
  return 0;
}
