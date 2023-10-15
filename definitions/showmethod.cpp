#include <iostream>
using namespace std;

class Fraction {
  public:
    Fraction(int top=0,int bottom=1){
      num=top; 
      den=bottom;
    }
    void show(){ 
      cout << num << "/" << den << endl;
    }
  private:
    int num,den;
};

int main(){
  Fraction fraca(3,5);
  Fraction fracb(3);
  Fraction fracc;
  fraca.show();
  fracb.show();
  fracc.show();
  return 0;
}
