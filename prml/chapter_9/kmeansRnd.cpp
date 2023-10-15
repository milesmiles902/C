/*
 * @file kmeansRand.cpp
 * @Description Generate samples from a Gaussian mixture distribution with common variances (kmeans model)
 */

#include "nr3.h"
#include "dirichletRnd.cpp"
#include "discreteRnd.cpp"
#include <csmath>
#include <iostream>

/*
 *Input:
 *d: Dimensions of Data
 *k: Number of Components
 *n: Number of Data
 *Output:
 *X[dxn]: Data Matrix
 *z[1xn]: Response Variable
 *mu[dxk]: Centers of Clusters
*/

void kmeansRnd(int d, int k, int n){
  int i,j;
  MatDoub X(d,n),w(d,n),E(n,n,0),mu(d,n);
  VecDoub alpha(d,1),invk(k,1/k),z(n);
  
  Doub beta=pow(k,d);
  for(i=0;i<d,i++){
    for(j=0;j<n;j++){
      X[i][j]=rand();
    }
  }
  w=dirichletRnd(alpha,invk);
  z=discreteRnd(w,n);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      mu[i][j]=rand()*beta;
      X[i][j]+=mu[i][j]*E[i][j];
    }
  }
}


