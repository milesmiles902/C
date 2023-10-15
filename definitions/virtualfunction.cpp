#include <iostream>
using namespace std;

class Base {
  public:
    virtual void printType(){
      subfunction();
      cout << "I'm inherited!" << endl << endl;
    }
    virtual void subfunction(){
      
    }
}

class SubFirst : public Base {
  virtual void subfunction(){
    cout << "I'm one type of sub-class!" << endl;
  }
}

class SubSecond : public Base {
  virtual void subfunction(){
    cout << "I'm another type of sub class!" << endl;
  }
}

int main(){
  SubFirst first;
  first.printType();
  
  SubSecond second;
  second.printType();
 
  return 0;
}
