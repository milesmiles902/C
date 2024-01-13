#include <iostream>
using namespace std;

int foo(int tom){
  int fred = 0;
  for(int bill = 0; bill < tom+1; bill++){
    int barney = bill;
    fred = fred + barney;
  }
  return fred;
}

int main(){
  cout << foo(10);
  return 0;
}
