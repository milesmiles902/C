/*
 * @file .cpp
 * @Description knReg
 * Equation #6.62: C(xn,xm)=k(xn,xm)+delta/beta
 * Equation #6.68: m(xn+1)=sum(a_n*k(xn,xn+1));
 * Equation #3.21: 1/beta=(sum(t-w*phi(x))^2)/N
 * Equation #3.55: ln(p(w|t))=-beta/2*sum(t-w*phi(x))^2 - alpha/2*w^2;
 */

#include <csmath>
#include <iostream>
#include "nr3.h"
#include "knCenter.cpp"
#include "KnGauss.cpp"

/*
 *Input:
 * X[mxn]: Data Matrix
 * t[n]: Response
 * lambda: Regularization Parameter
 *Output:
 * K[nxn]: Trained Matrix
*/

void knReg(MatDoub X, VecDoub t, int lambda){
  int i,j,nrow,ncol;
  nrow=X.nrows();
  ncol=X.ncols();
  MatDoub K(nrow,ncol),U(nrow,ncol),A(nrow,ncol);
  Doub tbar;
  
  K=knCenter(KnGauss(),X);
  for(i=0;i<t.size();i++){
    tbar+=t[i];
  }
  tbar/=t.size();
  for(i=0;i<nrow;i++){
    for(j=0;j<ncol;j++){
    U[i][j]=K[i][j]+lambda;
    }
  }
  Cholesky myCholesky(U);

  for(i=0;i<nrow;i++){
    for(j=0;j<ncol;j++){
      a[i][j]=U[i][j]*(U[j][i]/(t(i)-tbar));
    }
  }
}

int main(){
  Int i,j,n,m,lambda;
  n=3;
  m=3;;
  MatDoub X(m,n);
  VecDoub t(n);
  
  lambda=5;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
    t[i]=rand()%10;
  } 
  knReg(X,t,lambda);
}
