/*
 * @file unituze.cpp
 * @Description Unitized the vectors to be unit length
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxd]: Input Data [Vectors]
 * d: 0=columns, 1=rows
 *Output:
 * Y[dxd]: Output Data [Normalized]
*/

void unitize(MatDoub X, int d, MatDoub &Y, MatDoub &s){
  int i,j,k,d=X.nrows();
  MatDoub S(d,d);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
      S[i][j]+=X[j][k]*X[k][j]; 
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      if(d==0){ 
        s[i][j]=sqrt(S[i][j]);
      } else {
        s[i][j]=sqrt(S[j][i]);
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        Y[i][j]=X[i][j]*s[i][j];
      }
    }
  }
}

