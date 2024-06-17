/*
 * @file adaboostBinPred.cpp
 * @Description Prediction of binary Adaboost
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * model: Trained Model Structure
 * X[dxn]: Data Matrix
 *Output:
 * t[1xn]: Prediction
*/

void adaboostBinpred(adaboost model, MatDoub X, VecDoub &t){
  int i,j,d=X.nrows(),n=X.ncols();
  MatDoub Alpha = model.alpha;
  MatDoub Theta = model.theta;
  MatDoub c(d,d);
  int M=Alpha.nrows();
  for(M=0;M<d;i++){
    for(i=0;i<d;i++){
      for(j=0;j<n;j++){
        c=model.Theta[i][j][M];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<n;j++){
        y[i]+=pow(c[i][j],2)-pow(X[i][j],2);
      }
    }
    for(i=0;i<d;i++){
      t[i]=t[i]+Alpha[M]*y[i];
    }
  }
}

