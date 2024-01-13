/*
 * @file .cpp
 * @description Compute log pdf of a Gaussian Distribution
 */

#include <cmath>
#include <iostream>
#include <array>
#include <cassert>
#include "nr3.h"
#include "cholesky.h"

/*
 * @brief Compute log of a Gaussian N(x|mu,sigma^2)
 * @param x: DxN data matrix
 * @param mu: Dx1 mean vector of Gaussian
 * @param sigma: DxD covariance matrix of a Gaussian
 * @return y: 1xN probability density in logarithm scale y=log p(x)
 */
#include <cstdlib>
void logGauss(MatDoub &x,
              VecDoub &mu,
              MatDoub &sigma,
              VecDoub &q){
  int i,j,k,row,col,sum=0;
  row=x.nrows();
  col=x.ncols();

  MatDoub Q(row,col);
  VecDoub c();

  for (i; i<row; i++){
    for (j; j<col; j++){
      x[i][j]=x[i][j]-mu[j];
    }
  }
  Cholesky myCholesky(sigma);
  myCholesky.inverse(sigma);
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      Doub temp(0.0);
      for(k=0;k<col;k++){
        temp += sigma[i][j]*x[j][k];
      }
      Q[i][j]=temp;  
    }
  }
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      q[i*row+j]=-(Q[i][j]*Q[j][i]+log(x[i][i])+row*log(2*M_PI))/2;
    };
  };
}

void test(VecDoub q){
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      std::cout << q[i*5+j] << " ";  
    }
    std::cout << std::endl;
  }
}

int main(){
  MatDoub X(5,5), SIGMA(5,5);
  VecDoub MU(5), q(25);
  for (Int i=0;i<5;i++){
    for (Int j=0;j<5;j++){
      X[i][j]=0;
      SIGMA[i][i]=0.05;
      MU[i] = 0;
    }  
  }
  logGauss(X, MU, SIGMA, q);
  test(q);
}
