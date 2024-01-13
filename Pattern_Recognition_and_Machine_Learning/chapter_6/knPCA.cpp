/*
 * @file .cpp
 * @Description knPCA
 * @Eqn #12.1 Mean: E[x]=sum(x)/n;
 *  Eqn #12.2 Variance: uSu=E[ux-uE[x]]^2
 *  Eqn #12.3 Covariance: S=E[x-E[x]]^2
 *  Eqn #12.4 Lagrange Multiplier: uSu+lamda(1-uu) ..with normalization condition uu=1;
 *  Eqn #12.5 Stationary Point: Su=lambda*u
 *  Eqn #12.6 Variance of Lambda: uSu=lambda;
 *  Eqn #12.7 Minimum error: uu~=1;
 *  Eqn #12.8 Linear combination of Basis: x=sum(alpha*u);
 *  Eqn #12.9 Inner product: x=sum((xu)*u);
 *  Eqn #12.10 Projection to (N-1)-subspace: ~x=sum_1_M(zu)+sum_(M+1)_D(bu)
 *  Eqn #12.11 Mean Squared Eror: J=E[x-~E[x]]^2
 *  Eqn #12.12 Orthonormality Conditions: z=xu
 *  Eqn #12.13 Orthnormality Relations: b=E[x]u
 *  Eqn #12.14 Substituting 12.12,12.13: x-~E[x]=sum(x-E[x])u;
 *  Eqn #12.15 Distortion Measure (Expected Variance beyond M+1): 
 *             J=E[ sum_(M+1)_d (E[ux-uE[x]]^2)^2 ]=sum_(M+1)_D(uSu);
 *  Eqn #12.16 Minimization of Enforcement Contraint: ~J=uSu+lamda(1-uu);
 *  Eqn #12.17 Eigenvectors of Covariance Matrix: Su=lamda*u;
 *  Eqn #12.18 Distortion Measure: J=sum_(M+1)_D( lambda);
 */

#include "nr3.h"
#include "eigen.sym.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[(ell+1)xt]: Kernel Matrix
 * k: Projection Space
 *Output:
 * V[ellxk]:First k eigenvectors
 * L[kxk]: Diagnol Matrix
*/

void knPCA(MatDoub X, VecDoub k){
  int i,j,xrow=X.nrow(),xcol=X.ncol();
  MatDoub J(xrow,xcol), Test(xrow,xcol), Train(xrow,xcol), Knew(xrow,xcol),Ktest(xrow,xcol),Ktested(xrow,xcol),pers(xrow,xcol);
  VecDoub invL(xrow),sqrtL(xrow),invsqrtL(xrow);
  Doub D,E,sumX,sumD;
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      Xsum+=X[i][j];
    }
  }
  D=Xsum/(nrow*ncol);
  E=D/(nrow*ncol);
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      J[i][j]=D;
    }
  }
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      X[i][j]=X[i][j]-2J[i][j]+E;
    }
  }
  Symmeig s(K); 
  for(i=0;i<xrow;i++){
    invL[i]=1/s.d[i];
    sqrtL[i]=sqrt(s.d[i]);
    invsqrtL[i]=1/sqrtL[i];
  }
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      Test[i][j]=invsqrtL*s.z[j][i]; //12.15 Sum-squres of norm projects
      Train[i][j]=sqrtL*s.z[j][i];
      pers[i][j]=invsqrtL*s.z[j][i]*K[i][j];
    }
  } 
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      Knew[i][j]=s.z[i][j]*s.d[i]*s.z[j][i];
      Ktest[i][j]=s.z[i][j]*s.z[j][i];
      Ktested[i][j]=s.z[i][j]*invL[i]*s.z[j][i];
    }
  }
  //cout or examine residual of test points
}

int main(){
  Int i,j,n,m,k;
  n=3;
  m=3;
  k=3;
  MatDoub X(m,n);
  
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
  } 
  knPCA(X,k);
}
