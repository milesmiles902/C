/*
 * @file dirichletRnd.cpp
 * @Description Generate sampples from a Dirichlet distribution
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 *a[1xk]: K-dimensional vector
 *m[1xk]: K-dimensional mean vector
 *Output:
 *X[axm]: Generated sample from a Dir(a,m)
*/

MatDoub dirichletRnd(VecDoub a, VecDoub m){
  int i,j,k;
  k=a.size();
  MatDoub X(k,k);
  Doub sum;
  for(i=0;i<k;i++){
      a[i]=a[i]*m[i];
    for(j=0;j<k;j++){
      X[i][j]=rand()^a[i]*exp(-rand())/rand();
      sum+=X[i][j];
    }
  }
  for(i=0;i<k;i++){
    for(j=0;j<k;j++){
      X[i][j]/=sum;
    }
  }
  return X;
}
