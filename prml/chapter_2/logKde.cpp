/*
 * @file .cpp
 * @brief Computer log probability density function of kernel density estimator.
 */

#include <cmath>
#include <iostream>
#include "nr3.h"

void logKde(MatDoub X, MatDoub Y, Doub SIGMA, int &z){
  int i,j;
  VecDoub Xdot(25), Ydot(25), XYdot(25);
  int logsumexp;
  for(i=0;i<X.nrows();i++){
    for(j=0;j<X.ncols();j++){
      Xdot[i*5+j]=X[i][j]*X[i][j];
      Ydot[i*5+j]=Y[i][j]*Y[i][j];
      XYdot[i*5+j]=X[i][j]*Y[j][i];
    }
  }
  for (i=0;i<X.nrows();i++){
    for(j=0;j<X.ncols();j++){
      logsumexp += exp((Xdot[i*5+j]+Ydot[i*5+j]-2*XYdot[i*5+j])/(-2*pow(SIGMA,2)));   
    }
  }
  logsumexp = log(logsumexp)-0.5*log(2*M_PI) -log(SIGMA*Y.ncols());
  z=logsumexp;
}

int main(){
  MatDoub X(5,5), Y(5,5);
  int z(25);
  Doub SIGMA;
  for (int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      X[i][j] = rand() % 5;
      Y[i][j] = rand() % 5;
      SIGMA = rand() % 1001;
    }
  }
  logKde(X, Y, SIGMA, z);
  std::cout << z;
}
