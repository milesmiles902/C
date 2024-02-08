/*
Question 1.3.8

Function: x^{k+1} = x^k - alpha*delf(x) + beta*(x^k-x^{k-1})
 
a) If f is the quadratic function f(x) = (1/2)*x'Q*x +c'*x

     1) x^{k+1} = x^k - alpha*delf(x) + beta*(x^k-x^{k-1})
 
              = (1+beta)*x^k-alpha*Q-beta*x^{k-1}

     2)    x^k  = x^k

     3)  x^{k+1} = A*x^k
   
     4)  |x^{k+1}|   | (1+beta)-alpha*Q     -beta | |   x^k  | 
         |       | = |                            |*|        |
         |  x^k  |   |        1                0  | | x^{k-1}|
    
     5)  A = | (1+beta)-alpha*Q     -beta |
             |                            |
             |        1                0  |

     6)  Eigenvalues:
 
         A|u| = lambda|u|
          |v|         |v|
         
         lambda1 = 0
         lambda2 = Difficult because lambda2+beta/lambda2 = 1 + beta - alpha*Q isn't an easy quadratic

     7) The maximal eigenvalue relationship is 0 < lambda2 < 2*(1+beta)/M

     8) A secondary solution for lambda2 solved the quadratic from 6) 
  
        lambda2 = [1+beta-alpha*Q+-sqrt((1+beta-alpha*lambda)^2-4*beta)]/2

     9) Correspondence between lambda1 and lambda2 begins with the step function:
  
         (1/2)(1+beta-alpha*lambda1)^2-beta = (1/2)(1+beta-alpha*lambda2)^2-beta
 
         alpha = 2(1+beta)/(lambda1+lambda2)

     10) A substituion into the maximum eigenvalue equation
  
         beta = (1/2)(1+beta-alpha*M)^2-beta
 
              = (1/2)((1+beta)(M-m)/(m+M))^2-beta

              = (sqrt(M)-sqrt(m))/(sqrt(M)+sqrt(m)))^2

b) The book describes steepest descent convergence as

      ||x^{k+1}||/||x^k|| <= (M-m)/(M+m) <=(sqrt(M)-sqrt(m))/(sqrt(M)+sqrt(m))

   A comparison between steepest descent and the new method show a conditional number with faster convergence rate

c) Function #1: f(x)=0.5*x^2(1+gamma*cos(x)) 

   Function #2: f(x)=0.5*sum_1_m [|z_i-tanh(xy)]^2
*/

#include <iostream>
#include <cmath>
#include <chronos>

using namespace std;

std::function<double(double, double)> RealFunc1;
typedef std::function<double(std::function<double(double,double)>,bool,double,double)> RealFunc1Derivative;

std::function<double(double, double, double)> RealFunc2;
typedef std::function<double(std::function<double(double,double,double)>,bool,double,double,double)> RealFunc2Derivative;

double Func1(double x, double gamma){
  return 0.5*pow(x,2)*(1+gamma*cos(x));
}

double Func2(double x, double y, double z){
  return 0.5*pow(abs(z-tanh(x*y)),2)
}

double computeDerivative1(RealFunc f, bool xEval, double x, double gamma){
  double h = sqrt(std::numeric_limits<double>::epsilon());
  return (f(x+h,gamma)-f(x,gamma))/h;  
}

double computeDerivative2(RealFunc f, bool xEval, double x, double y, double z){
  double h = sqrt(std::numeric_limits<double>::epsilon());
  return (f(x+h,y,z)-f(x,y,z))/h;  
}

void SteepestDecentMethod(RealFunc f, RealFuncDerivative d, double x0, double y0, double gamma, double alpha, double precision){
  double x = x0, y = y0;
  bool xEval = true;
  for(int i=0;;i++){
    x=x-alpha*f(x,y,b)/d(f,xEval,x,y,b);
    std::cout << "Iteration: " << i << std::endl;
    if(abs(f(x,y,b)<precision)){
      std::cout << "Function Local Minimum x: " << x << std::endl;
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
