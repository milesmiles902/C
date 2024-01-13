#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

bool rbinarySearch(vector<int> alist, int start, int end, int item) {
  int midpoint = alist.size() / 2;
  if(start<=end){
    if (alist[midpoint] == item) {
      return true;
    } else if (item < alist[midpoint]) {
        return rbinarySearch(alist, start, midpoint-1, item);
    } else if (item > alist[midpoint]){
        return rbinarySearch(alist, end, midpoint+1, item);
    }
  }
  return false;
}

int main() {
    int i,size,iter=10000000; 
    static const int arr[] = {1, 2, 5, 6, 8, 9, 10, 11, 12, 15, 17, 18, 19};
    size=sizeof(arr)/sizeof(int);
    vector<int> sorted_vector(arr, arr+size);
    time_t begin = time(0);
    for(i=0;i<iter;i++){
      rbinarySearch(sorted_vector,0,size-1, 11);
    }
    time_t end = time(0);
    cout << "The time to complete 10000000 iterations for a iterative binary search: " << difftime(end,begin) << endl;

    return 0;
}

