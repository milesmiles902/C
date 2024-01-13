#include <iostream>
#include <cstdlib>
using namespace std;

class BinaryTree{
  private:
    char key;
    BinaryTree *leftChild;
    BinaryTree *rightChild;

  public:
    BinaryTree(char rootObj){
      this->key = rootObj;
      this->leftChild = NULL;
      this->rightChild = NULL;
    }
  
  void insertLeft(char newNode){
    if(this->leftChild == NULL){
      this->leftChild = new BinaryTree(newNode);
    } else {
      BinaryTree *t = new BinaryTree(newNode);
      t->leftChild = this->leftChild;
      this->leftChild = t;
    }
  }
  
  void insertRight(char newNode){
    if(this->leftChild == NULL){
      this->leftChild = new BinaryTree(newNode);
    } else {
      BinaryTree *t = new BinaryTree(newNode);
      t->rightChild = this->rightChild;
      this->rightChild = t;
    }
  }
  
  BinaryTree *getRightChild(){
    return this->rightChild;
  } 
  
  BinaryTree *getLeftChild(){
    return this->leftChild;
  }
  
  void setRootVal(char obj){
    this->key=obj;
  }
 
  char getRootVal(){
    return this->key;
  }
};

int main(){
  BinaryTree *r = new BinaryTree('a');
  cout << r->getRootVal() << endl;
  cout << r->getLeftChild() << endl;
  r->insertLeft('b');
  cout << r->getLeftChild() << endl;
  cout << r->getLeftChild()->getRootVal() << endl;
  r->insertRight('c');
  cout << r->getRightChild() << endl;
  cout << r->getRightChild()->getRootVal() << endl;
  r->getRightChild()->setRootVal('d');
  cout << r->getRightChild()->getRootVal() << endl;
  
  return 0;  
}
