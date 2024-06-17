/*
 * @file invpd.cpp
 * @Description Computer A\B where A is a positive definite matrix
 */

#include "nr3.h"
#include "cholesky.h"
#include "inverse.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * M[dxd]: A positive semi-definite. 
 *Output:
 * W[dxd]: (M^-1/2)^T*(M^-1/2) 
*/

void invpd(MatDoub &M){
  MatDoub W(d,d);
  cholesky(M);
  M=inverse(M);
  for(int i=0;i<d;i++){
    for(int j=0;j<d;j++){
      for(int k=0;k<d;k++){
        W[i][j]+=M[j][k]*M[k][j];
      }
    }
  }   
}
