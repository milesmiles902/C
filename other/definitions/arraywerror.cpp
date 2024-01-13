#include <iostream>
using namespace std;

int main(){
  int myarray[] = {2,4};
  int otherdata[]={777,777};
  for(int i=0;i<4;i++){
    myarray[i]=0;
    cout << "myarray[" << i << "]=";
    cout << myarray[i] << endl;
    cout << "add:" << &myarray[i] << endl;
  }

  for(int i=0;i<2;i++){
    cout << "otherdata[" << i << "]=";
    cout << otherdata[i] << endl;
    cout << "add:" << &otherdata[i] << endl;
  }
  return 0;
}
