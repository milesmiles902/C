/*
 * @file logsumexp.cpp
 * @Description Computer log(sum(exp(X),dim)) while avoiding numerical underflow
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxd]: Input data
 * dim: 1=colums,2=rows
 *Output:
 * s: Output data
*/

void logsumexp(MatDoub X, int dim, VecDoub &s){
  int i,j,d=X.nrows();
  VecDoub a(d,0);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      if(dim==1){
        if(a[i]<X[i][j]){
          a[i]=X[i][j];
        }
      } else {
        if(a[i]<X[j][i]){
          a[i]=X[i][j];
        }
      }
    }
  }

  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      s[i]+=exp(X[i][j]-a[i])
    }
    s[i]=log(s)+a[i];
  }  
  for(i=0;i<d;i++){
    s[i]=a[i];
  }
}

