#include <iostream>
using namespace std;

int main(){
  int x = 12345;
  int *ptrx = &x;
  while (ptrx){
    cout << "Pointer ptrx points to " << ptrx << endl;
    ptrx = NULL;
  }
  cout << "Pointer ptrx points to nothing!" << endl;
}
