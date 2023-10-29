/*
 * @file pcaEmC.cpp
 * @Description A Constrained EM Algorithm for Principal Component Analysis
 */

#include "nr3.h"
#include <iostream>
#include <csmath>

/*
 *Input:
 * X[dxn]: Data Matrix
 * m: Dimension of Target Space
 *Output:
 * W[dxm]: Weight Matrix
 * Z[mxn]: Projected Data Matrix
 * mu[dx1]: Mean Vector
 * mse: Mean Square Error
*/

void pcaEmC(MatDoub X, int m, MatDoub &W, MatDoub &Z, VecDoub &mu, int mse){
  int i,j,d=X.nrows(),n=X.cols(),iter,maxIter=200;
  MatDoub WX(m,n),WW(d,d);
  Doub mu,tol=1*exp(-6);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      mu+=X[i][j];
    }
  } 
  mu/=(d*n);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]-=mu;
    }
  }  
  for(iter=1;iter<maxIter;iter++){
    for(i=0;i<m;i++){
      for(j=0;j<m;j++){
        for(k=0;k<n;k++){
          WW[i][j]+=W[j][k]*W[k][j];
      }
    }
    for(i=0;i<m;i++){
      for(j=0;j<n;j++){
        for(k=0;k<d;k++){
          WX[i][j]+=W[i][k]*X[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;j++){
          if(j<k) Z[i][j]+=WW[j][k]/WX[k][j];
        }
      }
    } 
  }
}

