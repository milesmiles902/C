#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
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

int medianofthree(vector<int> &avector,int first, int last){
  int fval=avector[first];
  int midval=avector[round((last-first)/2)+first];
  int lval=avector[last];
  int i=first;
  int j=last;
  int count=0;
  if(midval > fval && midval < lval || midval > lval && midval < fval ) fval = midval;
  else if(lval>fval && lval<midval || lval > midval && lval < fval) fval = lval;
  while(true){
    do {j--;count++;} while (avector[j] > fval);
    do {i++;count++;} while (avector[i] < fval);
    if(i<j) swap(avector[i],avector[j]);
    else return j+1;
  }
}

//recursive function that quicksorts through a given vector
void quickSort(vector<int> &avector, int first, int last, bool val) {
  int splitpoint;
  if(first<last){
    if(!val){
      cout << "Here" << endl;
      splitpoint = medianofthree(avector,first,last);
    } else {
      splitpoint = partition(avector,first,last);
    }
    quickSort(avector,first,splitpoint,val);
    quickSort(avector,splitpoint+1,last,val);
  }
}

int main() {
  // Vector initialized using a static array
  static const int arr[] = {54, 26, 93, 17, 77, 31, 44, 55, 20};
  vector<int> avector (arr, arr + sizeof(arr) / sizeof(arr[0]) );
  chrono::time_point<chrono::system_clock> start, end;
  start = chrono::system_clock::now();
  quickSort(avector,0,avector.size()-1,true);
  end = chrono::system_clock::now();
  chrono::duration<double> elapsed_sec = end-start;
  cout << "The duration for regular quick sort was: " << elapsed_sec.count() << endl;

  start = chrono::system_clock::now();
  quickSort(avector,0,avector.size()-1,false);
  end = chrono::system_clock::now();
  elapsed_sec = end-start;
  cout << "The duration for median-of-three quick sort was: " << elapsed_sec.count() << endl;

  printl(avector);

  return 0;
}

