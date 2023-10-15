/*
 * @file .cpp
 * @brief Compute log pdf of von Mises-Fisher distribution.
 */
#include <cmath>
#include <iostream>
#include "nr3.h"

using namespace std;

MatDoub logVmf(MatDoub X, MatDoub mu, MatDoub kappa, MatDoub &y){
  int i,j,xrow,xcol,mucol;
  xrow = X.nrows();
  xcol = X.ncols();
  mucol = mu.ncols();
  MatDoub c(xrow,xcol),q(xrow,mucol);
  VecDoub d(xrow);
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      c=(d[i]/2-1)*log(kappa[1][1])-(d[i]/2)*log(2*M_PI)-std::cyl_bessel_j(d[i]/2-1,kappa);
    }
    for(j=0;j<mucol;j++){
      q[i][j]=mu[i][j]*kappa[1][1]*X[i][j];
    }
    for(j=0;j<xcol;j++){
      y[i][j]=q[i][j]*c[i][j];
    }
  }
}


/*
 * Input:
 *   X: d x n data matrix
 *   mu: d x k mean
 *   kappa: 1 x k variance
 * Output:
 *   y: k x n
 */


int main(){
  int i,j,d,n,k,sum;
  d=5;
  n=6;
  k=1;
  MatDoub X(d,n),mu(d,k),kappa(1,k), y(k,n);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()/5;
      sum+=X[i][j];
    }
    mu[i][k]=sum/(n);
  }
  std::cout << std::cyl_bessel_j(0,50);
  logVmf(X,mu,kappa,y);  
  for(i=0;i<k;i++){
    for(j=0;j<n;j++){
      std::cout << y[i][j] << std::endl;
    }
  }
}


