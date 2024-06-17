/*
 * @file rvmBinPred.cpp
 * @Description Predict the label for a binary logistic regression model
 */

#include "nr3.h"
#include <csmath>
#include <iostream>


/*
 *Input:
 * X[dxn]: Testing Data
 *Output:
 * y[1xn]: Predict Label (0/1)
 * p[1xn]: Predict Probability [0,1]
*/

int main(){
  Int i,j,n,m;
  n=3;
  m=3;
  MatDoub X(m,n),w(m,n);
  VecDoub y(n),p(n);
  
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=1;
      w[i][j]=rand()%5;
    }
  } 
  rvmBinPred
  //How is this returning a model???
  rvmBinFp(MatDoub X, VecDoub t, int alpha)

  for(i=0;i<n;i++){
    p[i]=sigmoid(w[i][j])
  }
  y=p;
}
