/*
 * @file gson.cpp
 * @Description Gram-Schmidt orthonormalization
 * @Eqns proj(v)=<v,u>/<u,u>*u
 */

#include "nr3.h"
#include <cmath>
#include <iostream>

/*
 *Input:
 * X[dxd]: Data Matrix
 *Output:
 * Q[dxd]: Orthonormalized Vectors
 * R[dxd]: Normalized Vectors
*/

void gson(MatDoub X, MatDoub &Q, MatDoub &R){
  int i,j,k,d=X.nrows();
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        R[i][j]+=Q[j][k]*X[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        v[i][j]-=Q[k][j]*X[k][j];
      }
      v[i][j]+=X[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        R[i][i]=v[j][k]*v[j][k];
      }
    }
    R[i][i]=sqrt(R[i][i]);
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      Q[i][j]=v[i][j]/R[i][i];
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

