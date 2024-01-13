#include <iostream>
#include <cstdlib>
#include "Queue.cpp"

//The real life formulation of busses waiting to leave.

using namespace std;

int main(){
  int bus;
  int total_busses=5;
  Queue<int> amount_waiting = {};
  
  for(bus=1;bus<=total_busses;bus++){
    amount_waiting.push(bus);
  }
  
  while(!amount_waiting.empty()){
    cout << "The total amount of busses waiting are: " << amount_waiting.size() << endl;
    amount_waiting.pop();
  }

  return 0;
}
