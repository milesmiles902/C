#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

void printl(vector<int> avector) {
  for (unsigned i=0; i<avector.size(); i++) {
    cout<<avector[i]<<" ";
  }
  cout<<endl;
}

void insertionSort(vector<int> &avector){
  for(unsigned int index=1;index<avector.size();index++){
    int currentvalue = avector[index];
    int position = index;
    while(position>0 && avector[position-1]>currentvalue){
      avector[position] = avector[position-1];
      position--;
    }
    avector[position] = currentvalue;
  }
}

//function partitions vector depending on pivot value
int partition(vector<int> &avector, int first, int last) {
  int pivotvalue = avector[first];

  int rightmark = last;
  int leftmark = first+1;

  bool done = false;
  
    while(not done){
      while(leftmark<=rightmark and avector[leftmark]<=pivotvalue){
        leftmark++;
      }
      while(rightmark>=leftmark and avector[rightmark]>=pivotvalue){
        rightmark--;
      }
      if(rightmark<leftmark){
        done = true;
      }
      else{
        swap(avector[rightmark], avector[leftmark]);
      }
    }
  swap(avector[rightmark], avector[first]);
  return rightmark;
}

//recursive function that quicksorts through a given vector
void quickSort(vector<int> &avector, int first, int last, int n) {
  int splitpoint;
  if(avector.size() < n){
    insertionSort(avector);
    return;
  }
  if (first<last) {
    splitpoint = partition(avector,first,last);

    quickSort(avector,first,splitpoint,n);
    quickSort(avector,splitpoint+1,last,n);

  }
}

int main() {
  // Vector initialized using a static array
  static const int arr[] = {54, 26, 93, 17, 77, 31, 44, 55, 20};
  vector<int> avector (arr, arr + sizeof(arr) / sizeof(arr[0]) );
  chrono::time_point<chrono::system_clock> start, end;
  for(int i=0;i<avector.size();i++){
    start = chrono::system_clock::now();
    quickSort(avector,0,avector.size()-1,i);
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_sec = end-start;
    cout << "The elapsed time for a partition limit of " << i << " was: " << elapsed_sec.count() << endl;    
  }
  printl(avector);

  return 0;
}

