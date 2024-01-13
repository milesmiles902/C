/*
 * @file kmeansPred.cpp
 * @Description Prediction for kmeans clustering
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 *model[dxk]: Cluster Center Matrix
 *X[dxn]: Testing Data
 *Output:
 *label[1xn]: Cluster Label
 *energy: Optimization target value
*/

void kmeansPred(kmeans model, MatDoub X){
  Int i,j,l,d,k,n;
  d=X.nrows();
  k=mu.ncols();
  n=X.ncols();
  MatDoub dotmu(d,d),dotX(d,d);
  VecDoub val(d);
  Doub energy,minVal=0;

  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      for(l=0;l<d;l++){
        dotmu[i][j]=mu[l][j]*mu[j][l];
      }
    }
    for(j=0;j<k;j++){
      for(l=0;l<d;l++){
        dotX[i][j]=X[l][k]*X[k][l];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      val[i]=dotX[i][j]+dotmu[i][j]-2*mu[i][j]*X[i][j];
      if(minVal<val[i]) {
        minVal=val[i];
        label[i]=minVal;
      }
    }
  }
  for(i=0;i<d;i++){
    energy+=val[j];
  }
}
