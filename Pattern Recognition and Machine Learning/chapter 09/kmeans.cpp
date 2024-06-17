/*
 * @file kmeans.cpp
 * @Description Perform kmeans clustering
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * m: Initializer
 *Output:
 * label[1xn]: Sample labels
 * mu[dxk]: Center of clusters
 * energy: Optimization target value
*/

void kmeans(MatDoub X, VecDoub &label, MatDoub &mu, int energy){
  int i,j,k,d,n;
  d=X.nrows();
  n=X.ncols();
  VecDoub label(n),idx(n),last(n,0),mu(n),val(n);
  Doub minmu=0;
  for(i=0;i<n;i++){
    last[i]=label[i];
    for(j=0;j<d;j++){
      mu[i]=X[i][j]/(d*n);
    }
  }
  for(i=0;i<d;i++){
   for(j=0;j<n;j++){
     for(k=0;k<d;k++){
       dotmu[i][j]+=mu[k][i]*mu[i][k];
     }
   }
  }
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      if(minmu<dotmu[i][j]) val[i]=dotmu[i][j]/2-mu[i]*X[i][j];  
    }
  }
  for(i=0;i<d;i++){
    sumval+=val[i];
  }  
  for(i=0;j<n;j++){
    for(j=0;j<n;j++){
      for(k=0;k<d;k++){
        energy+=X[k][i]*X[i][k]+2*sum(val);
      }
    }
  }
}
