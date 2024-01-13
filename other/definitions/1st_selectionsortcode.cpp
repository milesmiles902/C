#include <iostream>
#include <vector>

using namespace std;

vector<int> selectionSort(vector<int> avector){
  for(int fillslot = (avector.size() -1); fillslot >= 0; fillslot--){
    int positionOfMax = 0;
    for(int location = 1; location < fillslot + 1; location ++){
      if(avector[location] > avector[positionOfMax]){
        positionOfMax = location;
      }
    }
    int temp = avector[fillslot];
    avector[fillslot] = avector[positionOfMax];
    avector[positionOfMax] = temp;    
  }
  return avector;  
}

int main(){
  static const int arr[] = {53,26,93,17,77,31,44,565,25};
  vector<int> avector (arr, arr+sizeof(arr)/sizeof(arr[0]));
  vector<int> updatedAvector = selectionSort(avector);
  
  for(unsigned int i=0;i<updatedAvector.size(); i++){
    cout << updatedAvector[i] << " ";
  }
  cout << endl;
  return 0;  
}
