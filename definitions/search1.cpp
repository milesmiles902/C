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

int main() {
    int arr[] = {1, 2, 32, 8, 17, 19, 42, 13, 0};
    vector<int> testvector(arr,arr+(sizeof(arr)/sizeof(arr[0])));

    cout << sequentialSearch(testvector, 3) << endl;
    cout << sequentialSearch(testvector, 13) << endl;

    return 0;
}

