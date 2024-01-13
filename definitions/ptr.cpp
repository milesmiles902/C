#include <iostream>
using namespace std;

int main(){
  int varN = 100;
  int *ptrN = &varN;
  
  cout << "varN value: " << varN << endl;
  cout << "varN location: " << ptrN << endl;
  cout << "dereference ptrN: " << *ptrN << endl;

  return 0;
}
