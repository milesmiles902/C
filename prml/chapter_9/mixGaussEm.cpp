/*
 * @file mixGaussEm.cpp
 * @Description Perform EM algorithm for fitting the Gaussian mixture model
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrx
 * init: K-number of components or label(1xn,l<=label(i)<=k) or model structure
 *Output:
 * label[1xn]: Cluster label
 * model: Trained model structure
 * llh: loglikelihood
*/
void loggausspdf(MatDoub X, MatDoub mu, MatDoub Sigma, MatDoub &y){
  int i,j,d,n;
  MatDoub U(d,n),Q(d,n),q(d,d);
  Doub c;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]-=mu[i][j];
    }
  }
  cholesky(Sigma);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      Q[i][j]=U[i][j]/X[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        q[i][j]=Q[j][k]*Q[k][j]; 
      } 
    c+=log(diag(U[i][i]); 
    }
  }
  c+=d*log(2*PI());
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      y[i][j]=-(c+q[i][i])/2;
    }
  }
}

void maximization(MatDoub X, MatDoub R, mixGaussEm &model){
  int i,j,d,n;
  d=X.nrows();
  n=X.ncols();
  MatDoub mu(d,n),sigma(d,d,0),r(d,n),Xo(d,n);
  VecDoub k(n),nk(d),w(n);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      nk[d]+=R[i][j];
    }
    w[d]=nk[d]/n;
  }
   
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      mu[i][j]=X[i][j]*R[i][j]/nk[d];
      r[i][j]=sqrt(R[i][j]);
    }
  }
  for(i=0;i<d;i++){
   for(j=0;j<n;j++){
     Xo[i][j]=(X[i][j]-mu[i][j])*r[i][j];
    
   } 
  }
  model.mu=mu;
  model.sigma=sigma;
  model.w=w;
}

void expectation(MatDoub X, mixGaussEm model, MatDoub &R, int &llh){
  int i,j,d,n;
  d=X.nrows();
  n=X.ncols();
  MatDoub mu(d,n),sigma(d,n),w(d,n),R(d,n,0);
  mu=model.mu;
  sigma=model.sigma;
  w=model.w;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){ 
      loggausspdf(X,mu,sigma,R);
    }
  }
  
   .....

 
}

void initialization(MatDoub X, mixGaussEm model,int init, MatDoub &R){
  int d,n;
  d=X.nrows();
  n=X.ncols();
  MatDoub R(d,n,rand());
  if(init) expectation(X,model,R,llh);
}

void (MatDoub X, int init, VecDoub &label, mixGaussEm &model, int &llh){
  int i,j,k,d,n,iter,maxiter=500;
  d=X.nrows();
  n=X.ncols();
  MatDoub R(d,n);
  Doub tol=1*10^-6;
  initialization(X,model,init,R);
  for(iter=1;iter<maxiter;iter++){
    for(i=0;i<n;i++){ 
      for(j=0;j<d;j++){
        if(R[j][i]>label[i]) label[i]=R[j][i];
      }
    }
    maximization(X,R,model);
    expectation(X,model,R,llh);
    if(abs(llh[iter]-llh[iter-1]) < tol*abs(llh[iter])) break;
  }
}
