/*
 * @file nbGaussPred.cpp
 * @Description Prediction of naive Bayes classifier with independent Gaussian
 */

#include "nr3.h"
#include "nbGauss.cpp"
#include <csmath>
#include <iostream>

/*
 *Input:
 * model: Trained model
 * X[dxn]: Data structure
 *Output:
 * y[1xn]: Predicted class label
*/

void nbGaussPred(fit model, MatDoub X, VecDoub &y){
  int i,j,m,n,c,d;
  m=X.nrows();
  n=X.ncols();
  MatDoub mu(m,n),var(m,n),ml(m,n),lambda(m,n),dotmuml(m,n),M(m,n);
  VecDoub y(n);
  Doub norm,w=model.var;
  mu=model.mu;
  var=model.var;
 
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      lambda[i][j]=1/var[i][j];
      norm[i][j]+=log(var[i][j]);
      ml[i][j]=mu[i][j]*lambda[i][j];
    }
  }
  norm=m*log(2*PI())+2*norm;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      for(k=0;k<n;k++){
        dotmuml[i][j]=mu[i][k]*ml[k][j];
      }
    }
  }
 
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      M[i][j]=lambda[j][i]*X[i][j]*X[i][j]-2*ml[j][i]+dotmuml[j][i];
      R[i][j]=-0.5*(M[i][j]+c);
    }
  }
  for(i=0;i<n;i++){
    y[i]=exp(R[i][j]*w);
  }
}
