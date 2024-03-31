/*Question 3.1.12*/

#include <functional>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

/*a) The algorithm finds the projection vector (z) on a simplex (x = {x|sum_i[x_i]=const}). A purpose is a forecast between cycles in a business with adjusted coeffients for operating sales or expense*/

double Projection(vector<double> y){
  int i,j,idx,size=y.size();
  double x = 0, max = 0, lambda = 0;

  //Largest projection is from the largest value
  sort(y.begin(),y.end());
  //Vector needs reversal because sorts from small to large
  reverse(y.begin(),y.end());
  //Largest average projection; The steps are from Lagrange's derivative;
  for(i=0;i<size;i++){
    for(j=0;j<i;j++){
      lambda+=y[j]/i;
    }
    lambda=y[i]-(1-lambda)/i;
    if(lambda>max){
      max = lambda;
      idx = i;
    }
  }
  //Largest projection up till the largest average projection, the Lagrange multiplier.
  for(i=0;i<idx;i++){
    lambda -= y[i];
  }
  lambda = (1-lambda)/max;
  
  for(i=0;i<idx;i++){
    max = y[i]+lambda;
    if(max>x){
      x=max;
    }
  }
  return x;
}

/*b) The books wants a cost function. Example, business costs per cycle with an adjusted coefficient for operating sales or expense. A threshold value. Congressional lawyers sit with propositions and thresholds. What finds a propositions or thresholds importance?*/

/*Cost Function: f(x) = sum_1_n[alpha_i*x_i+(1/2)*beta_i*x_i^2)] */

void Calculation(vector<int> alpha, vector<int> beta, std::vector<double> x, double precision){
  int i=0,n=x.size();
  for(i=0;i<x.size();i++){
    x[i] = alpha[i]*x[i]+(1/2)*beta[i]*x[i]*x[i];
  }
  std::cout <<"The minimum is: " << Projection(x) << std::endl;
  return;
}

int main(){
  int n = 5;
  std::vector<int> alpha = {1,2,3,4,5};
  std::vector<int> beta = {2,4,6,8,10};
  std::vector<double> x = {11,22,33,55,44};
 
  double precision = 10e-3;
 
  std::cout <<"Initial alpha: "<< std::endl;
  for(int i=0;i<n;i++){
    std::cout << alpha[i] << " ";
  } std::cout << std::endl;

  std::cout <<"Initial beta: "<< std::endl;
  for(int i=0;i<n;i++){
    std::cout << beta[i] << " ";
  } std::cout << std::endl;

  std::cout <<"Initial x: "<< std::endl;
  for(int i=0;i<n;i++){
    std::cout << x[i] << " ";
  } std::cout << std::endl;
 
  std::cout <<"Initial precision: " << precision << std::endl;
 
  std::cout <<"Case #1: Beta > 0 " << std::endl;
  Calculation(alpha,beta,x,precision);

  std::cout <<"Case #2: Beta = 0 " << std::endl;
  beta = {0,0,0,0,0};
  Calculation(alpha,beta,x,precision);

  std::cout <<"A finalizationist, tomorrow." << std::endl;
  return 0;
}








