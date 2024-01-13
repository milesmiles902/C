/*
 * @file besseliLn.cpp
 * @Description Computer logarithm of Besseli function (modified Bessel function of the first kind)
 * @Equation: Ja = sum [(-1)^m / (m!*gam(m+a+1)) ](x/2)^(2m+a)
 */

#include "nr3.h"
#include <cmath>
#include <iostream>

/*
 *Input:
 * X[dxd] Besseli Data
 *Output:
 * X[dxd]: log(Besseli Data)
*/

void besseliLn(MatDoub &X){
  for(int i=0;i<X.nrows();i++){
    for(int j=0;j<X.ncols();j++){
      X[i][j]=log(cyl_bessel(0,X[i][j]));
    }
  }
}

