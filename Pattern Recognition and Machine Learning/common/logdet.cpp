/*
 * @file logdet.cpp
 * @Description Computer log(det(A)) where A is positive definite
 */

#include "nr3.h"
#include "cholesky."
#include <csmath>
#include <iostream>

/*
 *Input:
 * A[dxd]: Input
 *Output:
 * y: Output
*/

void logdet(MatDoub A, MatDoub &y){
  int i,j,d=A.nrows();
  cholesky(A);
  
  for(i=0;i<d;i++){
    y+=2*log(A[i][j]);
  }
}

