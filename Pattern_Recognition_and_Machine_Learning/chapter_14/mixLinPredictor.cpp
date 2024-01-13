/*
 * @file mixLinpred.cpp
 * @Description Prediction function for a mixture of linear regression
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * model: Trained model Structure
 * X[dxn]: Data Matrix
 * t[1xn]: Responding vector
 *Output:
 * y[1xn]: Prediction
 * z[1xn]: Cluster Label
 * p[1xn]: Predict Probability for t
*/

void mixLinPred(MatDoub X, VecDoub t, Vecdoub &y, VecDoub &z, VecDoub &p){
  int i,j,k,d=X.nrows(),n=X.ncols();
  MatDoub alpha(d,n),beta(d,n);
  VecDoub W(d),D(d),logRho(d),T(d),p(d),logR(d),R(d),z(d),sumexp(d);
  W=model.W;
  alpha=model.alpha;
  beta=model.beta;
  
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]+=1;
      y[i]+=W[i]*X[i][j];
    }
    logRho[i]=-0.5*beta[i]*pow(y[i]-t[i],2)+log(alpha[i]);
    sumexp+=exp(logRho[i]);
  }
  T=log(sumexp);
  p=sumexp;
  for(i=0;i<d;i++){
    logR[i]=logRho[i]-T;
  }
  z=exp(logR);
}


