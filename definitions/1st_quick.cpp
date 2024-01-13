#include <iostream>
#include <vector>
using namespace std;

void printl(vector<int> avector) {
  for (unsigned i=0; i<avector.size(); i++) {
    cout<<avector[i]<<" ";
  }
  cout<<endl;
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
void quickSort(vector<int> &avector, int first, int last) {
  int splitpoint;

  if (first<last) {
    splitpoint = partition(avector,first,last);

    quickSort(avector,first,splitpoint);
    quickSort(avector,splitpoint+1,last);

  }
}

int main() {
  // Vector initialized using a static array
  static const int arr[] = {54, 26, 93, 17, 77, 31, 44, 55, 20};
  vector<int> avector (arr, arr + sizeof(arr) / sizeof(arr[0]) );

  quickSort(avector,0,avector.size()-1);

  printl(avector);

  return 0;
}

