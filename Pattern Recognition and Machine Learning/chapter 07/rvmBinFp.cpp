/*
 * @file rvnBinFp.cpp
 * @Description Relevance Vector Machine (ARD sparse prior) for binary classification.
 * Trained by Empirical Bayesian (Type II ML) using Mackay fix point update.
 * @Eqns #7.110: del[ln(p(w|t,alpha))]=phi*(t-y)-A*w 
 *       #7.111: del[del[ln(p|t,alpha)]]=-(phi*B*phi+A)
 *       #7.112: w*=(A^-1)*phi*(t-y)
 *       #7.113: sigma=(phi*B*phi+A)^-1
 *       #7.114: p(t|alpha)=integral(p(t|w)*p(w|alpha)dw=p(t|w*)p(w|alpha)*2pi^M/2*sigma^1/2
 *       #7.118: lnp(t|alpha,beta)=-1/2{Nln(2pi)+ln|C|+ t^T*C^-1*t}
 *       #7.89:  gamma=I-alpha*sigma
 *       #7.87:  alpha=gamma/m^2
 *       #7.116: alpha=gamma/w^2
 *       #4.87:  p(C|phi)=y(phi)=sigma(w*phi);
 *       #4.98:  R=y(1-y);
 *       #4.97:  H=del[del[E(w)]]=sum(y(1-y)phi*phi)=phi*r*phi
 *       #4.96:  del[E(w)]=sum(y-t)*phi=phi*(y-t)
 *       #4.92:  w=w-(H^-1)*del[E(w)]
 *       #4.89:  p(t|w)=PI(y)^t * (1-y)^{1-t}
 */

#include "nr3.h"
#include <csmath>
#include <iostream>
#include "logitBin.cpp"
#include "inverse.cpp"

/*f
 *Input:
 * X[dxn]: Data Matrix
 * t[1xn]: Binary label (0/1)
 * alpha: Prior Parameter
 *Output:
 * model: Trained model structure
 * llh: loglikelihood
*/

void rvmBinFp(MatDoub X, VecDoub t, int alpha){
  int i,j,xrow,xcol,iter,maxiter;
  
  maxiter=100;
  xrow=X.nrow();
  xcol=X.ncol();
  MatDoub V(xrow,xcol),dgS(xrow,xcol);
  VecDoub a(xrow),m(xrow),llh(maxiter),idx(xrow),m2(xrow);
  Doub tol,nz,m2,digX;
  for(i=0;i<xrow;i++){
    m[i]=0;
    llh[i]=0;
    idx=i;
  }
 
  tol=0.001;
  for(iter=1;iter<maxiter;iter++){
    for(i=0;i<xrow;i++){
      for(j=0;j<xcol;j++){
        if(X[i][j]==0){ X[i][j]=1./alpha;}
      }
    }
    logitBin(X,t,alpha,m[0]);
    for(i=0;i<xrow;i++){
      digX+=X[i][i];
    }
    for(i=0;i<xrow;i++){
      m2[i]=m[0]*m[0];
      llh[iter]=t[xrow-1]+0.5*(xrow*log(alpha))-2*sum(log(sumX))-alpha*m2[i]-log(2*PI());
      if(abs(llh[iter]-llh[iter-1])<tol*abs(llh[iter-1])){ break;}
    }
    inverse(X,V,xrow);
    for(i=0;i<xrow,i++){
      for(j=0;j<xcol;j++){
        for(k=0;k<xrow;k++){
          dgS[i][j]+=V[i][k]*V[k][j];
        }
      }
    }
  }
  llh.resize(iter);
  std::cout << "m: " << m
  std::cout << "alpha: " << alpha; 
  //What should the model return for the predictor [Model Parameters]???
  //return m;
}

int main(){
  Int i,j,n,m,lambda;
  n=3;
  m=3;
  MatDoub X(m,n);
  VecDoub t(n);
  
  lambda=1;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
    t[i]=rand()%2;
  } 
  rvmBinFp(X,t,lambda);
}
