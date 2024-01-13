#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
using namespace std;

class Task {
  public:
    Task(int time){
      timestamp = time;
      pages=(rand()%20)+1;
    }
    int getStamp(){
      return timestamp;
    }
    int getPages(){
      return pages;
    }
    int waitTime(int currenttime){
      return (currenttime-timestamp);
    }
  private:
    int timestamp;
    int pages;
};

class Printer{
  public:
    Printer(int pagesPerMinute){
      pagerate=pagesPerMinute;
      timeRemaining=0;
      working=false;
    }
    void tick(){
      if(working){
        timeRemaining--;
        if(timeRemaining<=0)
          working=false;
      }
    }
    bool busy(){
      return working;
    }
    void startNext(Task newTask){
     currentTask=newTask;
     timeRemaining=newTask.getPages()*60/pagerate;
     working=true;
    }
  private:
    int pagerate;
    Task currentTask = {0};
    bool working;
    int timeRemaining;
};

bool newPrintTask(){
  return (rand()%180+1)==180;
}

void simulation(int numSeconds,int pagesPerMinute){
  Printer labprinter(pagesPerMinute);
  queue<Task> printQueue;
  vector<int> waitingTimes;
  for(int i=0;i<numSeconds;i++){
    if(newPrintTask()){
      Task task(i);
      printQueue.push(task);
    }
    if(!labprinter.busy() &&!printQueue.empty()){
      Task nextTask = printQueue.front();
      printQueue.pop();
      waitingTimes.push_back(nextTask.waitTime(i));
      labprinter.startNext(nextTask);
    }
    labprinter.tick();
  }
  float total=0;
  for(int waitTime : waitingTimes)
    total+=waitTime;
  cout << "Average Wait "<<total/waitingTimes.size()<<" secs "<<printQueue.size()<<" tasks remaining."<<endl;
};

int main(){
  srand(time(NULL));
  for(int i=0;i<10;i++){
    simulation(3600,5);
  }
  return 0;
}
