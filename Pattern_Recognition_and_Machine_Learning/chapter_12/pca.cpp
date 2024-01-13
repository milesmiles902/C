/*
 * @file pca.cpp
 * @Description Principal Component Analysis (PCA)
 * @Eqns #12.3: S=[sum(x-xbar)(x-xbar)^T]/N
 *       #12.5: Su1=lambdaU1
 */

#include "nr3.h"
#include "eigen.sym.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * m: Target Dimension
 *Output:
 * U[dxm]: Projection Matrix
 * L[mx1]: Eigenvalues
 * mu[dx1]: Mean
 * mse: Mean Square Error
*/

void pca(MatDoub X, int m, Matdoub &U, VecDoub &L, VecDoub &mu, Doub &mse){
  int i,j,k,m=X.nrows(),n=X.ncols();
  MatDoub Xo(m,n),S(m,n);
  Doub mu;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      mu+=X[i][j];
    }
  }
  mu/=(m*n);
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){ 
      Xo[i][j]=X[i][j]-mu;
    }
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){   
      for(k=0;k<n;k++){
        S[i][j]=Xo[j][k]*Xo[k][j]/n;
      }
    }
  }
  Symmeig E(S);
  U=E.d;
  L=E.z;
}

