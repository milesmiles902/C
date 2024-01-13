#include <iostream>
#include <queue>
#include <string>

using namespace std;

string hotPotatoe(string nameArray[],int num){
  queue<string> simqueue;
  int nameLength=nameArray->length();
  for(int i=0;i<nameLength;i++){
    simqueue.push(nameArray[i]);
  }
  while(simqueue.size() >1) {
    for(int i=0;i<num;i++){ 
      simqueue.push(simqueue.front());
      simqueue.pop();
    }
    simqueue.pop();
  }
  return simqueue.front();
}

int main(){
  string s[]={"Bill","David","Susan","Doug","Jane","Boyd","Scott"}; 
  cout << hotPotatoe(s,7) << endl;
  return 0;
}
