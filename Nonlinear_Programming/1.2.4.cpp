//C++ Standard Library Extensions
//g++ 1.2.4 -std=c++11

/*
Question 1.2.4

Function: f(x,y) = x^2+y^2+b*x*y+x+2*y

Proving gradient descent of Lipschitz condition: ||delf(x)-delf(y)|| <= L||x-y||

Rule:  Steepest Descent Method:                                                                                              D^k=1, k=0,1,...,                                                                                                    Normalized Negative Gradient: d^k=-delf(x*)/||delf(x^k)||                                                            Iteration: x^{k+1} = x^k-alpha*(D^k)*delf(x^k) where d^k=-D^k*del(f^k)       

       Prop 1.2.2: (Constant Stepsize)                                                                                                  e < alpha^k < (2-e)*alpha^k      
                   where alpha^k = |delf(x^k)'*d^k|/{L||d^k||} 
                   and e(0,1]
 
       Lipshitz Condition: ||delf(x)-delf(y)|| <= L||x-y|| 

*/

#include <iostream>
#include <cmath>
#include <functional>
#include <limits>
#include <vector>

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
    std::cout << "Iteration: " << i << std::endl;
    if(abs(f(x,y,b)<precision)){
      std::cout << "Function Local Minimum x: " << x << std::endl;
      std::cout << "Function Local Minimum y: " << y << std::endl;
      return;
    }
  }
}

int main(){
  RealFunc f{Func};
  RealFuncDerivative d{computeDerivative};
  
  double x0=5.0, y0=0.0, alpha=1.0, L=1;
  
  std::cout << "Initial x: " << x0 << std::endl;
  std::cout << "Initial y: " << y0 << std::endl;
  std::cout << "Initial alpha: " << alpha << std::endl; 
    
  SteepestDecentMethod(f, d, x0, y0, 1.0, alpha, 10e-3);
  
  std::cout << "Proving Lipschitz condition: " << std::endl;
  std::cout << "||delf(x)-delf(y)|| = " << d(f,true,x0,y0,1.0)-d(f,false,x0,y0,1.0) << " <= L||x-y|| = " << x0-y0 <<  std::endl;
  
  return 0;
}
