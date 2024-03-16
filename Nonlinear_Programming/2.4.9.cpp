/*
Question 2.4.9:

Function: g_1(x) = x*x - 2 
          g_2(x) = x*x

a) Verify each Extended Kalman Filter cycle by a sequence:

       H = lambda*H_{i-1} + delg*g
    
         = lambda*H_{i-1} + (2x)*(2x)

       x^{k+1} = x^k - (2x)(x*x-2)/H

b)*/

//g++ 2.4.9.cpp -std=c++17
#include <functional>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

typedef std::function<double(double,double)> RealFunc;
typedef std::function<double(std::function<double(double,double)>,double,double,bool)> RealFuncDerivative;

double Func(double x, double y){
  return (x+y)/2;
}

double computeDerivative(RealFunc f, double x, double y, bool xeval){
  double h = sqrt(std::numeric_limits<double>::epsilon());
  if(xeval){
    return (f(x+h,y)-f(x,y))/h;
  } else{
    return (f(x,y+h)-f(x,y))/h;
  } 
}

void ExtendedKalmanFilter(RealFunc f, RealFuncDerivative d, double x0, double y0, double H0, double lambda, double precision){
  double x = x0, y=y0, Hx=H0, Hy=H0;
  for(int i=0;;i++){
    Hy=lambda*Hx+d(f,x,y,true)*f(x,y);
    y=x-d(f,x,y,true)*f(x,y)/Hy;
    Hx=lambda*Hy+d(f,x,y,false)*f(x,y);
    x=y-d(f,x,y,false)*f(x,y)/Hx;
    if(abs(f(x,y)<precision)){
      std::cout <<"Function Local Minimum x: " << x << std::endl;
      std::cout <<"Function Local Minimum y: " << y << std::endl;
      return;
    }
  }  
}

int main(){
  RealFunc f{Func};
  RealFuncDerivative d{computeDerivative};
  
  double x=1.0, y=1.0, H=1.0, lambda=0.1, precision = 10e-3;
 
  std::cout <<"Initial x: " << x << std::endl;
  std::cout <<"Initial y: " << y << std::endl;
  std::cout <<"Initial H: " << H << std::endl;
  std::cout <<"Initial lambda: " << lambda << std::endl;
  std::cout <<"Initial Precision: " << precision << std::endl;

  for(int i=0;i<9;i++){
    ExtendedKalmanFilter(f,d,x,y,H,lambda,precision);
    lambda+=0.1;
    std::cout << " " << std::endl;
    std::cout << "A new lambda value at: " << lambda << std::endl;
  }

  std::cout << "The true function has no local minimum" << std::endl;

  std::cout << "Extended Kalman Filters lower increments before approaching infinity or when the earth falls off or where the sidewalk ends."; 
  return 0;
}

 
/*
Rules: Extended Kalman Filter:
         x^{k+1} = x^k - sum_1_m[delg*g]/H
         H = lambda*H_{i-1}+delg*g+Noise  */
