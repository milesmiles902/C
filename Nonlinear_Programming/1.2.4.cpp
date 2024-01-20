//C++ Standard Library Extensions
//g++ 1.2.4 -std=c++11

/*
Question 1.2.4

Function: f(x,y) = x^2+y^2+b*x*y+x+2*y

Proving gradient descent of Lipschits condition: ||delf(x)-delf(y)|| <= L||x-y||

Rule:  Steepest Decent Method:                                                                                              D^k=1, k=0,1,...,                                                                                                    Normalized Negative Gradient: d^k=-delf(x*)/||delf(x^k)||                                                            Iteration: x^{k+1} = x^k-alpha*(D^k)*delf(x^k) where d^k=-D^k*del(f^k)       

       Prop 1.2.2: (Constant Stepsize)                                                                                                  e < alpha^k < (2-e)*alpha^k      
                   where alpha^k = |delf(x^k)'*d^k|/{L||d^k||} 
                   and e(0,1]
 
       Lipshitz Condition: ||delf(x)-delf(y)|| <= L||x-y|| 

*/

#include <iostream>
#include <cmath>
#include <functional>
#include <limits>


typedef std::function<double(double, double, double)> RealFunc;
typedef std::function<double(std::function<double(double,double,double)>,bool,double,double,double)> RealFuncDerivative;

double Func(double x, double y, double b){
  return pow(x,2)+pow(y,2)+b*x*y+x+2*y;
}

double computeDerivative(RealFunc f, bool xEval, double x, double y, double b){
  double h = sqrt(std::numeric_limits<double>::epsilon());
  if(xEval){
    return (f(x+h,y,b)-f(x,y,b))/h;  
  } else {
    return (f(x,y+h,b)-f(x,y,b))/h;
  }
}

void SteepestDecentMethod(RealFunc f, RealFuncDerivative d, double x0, double y0, double b, double alpha, double precision){
  double x = x0, y = y0;
  bool xEval = true;
  for(int i=0;;i++){
    x=x-alpha*f(x,y,b)/d(f,xEval,x,y,b);
    y=y-alpha*f(x,y,b)/d(f,!xEval,x,y,b);
    
    if(abs(f(x,y,b)<precision)){
      std::cout << "x: " << x << std::endl;
      std::cout << "y: " << y << std::endl;
      return;
    }
  }
}

int main(){
  RealFunc f{Func};
  RealFuncDerivative d{computeDerivative};
  
  SteepestDecentMethod(f, d, 2.0, 0.0, 1.0, 1.0, 10e-4);
  
  //To do: Lipschitz condition using prior functions.
  return 0;
}
