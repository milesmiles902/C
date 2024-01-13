#include <iostream>
using namespace std;


void mission(int missionaries,int cannibals){
  int i,j;
  if(missionaries > cannibals){
    cout << "Send the boat across the river with two or less missionaries" << missionaries/2 << "times.";
    cout << "Return the boat" << endl;
    cout << "Send the boat across the river with a missionary and cannibal " << cannibals << " times.";
  } else if(missionaries < cannibals){
    cout << "The cannibals consumed the missionaries." << endl;
  }
  else{
    cout << "Send the boat across the river with a single missionary and cannibal " << cannibals << " times." << endl; 
  }
}

int main(){
  int missionaries = 3;
  int cannibals = 3;
  cout << "The series of crossings that get the citizens across the river is: " << endl;
  mission(missionaries,cannibals);
  return 0;
}
