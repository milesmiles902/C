/*
 * @file kseeds.cpp
 * @Description Perform kmeans++ seeding
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data matrix
 * k: Number of seeds
 *Output:
 * mu[dxn]: Seeds
*/

void kseeds(MatDoub X, int k){
  int i,j,d,n;
  n=X.ncols();
  MatDoub mu(d,k);
  VecDoub D(n),sum(n);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      mu[i][j]=X[i][j]*rand();
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      sum[i]+=pow((X[i][j]-mu[i][j]),2)
    }
  }
  for(i=1;i<d;i++){
    if(D[j]>sum[j]) D[j]=sum[j];
    for(j=0;j<n;j++){
      mu[i][j]=D[i][j]*rand()
    }    
  }
}
