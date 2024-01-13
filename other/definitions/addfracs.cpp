#include <iostream>
using namespace std;

class Fraction {
  public: 
    Fraction(int top = 0,int bottom = 1){
      num=top;
      den=bottom;
    }
  friend ostream &operator << (ostream &stream, const Fraction &frac);
  friend Fraction operator +(const Fraction &frac1, const Fraction &frac2);
  private:
    int num, den;
};

ostream &operator << (ostream &stream, const Fraction &frac){
  stream << frac.num << "/" << frac.den;
  return stream;
};

Fraction operator + (const Fraction &frac1, const Fraction &frac2){
  int newnum = frac1.num * frac2.den + frac1.den * frac2.num;
  int newden = frac1.den * frac2.den;
  return Fraction(newnum,newden);
};

int main(){
  Fraction f1(1,4);
  Fraction f2(1,2);
  Fraction f3 = f1+f2;
  cout << f3 << " is " << f1 << " + " << f2 << endl;
  return 0;
}
