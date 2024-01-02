/*
 * @file solvpd.cpp
 * @Description Computer A\B where A is a positive definite matrix
 */

#include "nr3.h"
#include <cmath>
#include <iostream>

/*
 *Input:
 * A[dxd]: Input Data
 * B[dxd]: Input Data
 *Output:
 * V[dxd]: Output Data
*/

void solvpd(MatDoub A, MatDoub B, MatDoub V){
  for(int i=0;i<A.nrows()){
    for(int j=0;j<A.ncols()){
      V[i][j]=A[i][j]/B[i][j];
    }
  }
}


