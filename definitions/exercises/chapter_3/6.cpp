#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include "Queue.cpp"

using namespace std;

//Queue<int> l = {};
queue<int> l;

int main(){
  time_t begin = time(0);
  for(int i=0;i<100000000;i++){
    if(l.size() > 100000000){
      l.pop();
    } else if(l.size() == 0){
      l.push(i);
    } else if(random() % 2 == 0){
      l.push(i);
    } else {
      l.pop();
    }
  }
  while(l.size()>0){
    l.pop();
  }
  time_t end = time(0);

  cout << "Total time: " << difftime(end,begin) << endl;
  return 0;
}

//A time benchmark listed 23 seconds for n=10000000 vector queue operations, and 4 seconds for a queue object. 
