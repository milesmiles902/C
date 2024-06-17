/*
 * @file nbGauss.cpp
 * @Description Naive Bayes classifier with independent Gaussian
 * @Eqns #
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * t[1xn]: label
 *Output:
 * model: trained model structure
*/

struct fit{
  Doub w;
  MatDoub mu;
  MatDoub var;
}

void nbGauss(fit model, MatDoub X, VecDoub t){
  int i,j,k,m,n;
  m=X.nrow();
  n=X.ncol();
  k=t.size();
  MatDoub E(k,n),R(k,n);
  Doub nk,mu,var;
  for(i=0;i<k;i++){
    for(j=0;j<n;j++){
      nk+=E[i][j];
    }
  }  
  w=nk/(k*n);
  for(i=0;i<k;i++){
    for(j=0;j<n;j++){
      R[i][j]=E[j][i]/nk;
      mu[i][j]=X[i][j]*R[i][j];
    }
  }
  mu/=(k*n);
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      var[i][j]=X[i][j]*X[i][j]*R[i][j]-mu[i][j]*mu[i][j];
    } 
  }
  model.mu=mu;
  model.var=var;
  model.w=w;
}

int main(){
  Int i,j,n,m,lamda;
  n=3;
  m=3;
  fit model;
  MatDoub X(m,n);
  VecDoub t(n);
  
  lambda=2;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
    t[i]=rand()%10;
  } 
  nbGauss(model,X,t,lambda);
}
