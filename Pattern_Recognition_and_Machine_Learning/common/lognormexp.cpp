/*
 * @file lognormexp.cpp
 * @Description Computer log(normalize(exp(x),dim)) while avoiding numerical underflow
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxd]: Input data
 * dim: 1=columns,2=rows
 *Output:
 * Y: Value
*/

void lognormexp(MatDoub X, VecDoub dim, Doub &s, Doub &Y){
  s=logsumexp(X,dim);
  Y=X-s;
}

