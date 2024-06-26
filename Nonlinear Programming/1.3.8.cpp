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
#include <chrono>
#include <vector>
#include <functional>
#include <limits>

using namespace std;

typedef std::function<double(double, double)> RealFunc1;
typedef std::function<double(std::function<double(double,double)>,double,double)> RealFunc1Derivative;

typedef std::function<double(double, double a[], double b[],int)> RealFunc2;
typedef std::function<double(std::function<double(double, double a[], double b[],int)>,double, double a[],double b[],int)> RealFunc2Derivative;

double Func1(double x, double gamma){
  return 0.5*std::pow(x,2)*(1+gamma*std::cos(x));
}

double Func2(double x, double y[5], double z[5], int m){
  double f;
  for(int i=1;i<=m;i++){
    f+=std::pow(std::abs(z[i]-std::tanh(x*y[i])),2);
  }
  return 0.5*f;
}

double computeDerivative1(RealFunc1 f, double x, double gamma){
  double h = sqrt(std::numeric_limits<double>::epsilon());
  return (f(x+h,gamma)-f(x,gamma))/h;  
}

double computeDerivative2(RealFunc2 f, double x, double y[5], double z[5], int m){
  double h = sqrt(std::numeric_limits<double>::epsilon());
  return (f(x+h,y,z,m)-f(x,y,z,m))/h;  
}

void SteepestDescentMethod(RealFunc1 f1, RealFunc2 f2, RealFunc1Derivative d1, RealFunc2Derivative d2, double x0, double y0, double y[5], double z[5], double alpha, double beta, double gamma, double precision){
  double xk = x0, xn = 0, xkm = x0;
 
  chrono::time_point<std::chrono::system_clock> start, end;
  chrono::duration<double> elapsed_seconds;
  
  start = chrono::system_clock::now();
  for(int i=0;;i++){
    xn=xk-alpha*d1(f1,xk,gamma)+beta*(xk-xkm);
    xkm=xk;
    xk=xn;
    if(abs(f1(xn,gamma)<precision)){
      end = chrono::system_clock::now();
      elapsed_seconds = end-start;
      std::cout << "Function #1 Local Minimum x: " << xk << std::endl;
      std::cout << "Total time was: " << elapsed_seconds.count() << std::endl;
      break;
    }
  }
  
  xk=x0; xkm = x0;  
  start = chrono::system_clock::now();
  for(int i=0;;i++){
    xn=xk-alpha*d2(f2,xk,y,z,5)+beta*(xk-xkm);
    xkm=xk;
    xk=xn;
    if(abs(f2(xn,y,z,5))<precision){
      end = chrono::system_clock::now();
      elapsed_seconds = end-start;
      std::cout << "Function #2 Local Minimum x: " << xk << std::endl;
      std::cout << "Total time was: " << elapsed_seconds.count() << std::endl;
      return;
    }
  }
 
}

int main(){
  RealFunc1 f1{Func1};
  RealFunc2 f2{Func2};
  RealFunc1Derivative d1{computeDerivative1};
  RealFunc2Derivative d2{computeDerivative2};
 
  double x0 = 1.2, y0 = 1.2, alpha=1.0, beta = 0, gamma = 1;
  double y[5] = {1.0,2.0,3.0,4.0,5.0};
  double z[5] = {1.0,1.0,1.0,1.0,1.0};
  double precision = 0.001;
 
  std::cout << "Initial x: " << x0 << std::endl;
  std::cout << "Initial y: " << y0 << std::endl;
  std::cout << "Initial alpha: " << alpha << std::endl; 
  std::cout << "Initial beta: " << beta << std::endl;
  std::cout << "Initial gamma: " << gamma << std::endl;
  
  std::cout << "Descent for f(x)=x^2(1+gamma*cos(x))/2" << std::endl;
  std::cout << "Descent for f(x)=sum_1_m*abs(z[i]-tanh(x*y[i]))^2/2" << std::endl;
  std::cout << std::endl;
  
  std::cout << "Case #1: Traditional Steepest Descent with beta = 0" << std::endl;
  SteepestDescentMethod(f1, f2, d1, d2, x0, y0, y, z, alpha, beta, gamma, precision);
 
  std::cout << std::endl; 
 
  std::cout << "Case #2: Heavy Step Method with beta = 1" << std::endl;
  SteepestDescentMethod(f1, f2, d1, d2, x0, y0, y, z, alpha, beta=1, gamma, precision);

  std::cout << std::endl << "A successful convergence supports part b, specifically, heavy step methods converge faster in time." << std::endl;
  return 0;
}
