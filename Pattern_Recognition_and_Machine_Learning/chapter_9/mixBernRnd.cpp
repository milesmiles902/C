/*
 * @file mixBernRnd.cpp
 * @Description Generate samples from a Bernoulli distribution
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * d: Dimensions of Data
 * k: Number of Components
 * n: Number of Data
 *Output:
 * X[dxn]: Data Matrix
 * z[1xn]: Response Variable
 * mu[dxk]: Parameters of each Bernoulli component
*/

void mixBernRnd(int d, int k, int n, MatDoub &X, VecDoub &z, MatDoub &mu){
  int i,j;
  MatDoub mu(d,k,rand()),X(d,n);
  VecDoub w(k),z(k);
  z=discreteRnd(w,n);
  for(i=0;i<k;k++){
    if(rand()*sum(i)<mu[i][j]) X[i][j]=true;
  }
}

