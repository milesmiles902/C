/*
 * @file .cpp
 * @Description Perform kernel kmeans clustering
 * Input:
 *   K(nxn): Data Matrix
 *   init: Number of clusters
 * Output:
 *   label(1xn): Sample Labels
 *   Model: Trained model Structure
 *   Energy: Optimization Target Value
 */

#include "nr3.h"
#include <iostream>
#include <cmath>
#include <stdlib>

void knKmeans(MatDoub X, int init){
  int i,j,k,xrow,xcol;
  xrow=X.nrows();
  xcol=X.ncols();
  MatDoub A(xrow,xcol),E(xrow,xcol);
  Doub min,ff,sum;

  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      A[i][j]=0;
      sum+=A[i][j];
    }
  }
 
  for(i=0;i<init;i++){
    for(j=0;j<xrow;j++){
      for(k=0;k<xcol;k++){
        E[i][j]=A[i][j]/sum; 
      }
    }
    min=0;
    for(j=0;j<xrow;j++){
      for(k=0;k<xcol;k++){
        XE[i][j]=E[j][i]*X[i][j]*E[i][j]-2*E[i][j]*X[i][j];
        if(XE[i][j]<min) { 
          min=XE[i][j];
          ff=j;
        }
        if(j=ff){
          A[i][j]=1;
        } else {
          A[i][j]=0;
        }
      } 
    }
  }  
}

void main(){
  int i,j,xrow,xcol,init;
  xrow=3;
  xcol=3;
  MatDoub x(xrow,xcol);
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      X[i][j]=rand()%5;
    }
  }
  knKmeans(X,init=4);
}
