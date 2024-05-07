/*Question 3.2.1 (Computational Problem)

minimize: f(x)=(1/2)*[x1^2 + x2^2 + (1/10)*x3^2] + 0.55*x3

subject to: x1 + x2 + x3 = 1, 0<x1, 0<x2, 0<x3

Show the global minimum [x*=(0.5,0.5,0)] by a conditional gradient and line minimization stepsize rule:

*/

#include <functional>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <iomanip>

using namespace std;

//Define complex variables
typedef std::function<double(double,double,double,double)> RealFunc;
typedef std::function<double(std::function<double(double,double,double,double)>,double,double,double,int)> RealFuncDerivative;

//The function: f(x)=(1/2)*[x1^2 + x2^2 + (1/10)*x3^2] + 0.55*x3
double Func(double x1, double x2, double x3, double lambda){
  double val = (x1*x1 + x2*x2 + x3*x3/10)/2 +0.55*x3 + lambda*(1-x1-x2-x3);
  return val;
}


//A function for computing a derivative
double computeDerivative(RealFunc f, double x1, double x2, double x3, int val){
  double h = sqrt(std::numeric_limits<double>::epsilon());
  double lambda=0.541667,fx = 0;
  switch(val) {
    case 1:
      fx = (f(x1+h,x2,x3,lambda)-f(x1,x2,x3,lambda))/h;
      return fx;
    case 2:
      fx = (f(x1,x2+h,x3,lambda)-f(x1,x2,x3,lambda))/h;
      return fx;
    case 3:
      fx = (f(x1,x2,x3+h,lambda)-f(x1,x2,x3,lambda))/h;
      return fx;
    default:
      std::cout << "A wrong val in derivative." << std::endl;
      break;
  }
  return 0;
}

//A line minimization: https://en.wikipedia.org/wiki/Line_search
double lineMin(RealFunc f,double d, double x1, double x2, double x3, int term){
  double lambda=0.541667,x=0,h=0,alpha=0.01,idx=1,min=0;
  switch(term) {
    case 1:
      min=f(x1+alpha*d,x2,x3,lambda);
      for(int k=2;k<=100;k++){
        alpha+=0.01;
        h=f(x1+alpha*d,x2,x3,lambda);
        if(h<min){
          min=h;
          idx=k;
        }
      }
      return idx/100;
    case 2:
     min=f(x1,x2+alpha*d,x3,lambda); 
     for(int k=2;k<=100;k++){
        alpha+=0.01;
        h=f(x1,x2+alpha*d,x3,lambda);
        if(h<min){
          min=h;
          idx=k;
        }
      }
      return idx/100;
    case 3:
      min=f(x1,x2,x3+alpha*d,lambda);
      for(int k=2;k<=100;k++){
        alpha+=0.01;
        h=f(x1,x2,x3+alpha*d,lambda);
        if(h<min){
          min=h;
          idx=k;
        }
      }
      return idx/100;
    default:
      std::cout << "A wrong val in lineMin" << std::endl;
      break; 
  }  
  return min;
}

//A three-variable Lagrange equation solved by conditional gradient descent: https://en.wikipedia.org/wiki/Gradient_descent
double evaluate(RealFunc f, RealFuncDerivative d, double x1, double x2, double x3,int term, double precision){
  double lambda=0.541167,dx=0,x=0,alpha=0;
  switch(term) {
    case 1:
      x=x1;
      for(int j=0;;j++){
        dx=f(x,x2,x3,lambda)/d(f,x,x2,x3,term);
        alpha=lineMin(f,dx,x,x2,x3,term);
        x=x-alpha*dx;
        if(x<0){x=0;}
        if(abs(d(f,x,x2,x3,term))<precision){
          std::cout <<"Function Minimum x: " << setprecision(2) << x << std::endl;
          std::cout <<"Error: " << abs(0.5-x)*100 << "%" << std::endl;
          return x;
        }
      }
      break;
    case 2:
      x=x2;
      for(int j=0;;j++){
        dx=f(x1,x,x3,lambda)/d(f,x1,x,x3,term);
        alpha=lineMin(f,dx,x1,x,x3,term);
        x=x-alpha*dx;
        if(x<0){x=0;}
        if(abs(d(f,x1,x,x3,term))<precision){
          std::cout <<"Function Minimum x: " << setprecision(2) << x << std::endl;
          std::cout <<"Error: " << abs(0.5-x)*100 << "%" << std::endl;
          return x;
        }
      }
      break; 
    case 3:  
      x=x3;
      for(int j=0;;j++){
        dx=f(x1,x2,x,lambda)/d(f,x1,x2,x,term);
        alpha=lineMin(f,dx,x1,x2,x,term);
        x=x-alpha*dx;
        if(x<0){x=0;}
        if(abs(d(f,x1,x2,x,term))<precision){
          std::cout <<"Function Minimum x: " << setprecision(2) << x << std::endl;
          std::cout <<"Error: " << setprecision(2) << abs(x)*100 << "%" << std::endl;
          return x;
        }
      }
      break;
    default:
      std::cout <<"Error in terminology." << std::endl;
      break;
  }
  return 0;
}

//The main with initial conditions
int main(){
  RealFunc f{Func};
  RealFuncDerivative d{computeDerivative};
  
  double x1=0.5,x2=0.3,x3=0.2,precision = 10e-3;

  std::cout <<"Function f(x1,x2,x3) = (1/2)*( x1*x2 + x2*x2 + x3*x3/10 ) + 0.55*x3" << std::endl;
  std::cout <<"Constraint: x1+x2+x3=1" << std::endl;
  std::cout << std::endl;

  std::cout <<"Initial x1: " << x1 << std::endl;
  std::cout <<"Initial x2: " << x2 << std::endl;
  std::cout <<"Initial x3: " << x3 << std::endl;
  std::cout <<"Initial Precision: " << precision << std::endl;
  std::cout << std::endl;

  x1 = evaluate(f,d,x1,x2,x3,1,precision);
  x2 = evaluate(f,d,x1,x2,x3,2,precision);
  x3 = evaluate(f,d,x1,x2,x3,3,precision);

  std::cout << std::endl; 
  std::cout << "Ths implementation contains a pre-defined Langrangian multipler (lambda = 0.541167)."<< std::endl; 
  return 0;
}

 



