#include <iostream>
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
  void append(int item){
    Node *temp = new Node(item);
    Node *current = head; 
    Node *previous = NULL;
    while(current != NULL){
      previous = current;
      current = current->getNext(); 
    }
    temp->setNext(current);
    previous->setNext(temp);
  } 

  int index(int item){
    Node *current = head;
    int count = 1;
    while(current != NULL){
      if(current->getData() == item){
        return count;
      }
      count++;
      current = current->getNext();
    }
      return count;          
  }

  void pop(){
    Node *current = head;
    Node *previous = NULL;
    while(current->getNext()!=NULL){
      previous = current;
      current = current->getNext();
    }
    previous->setNext(current->getNext());
  }
  
  void insert(int item, int pos){
    Node *current = head;
    Node *temp = new Node(item);
    while(pos--){
      current=current->getNext();
    }
    temp->setNext(current->getNext());
    current->setNext(temp);
  }   
};

int main(){}
