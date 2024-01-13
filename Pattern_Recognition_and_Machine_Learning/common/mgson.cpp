/*
 * @file mgson.cpp
 * @Description Modified Gram-Schmidt orthonormalization (numerical stable version of Gram-Schmidt algorithm)
 *              which produces the same result as [Q,R]=qr(X,0)
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxd]: Input Data
 *Output:
 * Q[dxd]: Orthogonalized Data
 * R[dxd]: Normalized Data
*/

void mgson(MatDoub X, MatDoub &Q, MatDoub &R){
  int i,j,k,d=X.nrows();
  VecDoub v(d);
  for(i=0;i<d;i++){
    for(j=0;j<n;i++){
      v[i]=X[i][j];
    }
    for(j=0;j<i-1;j++){
      R[j][i]=Q[i][j]*v[i];
      v[i]-=R[j][i]*Q[i][j]
    }
    R[i][i]=sqrt(v[i]);
    for(j=0;j<d;j++){
      Q[i][j]=v[i]/R[i][i];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        R[i][j]+=Q[j][k]*X[k][j];
      }
    }
  }
}

