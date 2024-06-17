/*
 * @file hmmEm.cpp
 * @Description EM algorithm to fit the parameters of Hmm model (aka Baum-Welch algorithm)
 * @Eqns #13.18: pi=gam(z)/sum[gam(z)]
 *       #13.19: A=sum[eta(z_{n-1},z_{n}]/sum[sum[z_{n-1},z_{n}]]
 *       #13.23: mu=sum[gam(z_{n})]*x_n/sum[gam(z)]
 *       #13.43: eta(z_{n-1},z_{n})=p(z_{n-1},z_{n}|X)
 *       #13.65: eta(z_{n-1},z_{n})=c_n*alpha(z_{n-1})*p(x|z)*p(z_{n}|z_{-1})*beta(z)
 *       #13.59: c_n*alpha(z_n)=p(x|z)*sum[alpha(z_{n-1})*p(z|z_{n-1}]
 *       #13.62: c_{n+1}*beta(z_n)=sum[beta(z_{n+1})*p(x_{n+1}|z_{n+1})**p(z_{n+1}|z_{n}]
 *       #13.64: gam(z)=alpha(z)*beta(z)
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[1xn]: Integer vector which is the sequence of observations
 * init: Model or k
 *Output:
 * model: Trained model structure
 * llh: loglikelihood
*/

void hmmSmoother(MatDoub M, MatDoub A, MatDoub s, MatDoub &gamma, MatDoub &alpha, MatDoub &beta, VecDoub &c){
  int i,j,k,d=M.nrows(),d=M.ncols();
  MatDoub At(d,n),AbM(d,d);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        alpha[i][j]+=s[j][k]*M[k][j];
      }
      c[i]+=alpha[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        AbM[i][j]+=beta[j][k]*M[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        beta[i][j]+=A[j][k]*AbM[k][j]/c[i];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        gamma[i][j]+=alpha[j][k]*beta[k][j];
      }
    }
  }
}

void hmmEm(VecDoub X, hmmEMModel init, hmmEmModel &model, Doub llh){
  int i,j,k,iter,d=X.nrows(),n=X.ncols(),maxiter=1000;
  MatDoub A(d,n),E(d,n),s(d,n),M(d,n),gamma(d,n),alpha(d,n),beta(d,n,1),c(d,n),abMc(d,d);
  VecDoub Amean(n),gammean(n);
  Doub tol=0.0001;
  A=init.A;
  E=init.E;
  s=init.s;

  for(iter=2;iter<maxiter;i++){
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          M[i][j]+=E[j][k]*X[k][j];
        }
        llh[iter]+=log(c[i][j]);
      }
    }
    hmmSmoother(M,A,s,gamma,alpha,beta,c);
    if(abs(llh[iter]-llh[iter-1])<tol*abs(llh[iter-1])) return;
    s=gamma;
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          abMc[i][j]+=(alpha[i][j]*beta[i][j]*M[i][j])/c[i][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          A[i][j]+=A[j][k]*abMc[k][j];
        }
        Amean[i]+=A[i][j];
        gammean[i]+=gamma[i][j];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        A[i][j]/mean[i];
        for(k=0;k<n;k++){
          E[i][j]+=gamma[j][k]*X[k][j]/gammean[i];
        }
      }
    }
  }
  model.s=s;
  model.A=A;
  model.E=E;
}

int main(){
  Int i,j,n,m,lamda;
  n=3;
  m=3;
  MatDoub X(m,n);
  VecDoub t(n);
  
  lambda=2;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
    t[i]=rand()%10;
  } 
  XXX(X,t,lambda);
}
