/*
 * @file ld.cpp
 * @Description LD factorization produce LDL'=X*X' which is the same as [L,D] = ldl(X*X');
 *              the underlying algorith is a Gram-Schmidt orthogonalization
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Input Data
 *Output:
 * L[dxd]: LD Factorized Matrix
*/

void ld(MatDoub X){
  int i,j,k,d=X.nrows(),n=X.ncols();
  MatDoub D(d,n),M(d,n,0),Q(d,n,0),L(d,n,1);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        L[i][j]=v[k][j]*Q[k][j]/D[j];
        v[i][j]-=L[j][k]*Q[k][j];
        D[i][j]=Q[j][k]*Q[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        L[i][j]=X[j][k]*Q[k][j]/D[j];
      }
    }
  }
}

