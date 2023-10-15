/*
 * @file fa.cpp
 * @Description Perform EM algorithm for factor analysis model
 * @Eqns #12.66: E[z]=G*W*Psi(x-xbar) wheree G=1/(I+W*Psi*W);
 *       #12.67: E[z*z]=G+E[z]*E[z]
 *       #12.69: W=[sum(x-xbar)E[z]][sumE[z*z]]
 *       #12.70: Psi=diag{S-W/N*sum(E[z](x-xbar)}
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * m: Dimension of target space
 *Output:
 * W[dxm]: Weight Matrix
 * mu[dx1]: Mean Vector
 * psi[dx1]: Variance Vector
 * llh: loglikelihood;
*/

void fa(MatDoub X, VecDoub t, int lambda){

}

int main(){
  Int i,j,n,m,lamda;
  n=3;
  m=3;
  MatDoub X(m,n);
  VecDoub t(n);
  
  lambda=2;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
    t[i]=rand()%10;
  } 
  XXX(X,t,lambda);
}
