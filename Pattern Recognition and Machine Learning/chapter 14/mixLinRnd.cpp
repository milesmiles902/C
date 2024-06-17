/*
 * @file mixLinRnd.cpp
 * @Description Generate data from mixture of linear model
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * d: Dimension of Data
 * k: Number of Components
 * n: Number of Data
 *Output:
 * X[dxn]: Data Matrix
 * y[1xn]: Response Variable
 * W[d+1 x k]: Weight Matrix
*/

void mixLinRnd(int d, int k, int n, MatDoub &X, VecDoub &y, MatDoub &W){
  int i,j; 
  VecDoub y(n),z(n);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      W[i][j]+=rand();
    }
  }
  kmeansRnd(d,k,n,X,z);
  for(i=0;i<d;i++){
    for(j=0;j<d+1;j++){
      for(k=0;k<n;k++){
        if(k==z[i]){
          y[i]+=W[j][k]*X[j][k]+W[j][k];
        }
      }
    }
  }
}

