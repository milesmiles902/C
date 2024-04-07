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

using namespace std;

typedef std::function<double(double,double,double)> RealFunc;
typedef std::function<double(std::function<double(double,double,double)>,double,double,double,int)> RealFuncDerivative;

double Func(double x1, double x2, double x3){
//  std::cout << "Func x1 " << x1 << " " << x2 << " " << x3 << std::endl;
  double val = (x1*x1 + x2*x2 + x3*x3/10)/2+0.55*x3;
  //std::cout << "Func val " << val << std::endl;
  return val;
}

double computeDerivative(RealFunc f, double x1, double x2, double x3, int val){
  double h = sqrt(std::numeric_limits<double>::epsilon());
  double fx = 0;
  switch(val) {
    case 1:
      fx = (f(x1+h,x2,x3)-f(x1,x2,x3))/h;
 //     std::cout << "fx " << fx << std::endl;
      return fx;
    case 2:
      fx = (f(x1,x2+h,x3)-f(x1,x2,x3))/h;
      return fx;
    case 3:
      fx = (f(x1,x2,x3+h)-f(x1,x2,x3))/h;
      return fx;
    default:
      std::cout << "A wrong val in derivative." << std::endl;
      break;
  }
  return 0;
}

double lineMin(RealFunc f,double d, double x1, double x2, double x3, int term){
  double h=0,alpha=0.1,idx=1,min=0;
  switch(term) {
    case 1:
      min=f(x1+alpha*d,x2,x3);
      //std::cout << "min " << min << std::endl;
      for(int k=2;k<=10;k++){
        h=f(x1+alpha*d,x2,x3);
        //std::cout << "h " << h << std::endl;
        if(h>min){
          min=h;
          idx=k;
        }
        alpha+=0.1;
      }
      return idx/10;
    case 2:
     min=f(x1,x2+alpha*d,x3); 
     //std::cout << "min " << min << std::endl;
     for(int k=2;k<=10;k++){
        h=f(x1,x2+alpha*d,x3);
        if(h>min){
          min=h;
          idx=k;
        }
        alpha+=0.1;
      }
      return idx/10;
    case 3:
      min=f(x1,x2,x3+alpha*d);
      for(int k=2;k<=10;k++){
        h=f(x1,x2,x3+alpha*d);
        if(h>min){
          min=h;
          idx=k;
        }
        alpha+=0.1;
      }
      return idx/10;
    default:
      std::cout << "A wrong val in lineMin" << std::endl;
      break; 
  }  
  return min;
}

double evaluate(RealFunc f, RealFuncDerivative d, double x1, double x2, double x3,int term, double precision){
  double dx=0,x=0,alpha=0;
  switch(term) {
    case 1:
      x=x1;
      for(int j=0;;j++){
//        std::cout << "1dxbefore " <<dx <<std::endl;
        dx=f(x,x2,x3)/d(f,x,x2,x3,term);
  //      std::cout << "2dxafter " << dx << std::endl;
        alpha=lineMin(f,dx,x,x2,x3,term);
    //    std::cout << "3ff " << f(x,x2,x3) << std::endl;
       // std::cout << "4dx " << dx << std::endl;
      //  std::cout << "5alpha " << alpha << std::endl;
      //  std::cout << "6xbefore " << x << std::endl;
        x=x-alpha*dx;
      //  std::cout << "7xafter" << x << std::endl;
        if(abs(d(f,x,x2,x3,term))<precision){
          std::cout <<"Function Local Minimum x: " << x << std::endl;
          return x;
        }
      }
      break;
    case 2:
      x=x2;
      for(int j=0;;j++){
      //  std::cout << "1dxbefore " <<dx <<std::endl;
        dx=f(x1,x,x3)/d(f,x1,x,x3,term);
        //std::cout << "2dxafter " << dx << std::endl;
        alpha=lineMin(f,dx,x1,x,x3,term);
        //std::cout << "3ff " << f(x,x2,x3) << std::endl;
        //std::cout << "4dx " << dx << std::endl;
        //std::cout << "5alpha " << alpha << std::endl;
        //std::cout << "6xbefore " << x << std::endl;  
        x=x-alpha*dx;
        //std::cout << "x " << x << std::endl;
        if(abs(d(f,x1,x,x3,term))<precision){
          std::cout <<"Function Local Minimum x: " << x << std::endl;
          return x;
        }
      }
      break; 
    case 3:  
      x=x3;
      for(int j=0;j<100000;j++){
        std::cout << "1dxbefore " <<dx <<std::endl;

        dx=f(x1,x2,x)/d(f,x1,x2,x,term);
        std::cout << "2dxafter " << dx << std::endl;

        alpha=lineMin(f,dx,x1,x2,x,term);
        std::cout << "3ff " << f(x,x2,x3) << std::endl;
        std::cout << "4dx " << dx << std::endl;
        std::cout << "5alpha " << alpha << std::endl;
        std::cout << "6xbefore " << x << std::endl; 
        x=x-alpha*dx;
         std::cout << "6xbefore " << x << std::endl;
        std::cout << "abs(d(f,x1,x2,x,term)" << abs(d(f,x1,x2,x,term)) << std::endl;
        if(abs(d(f,x1,x2,x,term))<precision){
          std::cout <<"Function Local Minimum x: " << x << std::endl;
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

int main(){
  RealFunc f{Func};
  RealFuncDerivative d{computeDerivative};
  
  double x1=10,x2=10,x3=10,precision = 10e-4;
 
  std::cout <<"Initial x1: " << x1 << std::endl;
  std::cout <<"Initial x2: " << x2 << std::endl;
  std::cout <<"Initial x3: " << x3 << std::endl;
  std::cout <<"Initial Precision: " << precision << std::endl;

  x1 = evaluate(f,d,x1,x2,x3,1,precision);
  x2 = evaluate(f,d,x1,x2,x3,2,precision);
  x3 = evaluate(f,d,x1,x2,x3,3,precision);
  return 0;
}



