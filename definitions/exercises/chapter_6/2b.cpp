#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

//The benchmark for an iterative and recursive binary search demonstrated a faster return for iterative.

bool binarySearch(vector<int> avector, int item) {
    int first = 0;
    int last = avector.size() - 1;
    bool found = false;

    while (first <= last && !found) {
        int midpoint = (first + last) / 2;
        if (avector[midpoint] == item) {
            found = true;
        } else {
            if (item < avector[midpoint]) {
                last = midpoint - 1;
            } else {
                first = midpoint + 1;
            }
        }
    }
    return found;
}

bool rbinarySearch(vector<int> alist, int item) {
      if (alist.size() == 0) {
        return false;
      } else {
        int midpoint = alist.size() / 2;
        if (alist[midpoint] == item) {
          return true;
        } else {
          if (item < alist[midpoint]) {
            vector<int> lefthalf(alist.begin(), alist.begin() + midpoint);
            return rbinarySearch(lefthalf, item);
          } else {
            vector<int> righthalf(
            alist.begin() + midpoint + 1, alist.end());
            return rbinarySearch(righthalf, item);
          }
        }
      }
}


int main() {
    int i,iter=1000000000; 
    static const int arr[] = {1, 2, 5, 6, 8, 9, 10, 11, 12, 15, 17, 18, 19};
    vector<int> sorted_vector(arr, arr + sizeof(arr) / sizeof(arr[0]));
    time_t begin = time(0);
    for(i=0;i<iter;i++){
      binarySearch(sorted_vector, 11);
    }
    time_t end = time(0);
    cout << "The time to complete 1,000,000 iterations for a iterative binary search: " << difftime(end,begin) << endl;

    begin = time(0);
    for(i=0;i<iter;i++){
      rbinarySearch(sorted_vector, 11);
    }
    end = time(0);
    cout << "The time to complete 1,000,000 iterations for a iterative binary search: " << difftime(end,begin) << endl;


    return 0;
}

