/*
 * @file mixLogitBin.cpp
 * @Description Mixture of logistic regression model for binary classification optimized by Newton-Raphsen methods
 */

#include "nr3.h"
#include <csmath>
#include <iostream>
#include <random>

/*
 *Input:
 * X[dxn]: Data Matrix
 * t[1xn]: Label (0/1)
 * k: Number of Mixture Components
 *Output:
 * model: Trained model Structure
 * llh: loglikelihood
*/

MatDoub newtonStep(MatDoub X, VecDoub t, MatDoub Y, MatDoub W, VecDoub R){
  int i,j,k,d=Y.ncols(),n=Y.nrows();
  MatDoub v(d,n),H(d,n),s(d,n),g(d,n);
  Doub lambda=0.000006;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      v[i][j]=Y[i][j]*(1-Y[i][j])*R[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        H[i][j]=X[j][k]*v[k][j];
      }
      H[i][j]+=lambda;
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
        s[i][j]=(Y[i][j]-t[i])*R[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;j<n;k++){
        g[i][j]+=X[j][k]*s[k][j];
      }  
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      W[i][j]-=H[i][j]/g[i][j];
    }
  }
  return W;
}

void mixLogitBin(MatDoub X, VecDoub t, int k, mixLogitBin &model, Doub &llh){
  int i,j,k,maxiter=100,d=X.nrows(),n=X.ncols();
  Doub T,sumlogRho,tol=0.0001;
  VecDoub nk(d),alpha(d),z(n,rand());
  MatDoub R(d,k),W(d,k),A(d,d),Y(d,d),logRho(d,d),logR(d,d);
  
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        A[i][j]+=X[i][j]*W[j][k];
      }
    }
  }
  for(iter=1;iter<maxiter;iter++){
    for(i=0;i<d;i++){
      for(j=0;j<k;j++){
        nk[i]+=R[i][j];
      }
    }
    for(i=0;i<d;i++){
      alpha[i]=nk[i]/n;
    }
    Y=sigmoid(A);
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        W[i][j]=newtonSteo(X,t,Y,W,R);
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        A[i][j]+=X[j][k]*W[k][j];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<n;j++){
        logRho[i][j]=-log(1+exp(-A[i][j]*h[i])) + log(alpha[i][j]);
        sumlogRho+=logRho[i][j]; 
      }
    }
    T=log(sumlogRho);
    llh[iter]=T/n;
    for(i=0;i<d;i++){
      for(j=0;j<n;j++){
        logR[i][j]-=T;
        R[i][j]=exp(logR[i][j]);
      }
    }
  } 
  model.alpha=alpha;
  model.W=W;
}

