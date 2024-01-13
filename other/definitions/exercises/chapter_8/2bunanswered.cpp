#include <iostream>
#include <cstdlib>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class BinaryTree {

    private:
        string key;
        BinaryTree *leftChild;
        BinaryTree *rightChild;
    public:
        BinaryTree(string rootObj){
            this->key = rootObj;
            this->leftChild = NULL;
            this->rightChild = NULL;
        }

        void insertLeft(string newNode){
            if (this->leftChild == NULL){
            this->leftChild = new BinaryTree(newNode);
            }
            else {
            BinaryTree *t = new BinaryTree(newNode);
            t->leftChild = this->leftChild;
            this->leftChild = t;
            }
        }

        void insertRight(string newNode){
            if (this->rightChild == NULL){
            this->rightChild = new BinaryTree(newNode);
            }
            else {
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

        void setRootVal(string obj){
            this->key = obj;
        }

        string getRootVal(){ 
            cout << this->key;
            return this->key;
        }
};

string removeSpaces(string a){
  string b;
  for(int i=0;i<a.length();i++){
    if(i==(a.length()-1)){
      b+=a.substr(i,1);
    } else {
      b+=a.substr(i,1)+"\0";
    }
  }
  return b;
}

int doMath(char op, int op1, int op2) {
    //Does math based on what op is passed as.
    if (op == '*') {
        return (op1 * op2);
    } else if (op == '/') {
        return (op1 / op2);
    } else if (op == '+') {
        return (op1 + op2);
    } else if (op == '-'){
        return (op1 - op2);
    } else if (op == '^'){
        return (op1^op2);
    } else if (op == '!'){
        return (op1);
    } else if (op == '|'){
        return (op1|op2);
    }
}

int postfixEval(string postfixExpr) {
    stack<int> operandStack;
    string nums = "0123456789";

    for (char i : postfixExpr) {
        if ((nums.find(i) <= nums.length())) { // Check if the current char is a number
            operandStack.push(int(i) - 48); // conversion from char to ascii
            // then subtract 48 to get the int value
            } else if (i != ' ') {
                          int operand2 = operandStack.top();
                          operandStack.pop();
                          int operand1 = operandStack.top();
                          operandStack.pop();
                          int result = doMath(i, operand1, operand2);
                          operandStack.push(result);
                  }
    }
    return operandStack.top();
}

BinaryTree *buildParseTree(string fpexp){
    string buf;
    vector<string> fplist;
    stringstream ss(fpexp);

    while (ss >> buf){
        fplist.push_back(buf);
    }
    stack<BinaryTree*> pStack;
    BinaryTree *eTree = new BinaryTree("");
    pStack.push(eTree);
    BinaryTree *currentTree = eTree;

    string arr[] = {"+", "-", "*", "/", "^", "|", "!"};
    vector<string> vect(arr,arr+(sizeof(arr)/ sizeof(arr[0])));

    string arr2[] = {"+", "-", "*", "/", "^", "|", "!", ")"};
    vector<string> vect2(arr2,arr2+(sizeof(arr2)/ sizeof(arr2[0])));

    for (unsigned int i = 0; i<fplist.size(); i++){
        if (fplist[i] == "("){
            currentTree->insertLeft("");
            pStack.push(currentTree);
            currentTree = currentTree->getLeftChild();
        }

        else if (find(vect.begin(), vect.end(), fplist[i]) != vect.end()){
            cout << "A" << fplist[i] << endl;
            currentTree->setRootVal(fplist[i]);
            currentTree->insertRight("");
            pStack.push(currentTree);
            currentTree = currentTree->getRightChild(); 
        }

        else if (fplist[i] == ")"){
            currentTree = pStack.top();
            pStack.pop();
        }

        else if (find(vect2.begin(), vect2.end(), fplist[i]) == vect2.end()) {
            //cout << "B" << fplist[i] << endl;
            try {
                currentTree->setRootVal(fplist[i]);
                BinaryTree *parent = pStack.top();
                pStack.pop();
                currentTree = parent;
            }

            catch (string ValueError ){
                cerr <<"token " << fplist[i] << " is not a valid integer"<<endl;
            }
        }
    }
    return eTree;
};

void postorder(BinaryTree *tree){
    if (tree != NULL){
        postorder(tree->getLeftChild());
        postorder(tree->getRightChild());
    }
};

int main() {

    BinaryTree *pt = buildParseTree("( ( 2 ^ 10 + 5 ) * 3 )");

    postorder(pt);

    return 0;
}

