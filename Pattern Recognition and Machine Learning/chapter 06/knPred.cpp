/*
 * @file knPred.cpp
 * @Description Training prediction for Gaussian Regression Fit
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 *  Model[Input]: Trained Model Structure
 *  X[dxn]: Testing Data
 *  t[1xn]: Testing Response
 *Output:
 *  y[1xn]: Prediction
 *  sigma: Variance
 *  p[1xn]: Likelihood of T
*/

void knPred(Model fit, MatDoub Xt, VecDoub t){
  int i,j,k,row,col;
  row=Xt.nrows();
  col=Xt.ncols();
  MatDoub kn(row,col),a(row,col),X(row,col),Kt(row,col), U(row,col),XU(row,col),dotXU(row,row),p(row,row);
  kn=fit.kn;
  a=fit.a;
  X=fit.X;
  
  Doub tbar,alpha,beta;
  tbar=fit.tbar; 
  Kt=knCenter(kn,X,X,Xt);
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      y[i][j]=a[j][i]*Kt[i][j]+tbar;
    }
  }
  U=fit.U;
  for(i=0;i<row;i++){
    for(j=0;j<col;k++){
      XU[i][j]=U[j][i]/Kt[i][j];
    }
  }
 
  for(i=0;i<row;i++){
    for(j=0;j<row;j++){
      for(k=0;k<col;k++){
         dotXU[i][j]+=XU[j][k]*XU[k][j];
      }
    }
  }  
  for(i=0;i<row;i++)
    for(j=0;j<col;j++){
      sigma[i][j]=sqrt(1/fit.beta+(knCenter(kn,X,Xt)-XU[i][j])/fit.alpha);
    }
  }
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      p[i][j]=exp(-0.5*((t[i]-y[i][j])/sigma[i][j])^2+log(2*pi))-log(sigma[i][j]);
    }
  } 
}

