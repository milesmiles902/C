#include <iostream>
#include <string>
using namespace std;

class LogicGate{
  public:
    LogicGate(string n){
      label=n;
    }
    string getLabel(){
      return label;
    }
    bool getOutput(){
      output = performGateLogic(); 
      return output;
    }
    virtual bool performGateLogic(){
      cout << "Error! performGateLogic Base" << endl;
      return false;
    }
    virtual void setNextPin(bool source){
      cout << "Error! setNextPin Base" << endl;
    }
  private:
    string label;
    bool output;
};

class BinaryGate : public LogicGate{
  public: 
    BinaryGate(string n) : LogicGate(n){
      pinATaken = false;
      pinBTaken = false;
      pinCTaken = false;
    }
    bool getPinA(){
      if(pinATaken == false){
        cout << "Enter Pin A input for gate " << getLabel() << ": ";
        cin >> pinA;
        pinATaken = true;
      }
      return pinA;
    }
    bool getPinB(){
      if(pinBTaken == false){
          cout << "Enter Pin B input for gate " << getLabel() << ": ";
          cin >> pinB;
          pinBTaken = true;
      }
      return pinB;
    }
    bool getPinC(){
      if(pinCTaken == false){
          cout << "Enter Pin C input for gate " << getLabel() << ": ";
          cin >> pinC;
          pinCTaken = true;
      }
      return pinC;
    }
    virtual void setNextPin(bool source){
      if(pinATaken == false){
        pinA = source;
        this->pinATaken = true;
      }
      else if(pinBTaken == false){
        pinB = source;
        this->pinBTaken = true;
      }else{
        pinC = source;
        this->pinCTaken = true;
      }
    }
  private:
    bool pinA,pinATaken,pinB,pinBTaken,pinC,pinCTaken;
};

class UnaryGate : public LogicGate{
  public:
    UnaryGate(string n) : LogicGate(n){
      pinTaken = false;
    }
    bool getPin(){
      if(pinTaken == false){
        cout << "Enter Pin input for gate " << getLabel() << ": ";
        cin >> pin;
        pinTaken = true;
      }
      return pin;
    }
    virtual void setNextPin(bool source){
      if(pinTaken == false){
        pin = source;
        pinTaken = true;
      }
      else {
        return;
      }
    }
  private:
    bool pin,pinTaken;
};

class AndGate : public BinaryGate {
  public:
    AndGate(string n) : BinaryGate(n) {};
    virtual bool performGateLogic(){
      bool a = getPinA();
      bool b = getPinB();
      if(a == 1 && b == 1){
        return true;
      }
      else {
        return false;
      }
    }
};

class OrGate : public BinaryGate {
  public:
    OrGate(string n) : BinaryGate(n) {};
    virtual bool performGateLogic() {
      bool a = getPinA();
      bool b = getPinB();
      if(a==1 || b==1){
        return true;
      }
      else {
        return false;
      }
    }
};

class NOrGate : public BinaryGate {
  public:
    NOrGate(string n) : BinaryGate(n) {};
    virtual bool performGateLogic(){
      bool a = getPinA();
      bool b = getPinB();
      if(a==0||b==0){
        return true;
      } else {
        return false;
      }
    }
};

class NotGate : public UnaryGate{
  public:
    NotGate(string n) : UnaryGate(n) {};
    virtual bool performGateLogic(){
      if(getPin()){
        return false;
      }
      else {
        return true;
      }
    }
};

class NAndGate : public BinaryGate{
  public:
    NAndGate(string n) : BinaryGate(n) {};
    virtual bool performGateLogic(){
      bool a = getPinA();
      bool b = getPinB();
      if (a==1||b==1){
        return false;
      } else {
        return true;
      }
    }
};

class XOrGate : public BinaryGate{
  public:
    XOrGate(string n) : BinaryGate(n) {};
    virtual bool performGateLogic(){
      bool a = getPinA();
      bool b = getPinB(); 
      if(a==b){
        return true;
      } else {
        return false;
      }
    }
};

class HalfAdder : public BinaryGate{
  public:
    HalfAdder(string n) : BinaryGate(n) {};
    virtual bool performGateLogic(){
      bool a = getPinA();
      bool b = getPinB();
      if(a==0||b==0){
        sum=1;
        carry=0;
      }   
      else if(a==0&&b==0){
        sum=0;
        carry=0;
      } else {
        sum=0;
        carry=1;
      }
    }
    bool getSum(){
      return sum;
    }
    bool getCarry(){
      return carry;
    }
  private:
    bool sum,carry;
};

class FullAdder : public BinaryGate{
  public:
    FullAdder(string n) : BinaryGate(n) {};
    virtual bool performGateLogic(){
      bool a = getPinA();
      bool b = getPinB();
      bool c = getPinC();
      if(a&&b){
        carry=1;
        if(c){
          sum=1;
        } else {
          sum=0;
        }
      } else if(a){
        if(c){
          sum=0;
          carry=1;
        } else {
          sum=1;
          carry=0;
        }
      } else if(b){
          if(c){
            sum=0;
            carry=1;
          } else{
            sum=1;
            carry=0;
          }
      } else { 
          carry=0;
          if(c){
            sum=1;
          } else {
            sum=0;
          }
        }
      }
  private:
    bool sum,carry;
};
class ConnectorFprward{
  public:
    Connector(LogicGate *fgate, LogicGate *tgate){
      fromgate = fgate;
      togate = tgate;
      tgate->setNextPin(fromgate->getOutput());
    }
    LogicGate *getFrom(){
      return fromgate;
    }
    LogicGate *getTo(){
      return togate;
    }
  private:
    LogicGate *fromgate, *togate;
};

class ConnectorBackward{
  public:
    ConnectorBackward(LogicGate *fgate, LogicGate *tgate){
      fromgate = tgate;
      togate = fgate;
      fgate->setNextPin(togate->getOutput()); 
    }
    LogicGate *getFrom(){
      return fromgate;
    }
    LogicGate *getTo(){
      return togate;
    }
  private:
    LogicGate *fromgate, *togate;
}
int main(){}
