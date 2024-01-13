/*
 * @file ud.cpp
 * @Description UD factorization U'*D*U=X'*X;
 */

#include "nr3.h"
#include "cholesky.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxd]: Input Matrix
 *Output:
 * U[dxd]: Output Data [Diagnolized]
 * D[dxd]: Output Data [Eigenvectors]
*/

void ud(MatDoub X, MatDoub &U, MatDoub &D){
  Cholesky X = new Cholesky(X);
  U=X;
  D=X.solve();
}
