/*
 * @file maxdiff.cpp
 * @Description Difference!
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[d] Input
 * Y[d] Input
 *Output:
 * Z[d] Output
*/

void maxdiff(VecDoub X, VecDoub Y, VecDoub &Z){
  for(int i=0;i<X.size();i++){
    Z[i]=abs(X[i]-Y[i]);
  }
}

