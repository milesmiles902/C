nputs and output the correct results*/
#include <iostream>
using namespace std;

class Fraction {
    public:
        Fraction(int top = 0, int bottom = 1){
            num = top;
            den = bottom;
        }
  friend ostream &operator << (ostream &stream, const Fraction &frac);

  private:
    int num, den;
};
    
ostream &operator << (ostream &stream, const Fraction &frac) {
  stream << frac.num << "/" << frac.den;
  return stream;
}
   
int main() {
  Fraction myfraction(3, 5);
  cout << myfraction;
  return 0;
}                                     
