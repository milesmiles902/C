/*
 * @file normalize.cpp
 * @Description Normalize the vectors to be summing to one
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxd]: Input Data
 * dim: Dimensions
 *Output:
 * Y[dxd]: Output Data
 * s: sum
*/

void normalize(MatDoub X, int dim, MatDoub &Y, int &s){
  int i,j,k;
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      if(dim==1){
        s+=X[i][j]
      } else {
        s+=X[j][i];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      Y[i][j]=X[i][j]/s;
    }
  }
}
