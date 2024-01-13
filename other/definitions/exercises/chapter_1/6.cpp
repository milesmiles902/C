#include <iostream>
using namespace std;

int gcd(int m, int n){
  while (m%n !=0){
    int oldm = m;
    int oldn = n;
  
    m = oldn;
    n = oldm%oldn;
  }
  return n;
}

class Fraction {
  public:
    Fraction(int top, int bottom){
      if(isdigit(top)||isdigit(bottom){
        num = top/gcd(top,bottom);
        den = abs(bottom/gcd(top,bottom));
      } else { cout << "The entries are not integers!" << endl};
    }
    Fraction(int top){
      if(isdigit(top){
        num = top;
        den = 1;
      } else { cout << "The entries are not integers!" << endl};
    }
    Fraction(){
      num=1;
      den=1;
    }
   
    int getNum(){
      return num;
    }  
    
    int getDen(){
      return den;
    }

    Fraction operator +(Fraction otherFrac){
      int newnum = num*otherFrac.den + den*otherFrac.num;
      int newden = den*otherFrac.den;
      int common = gcd(newnum,newden);
      return Fraction(newnum,newden);
    }
    bool operator ==(Fraction &otherFrac){
      int firstnum = num*otherFrac.den;
      int secondnum = otherFrac.num*den;
      return firstnum==secondnum;
    }
    Fraction operator -(Fraction &otherFraction){
      int newnum = num*otherFrac.den - den*otherFrac.num;
      int newden = den*otherFrac.den;
      return Fraction(newnum,newden);
    }
    Fraction operator *(Fraction &otherFraction){
      int newnum = num*otherFrac.num;
      int newden = den*otherFraction.den;
      return Fraction(newnum,newden);
    }
    Fraction operator /(Fraction &otherFraction){
      int newnum = num*otherFrac.den;
      int newden = den*otherFrac.num;
      return Fraction(newnum,newden);
    }
    bool operator >(Fraction &otherFraction){
      return (otherFrac.num/otherFrac.den)>(num/den);
    }
    bool operator >=(Fraction &otherFraction){
      return (otherFrac.num/otherFrac.den)>=(num/den);
    }
    bool operator <(Fraction &otherFraction){
      return (otherFrac.num/otherFrac.den)<(num/den);
    }
    bool operator <=(Fraction &otherFraction){
      return (otherFrac.num/otherFrac.den)<=(num/den);
    }
     bool operator !=(Fraction &otherFraction){
      return (otherFrac.num/otherFrac.den)!=(num/den);
    }

  friend ostream& operator<<(ostream& stream, const Fraction& fraction);
  private:
    int num,den;
};

ostream& operator << (ostream& stream, const Fraction & fraction){
  stream << fraction.num << "/" << fraction.den;
  return stream;
};

int main(){
  Fraction x(1,2);
  Fraction y(2,4);
  cout << x << "+" << y << " = " << x+y << endl;
  if (x==y){
    cout << "x is equal to y" << endl;
  }
  else{
    cout << "x is not equal to y" << endl;
  }
  return 0;
}
