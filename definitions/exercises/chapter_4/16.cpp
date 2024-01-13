#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Node {
  private:
    int data;
    Node *next;
  public:
    Node(int initdata){
      data=initdata;
      next=NULL;
  }

  int getData(){
    return data;
  }
  
  Node *getNext(){
    return next;
  }
  void setData(int newData){
    data = newData;
  }
  void setNext(Node *newnext){
    next=newnext;
  } 
};

class OrderedList {
  public:
    Node *head;
    OrderedList(){
      head=NULL;
    }
    bool search(int item){
      Node *current = head;
      bool found = false;
      bool stop = false;
      while(current !=NULL && !found && stop){
        if(current->getData() == item){
          found = true;
        } else {
          if(current->getData()>item){
            stop = true;
          } else {
            current=current->getNext();
          }
        }
     }
     return found;
  }
  void add(int item){
    if(head==NULL){
      Node *newNode = new Node(item);
      head = newNode;
    } else {
      Node *current = head;
      Node *previous = NULL;
      bool stop = false;
      while(current != NULL && !stop){
        if(current->getData() > item){
          stop = true;
        } else {
          previous=current;
          current=current->getNext();
        }
      }
      Node *temp=new Node(item);
      if(previous==NULL){
        temp->setNext(head);
        head = temp;
      } else {
        temp->setNext(current);
        previous->setNext(temp);
      }
    }
  }
};

int main(){
  int i,size=100000;
  time_t begin = time(0); 
  
  vector<int> vec_list(size); 
  for(i=0;i<size;i++){
    vec_list[i]=i;   
  }
  time_t end = time(0);
  cout << "Total time for a vector of 100,000 indices: " << difftime(end,begin) << endl;
  
  begin = time(0);
  OrderedList list;
  for(i=0;i<size;i++){
    list.add(i);
  }
  end = time(0);
  cout << "Total time for a list of 100,000 indices: " << difftime(end,begin) << endl;

  return 0;
}
