#include <iostream>
#include <list>
using namespace std;

struct Node {
  int data;
  struct Node* next;
  Node(int data){
    this->data = data;
    next = NULL;
  }
};

struct LinkedList{
  Node* head;
  LinkedList(){
    head = NULL;
  }
  Node *reverse(Node* head){
    if(head == NULL || head->next == NULL)
      return head;
    Node* rest = reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
  }
  void print(){
    struct Node* temp = head;
    while(temp!= NULL){
      cout << temp->data << " ";
      temp = temp->next;
    }
  }
  void push(int data){
    Node* temp = new Node(data);
    temp->next = head;
    head = temp;
  }
};

int main(){
  LinkedList ll; 
  ll.push(2);
  ll.push(22);
  ll.push(222);
  
  cout << "The linked list is: ";
  ll.print();
  cout << endl;
  ll.head = ll.reverse(ll.head);
  cout << "The reversed list is: ";
  ll.print();
   cout << endl;
}
