/*
 * @file fa.cpp
 * @Description Perform EM algorithm for factor analysis model
 * @Eqns #12.66: E[z]=G*W*Psi(x-xbar) wheree G=1/(I+W*Psi*W);
 *       #12.67: E[z*z]=G+E[z]*E[z]
 *       #12.69: W=[sum(x-xbar)E[z]][sumE[z*z]]
 *       #12.70: Psi=diag{S-W/N*sum(E[z](x-xbar)}
 */

#include "nr3.h"
#include "cholesky.h"
#include <cmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * m: Dimension of target space
 *Output:
 * W[dxm]: Weight Matrix
 * mu[dx1]: Mean Vector
 * psi[dx1]: Variance Vector
 * llh: loglikelihood;
*/

void fa(MatDoub X, int m, MatDoub &W, VecDoub &mu, VecDoub &psi, Doub &llh){
  int i,j,iter,d=X.nrows(),n=X.ncols(),maxiter=500;
  MatDoub r(d,d),W(d,m),M(d,d),T(d,m),U(d,d),Q(d,d),QQ(d,d),Ez(d,d),V(d,d),Ezz(d,d),Xez(d,d),VV(d,d),EzEz(d,d),WXEz[i][j];
  VecDoub lambda(d,rand());
  Doub mu,sumloglambda,tol=1e-4;
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
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        r[i][j]+=X[j][k]*X[k][j];
      }
    }
  }
  
  for(iter=2;iter<maxiter;iter++){
    for(i=0;i<d;i++){
      lambda[i]=1/rand();
      for(j=0;j<n;j++){
        T[i][j]=W[i][j]-lambda[i];  
      }
      for(i=0;i<d;i++){
        for(j=0;j<d;j++){
          for(k=0;k<n;k++){
            M[i][j]=T[j][k]*T[k][j]+1;
          }
        }
      }
      cholesky(M);
      U=M;
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          WInvPsiX[i][j]=(W[j][k]-lambda)*X[k][j];
        }
      }
      sumloglambda+=lambda[i];
    }
    for(i=0;i<d;i++){
      for(j=0;j<n;j++){
        logdetC[i][j]+=2*log(U[i][j])-sumloglambda;
        Q[i][j]=U[j][j]/WInvPsiX[i][j];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          QQ[i][j]=Q[j][k]*Q[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        trInvCS[i][j]=(r[j][i]*lambda[i]-QQ[i][j])/n;
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        llh(iter)=-n*(d*log(2*pi)+logdetC[i][j]+trInvCS[i][j])/2; 
      }
    }
    if(abs(llh(iter)-llh(iter-1)) < tol*abs(llh(iter-1))); break;
    
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        Ez[i][j]=M[i][j]/WInvPsiX[i][j];
        V[i][j]=U[j][i];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;k++){
          VV[i][j]+=V[j][k]*V[k][j];
          EzEz[i][j]+=Ez[j][k]*Ez[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        Ezz[i][j]=n*(VV[i][j])+EzEz[i][j];
      }
    }
   chol(Ezz);
   U=Ezz;
   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       XEz[i][j]=X[i][j]*Ez[j][i];
     }
   }
   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       W[i][j]=(XEz[i][j]/U[i][j])/U[j][i]
     }
   }
   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       for(k=0;k<d;k++){
         WXEz[i][j]+=W[j][k]*XEz[k][j];
       }
     }  
   }
   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       lambda[i]=n/(r[i][j]-WXEz[i][j]);
     }
   }
 }
 for(i=0;i<d;i++){
   psi[i]=1/lambda[i];
  }
} 
   
}

