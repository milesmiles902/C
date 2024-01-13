#include <iostream>
#include <queue>

using namespace std;

int main(){
  queue<int> newQueue;
  
  newQueue.push(3);
  newQueue.push(8);
  newQueue.push(15);

  cout << "Queue Empty? " << newQueue.empty() << endl;
  cout << "Queue Size: " << newQueue.size() << endl;
  cout << "Top element of the Queue: " << newQueue.front() << endl;
  newQueue.pop();
  cout << "Top Element of the Queue: " << newQueue.front() << endl;
  return 0;
}
