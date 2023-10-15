/*
 * @file linRegEm.cpp
 * @Description Fit empirical Bayesian linear regression model with EM
 * @Eqns 9.63: alpha=M/E[w*w]=M/(m*m+Tr(S))
 *       9.68: 1/beta=((t-phi*m)^2+sum(gam)/beta)/(N);
 */

#include "nr3.h"
#include "cholesky.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 *  X[dxn]: Data
 *  t[1xn]: Response
 *  alpha: Prior Parameter
 *  beta[nxn]: Prior Parameter
 *Output:
 * model: Trained Model Structure
 * llh: log(likelihood)
*/



void linRegEm(MatDoub X, VecDoub t, MatDoub alpha, MatDoub beta, linModel &model, MatDoub &llh){
  int i,j,k,d,n;
  d=X.nrows();
  n=X.ncols();
  MatDoub XX(n,n),Xt(d,n),A(n,n),U(n,n),m(n,n),logdetA(n,n),invU(n,n),trS(n,n),invUX(n,n),trXsX(n,n),w0(n,n);
  Doub xbar,tbar,tol,maxiter,m2,e2,logdetA;
  for(i=0;i<n;i++){
    tbar+=t[i];
    for(j=0;j<d;j++){
      xbar+=X[j][i];
    }
  }  
  xbar/=(d*n);
  tbar/=n;

  for(i=0;i<n;i++){
    t[i]-=tbar;
    for(j=0;j<d;j++){
      X[i][j]-=xbar;
    }
  }
  
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      for(k=0;k<d;k++){
        XX[i][j]=X[k][i]*X[i][k];
      }
      Xt[i][j]=X[i][j]*t[j];
    }
  }
  tol=1*10^-4;
  maxiter=100;
  for(iter=1;iter<maxiter;iter++){
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        A[i][j]=beta[i][j]*XX[i][j]+alpha[i][j];   
      } 
    }
    U=chol(A);
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        m[i][j]=beta[i][j]*(U[i][j]/(U[u][j]/Xt[i][j]));
        for(k=0;k<n;k++){
          m2[i][j]=m[k][i]*m[i][k];
        }
      }
    }
    
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        e2+=(t[i]-m[j][i]*X[i][j])^2;
        logdetA+=2*sum(log(diag(U[i][j])));
      }
    }
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        llh[iter][i]=0.5*(d*log(alpha[i][j])+n*log(beta[i][j])-alpha[i][j]*m2[i][j]-beta[i][j]*e2-logdetA-n*log(2*pi));
      if(abs(llh[iter][i])-llh(iter-1) < tol*abs(llh(llh[iter-1][i])); break; end;
      }
    }
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){ 
        invU[i][j]=U[i][j];
      }
    }
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        for(k=0;k<n;k++){
          trS[i][j]+=invU[k][i]*invU[i][k];
        }
      }
    }
    for(i=0;i<n;i++){
      for(k=0;k<n;k++){
        alpha[i][j]=d/(m2[i][j]+trS[i][j]);
      }
    }
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        invUX[i][j]=U[i][j]/X[i][j];
      }
    }
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        for(k=0;k<n;k++){
          trSX[i][j]+=invUX[k][i]*invUX[i][k];
        }
      }
    }
    for(i=0;i<n;i++){
      for(k=0;k<n;k++){
        beta[i][j]=n/(e2[i][j]+trSX[i][j]);
      }
    }
  }
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      w0[i][j]=tbar-m[i][j]*xbar;
    }
  }
  model.w0=w0;
  model.w=m;
  model.alpha=alpha;
  model.beta=beta;
  model.xbar=xbar;
  model.U=U;
}
