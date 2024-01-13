/*
 * @file hmmSmoother.cpp
 * @Description HMM smoothing algorithm (also know as normalized forward-backwater, normalized alpha-beta algorithm)
 *              The alpha and beta returned by this function are the normalized version.
 * @Eqns #13.59: c*alpha(z)=p(x_n|z_n)*sum[alpha(z_n-1)*p(z_n|z_n-1)]
 *       #13.62: c_n+1*beta(z)= sum[beta(z_n+1)*p(x_n+1|z_n+1)*p(z_n+1|z_n)]
 *       #13.64: gamma(z)=alpha(z)*beta(z)
 */

#include "nr3.h"
#include "inverse.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[1xn]: Integer vector containin sequence of observations
 * model: A Model
 *   model.s[mx1]: Start probabiliy vector
 *   model.A[mxm]: Transition Matrix
 *   model.E[mxd]: Emission Matrix
 *Output:
 * gamma[mxn]: Matrix of posterior gamma(t)=p(z_t,x_{1:T});
 * alpha[mxn]: Matrix of posterior alpha(t)=p(z_t|x_{1:T});
 * beta[mxn]: Matrix of posterior beta(t)=gamma(t)/alpha(t);
 * c[1xn]: Normalization constant vector
*/

void hmmSmoother(VecDoub &X, hmmModel &model, MatDoub &gamma, MatDoub &alpha, MatDoub &beta, VecDoub &c){
  int i,j,k,m=alpha.nrows(),n=alpha.ncols();
  MatDoub A(m,n)=model.A,s(m,n)=model.s,E(m,n)=model.E, X(m,n,1),M(m,m),At(m,m),betaM(m,m),AbetaM(d,d);
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      for(k=0;k<m;k++){
        M[i][j]+=E[j][k]*X[k][j];
      } 
    }
  }
  At=inverse(A); 
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
       sMmean[j]+=s[i][j]*M[i][j]; 
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      M[i][j]/=sMmean[i];
    }
  }
  for(i=0;i<m;i++){
    alpha[i][0]=M[i][0];;
  }

  for(i=0;i<m;i++){
    for(j=1;j<m;m++){
      alpha[i][j]=M[i][j];
    }
  }
  c=sMean;
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      for(k=0;k<m;k++){
        betaM[i][j]+=beta[j][k]*M[k][j];
      }
    }
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      for(k=0;k<m;k++){
        AbetaM[i][j]+=A[j][k]*betaM[k][j];
      }
    }
  }
  for(i=m;i>1;i--){
    for(j=m;j>1;j--){
      beta[i][j]=AbetaM[i][j]/c[i+1];
    }
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      gamma[i][j]+=alpha[i][j]*beta[i][j];
    }
  }
}

