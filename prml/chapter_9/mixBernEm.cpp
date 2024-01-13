/*
 * @file mixBernEm.cpp
 * @Description Perform EM algorithm for fitting theBernoulli mixture model
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Binary (0/1) Data Matrix
 * k: Number of Clusters
 *Output:
 * label[1xn]: Cluster Label
 * model: Trained model Structure
 * llh: Loglikelihood
*/

void expectation(MatDoub X, mixBernEm model, MatDoub &R, VecDoub &llh){
  int i,j,d,n,lsize;
  d=X.nrows();
  n=X.ncols();
  MatDoub mu(d,n),w(d,n);
  VecDoub sumexp(d);
  mu=model.mu; 
  w=model.mu;
  for(i=0;i<n;i++){
    for(j=0;j<d;j++){
      R[i][j]=X[i][j]*log(mu[i][j])+(1-X[i][j])*log(1-mu[i][j])+log(w[i][j]); 
      sumexp[j]+=exp(R[i][j]);
    }
  }
  for(i=0;i<d;i++){
    llh+=log(sumexp[i]);
  }
  llh/=d;
  for(i=0;i<n;i++){
    for(j=0;j<d;j++){
      R[i][j]=exp(R[i][j]-llh);
    }
  }
}

void maximization(MatDoub X, MatDoub R, mixBernEm &model){
  int i,j,k,d,n;
  d=X.nrows();
  n=X.ncols();
  MatDoub mu(d,n); 
  VecDoub nk(n);
  Doub w;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      nk[j]+=R[i][j];
    }
  }
  for(i=0;i<n;i++){
    w+=nk[j]
  }
  w/=n;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      for(k=0;k<d;k++){
        mu[i][j]+=X[k][i]*R[i][k]/nk[k]; 
      }
    }
  }
  model.mu=mu;
  model.w=w;
}

void mixBernEm(MatDoub X, int k, VecDoub &label, mixBernEm &model, VecDoub &llh){
  int i,j,k,d,n,lsize,iter,maxiter=500;
  d=X.nrows();
  n=X.ncols();
  MatDoub R(d,n);
  Doub max,tol=1*10^-8;
  for(iter=0;iter<maxiter;iter++){
    maximization(X,R,model);
    expectation(X,model,R,llh);
    if(abs(llh[iter]-llh[iter-1])<tol*abs(llh[iter])) break;
  }
  for(i=0;i<d;i++){
    max=0;
    for(j=0;j<n;j++){
      if(R[j][i]>max) label[i]=R[j][i]; 
    }
  }
}
