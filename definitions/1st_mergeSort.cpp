#include <iostream>
#include <vector>
using namespace std;

void print1(vector<int> avector){
  for(unsigned int i=0;i<avector.size();i++){
    cout << avector[i] << " ";
  }
  cout << endl;
}

vector<int> mergeSort(vector<int> avector){
  cout <<"Splitting ";
  print1(avector);
  if(avector.size()>1){
    int mid = avector.size()/2;
    vector<int> lefthalf(avector.begin(),avector.begin()+mid);
    vector<int> righthalf(avector.begin()+mid,avector.begin()+avector.size());

    lefthalf = mergeSort(lefthalf);
    righthalf = mergeSort(righthalf);
    unsigned i = 0;
    unsigned j = 0;
    unsigned k = 0;
    while(i<lefthalf.size() && j < righthalf.size()){
      if(lefthalf[i] < righthalf[j]){
        avector[k]=lefthalf[i];
        i++;
      } else {
        avector[k] = righthalf[j];
        j++;
      }
      k++;
    }
    while(i<lefthalf.size()){
      avector[k]=lefthalf[i];
      i++;
      k++;
    }
  }
  cout<<"Merging ";
  print1(avector);
  return avector;
}

int main(){
  static const int arr[] = {53,25,23,22,2222,21};
  vector<int> avector(arr,arr+sizeof(arr)/sizeof(arr[0]));
  print1(mergeSort(avector));
  return 0;
}
