/*
 * @file slice.cpp
 * @Description slice(A,2,index) = A(:,index, :)
 */

#include "nr3.h"
#include <cmath>
#include <iostream>

/*
 *Input:
 * A[dxdxd]: Input 
 * dim: 1 = col, 2 = row
 * index: index
 *Output:
 * B[dxd]: Output slice
*/

void slice(VecDoub A, int dim, VecDoub index, MatDoub &B){
  for(int i=0;i<A.nrows();i++){
    for(int j=0;j<A.nrows();j++){
      if(dim==1){
        B[i][j]=A[i][index][j];
      } else {
        B[i][j]=A[j][index][i];
      }
    }
  }
}

