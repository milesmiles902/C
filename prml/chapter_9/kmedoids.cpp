/*
 * @file kmedoids.cpp
 * @Description Perform k-medoids clustering
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * init[1xn]: K-number of clusters or labels
 *Output:
 * label[1xn]: Sample Labels
 * index: Location of medoids
 * energy: Optimization target value
*/

void kmedoids(MatDoub X, VecDoub init, VecDoub &label, int &index, int &energy){
  int i,j,k,d,n;
  d=X.nrows();
  n=X.ncols();
  MatDoub v(d,d);
  VecDoub mu(n),minD(n);
  Doub min;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      mu[j]+=X[i][j]/n;; 
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]-=mu[j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        v[i][j]+=X[i][k]*X[j][k]; 
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;k<d;j++){
      D[i][j]=v[i][j]+v[j][i]-2*X[i][j]*X[j][i];
    }
  }
  for(i=0;i<label.size();i++){
    if(label[i]){
      for(j=0;j<n;j++){
        min=D[i][j];
        if(min<minD[i]){
          minD[i]=min;
        }
      }
    }
  }
  for(i=0;i<n;i++){
    energy+=minD[i];
  } 
}
