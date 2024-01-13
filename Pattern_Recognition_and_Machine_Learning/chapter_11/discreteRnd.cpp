/*
 * @file discreteRnd.cpp
 * @Description Generate samples from a discrete distribution (multinomial
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * p[dxk]: K-dimensional probability vector
 * n: Number of samples
 *Output:
 * x[kxn]: Generated samples from multinomial(p);
*/

VecDoub discreteRnd(MatDoub X, VecDoub n){
  int i,j,size=n.size();
  VecDoub x(size)
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      x[i]+=x[j]*rand()*X[1][j];
    }
  }
  return x;
}
