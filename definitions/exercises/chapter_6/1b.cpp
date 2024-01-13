#include <iostream>
#include <vector>
using namespace std;

bool sequentialSearch(vector<int> avector, int item) {
    unsigned int pos = 0;
    bool found = false;

    while (pos < avector.size() && !found) {
        if (avector[pos] == item) {
            found = true;
        } else {
            pos++;
        }
    }

    return found;
}

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

int main() {
    cout << "A test on an ordered list of integers: " << endl;
    static const int arr[] = {0, 1, 2, 8, 13, 17, 19, 32, 42};
    vector<int> sorted_vector(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Sequential search: " << endl;
    cout << sequentialSearch(sorted_vector,1) << endl;
    cout << "Binary search: " << endl;
    cout << binarySearch(sorted_vector, 1) << endl;
    
    cout << "A test on an unordered list of integers: " << endl;
    static const int arr2[] = {1, 0, 2, 8, 13, 17, 19, 32, 42};
    vector<int> unsorted_vector(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    cout << "Sequential search: " << endl;
    cout << sequentialSearch(unsorted_vector,1) << endl;
    cout << "Binary search: " << endl;
    cout << binarySearch(unsorted_vector, 1) << endl;
    return 0;
}

