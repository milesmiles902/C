/*
 * @file .cpp
 * @brief Compute linear classification model y=U'*x;
 * @Eqns: 4.43-4.45
 */

#include "nr3.h"
#include "makeplot.h"
#include <cmath>
#include <iostream>

/*
 * Fisher (linear) discriminant analysis
 * Input:
 *   X: Data Matrix [dxn]
 *   t: Class label [1xn]
 *   d: Target Dimension
 * Output:
 *   U: Projection Matrix [dxn]
 */
void fda(MatDoub X, VecDoub t, Int n, Int d){
  Int i,j,k,xmean, maxT=0;
  MatDoub xbar(d,n), St(d,d), m(d,d), m0(d,d), Sb(d,d);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      mean+=X[i][j]
    }
  }
  xmean/=(d*n);  
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
    xbar[i][j]=X[i][j]-mean;
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        St[i][j]=xbar[i][k]*xbar[j][k]/n;
      }
    }
  }
  
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      m[i][j]=X[i][j]/(n);
    }
  }
  
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
        m0[i][j]=m[i][j]-mean;
      }
    }
  
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        Sb[i][j]=n*m0[i][k]*m0[j][k];
      }
    }
  }

  *Look at Eigenvalues **Later**
  
}
int main(){
  Int i,j,n,d=3;
  n=3;
  MatDoub X(d,n);
  VecDoub t(1,n);
  
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%5;
      t[j]=rand()%4;
    }
  }
  fda(X,t,n,d);
}
