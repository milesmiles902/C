/*
 * @file .cpp
 * @brief Computer log pdf of a Student's t-distribution
 */

#include <cmath>
#include <iostream>
#include "nr3.h"
#include "cholesky.h"

using namespace std;
Doub dotProduct(MatDoub Q){
  int i,j,result;
  for(i=0;i<Q.nrows();i++){
    for(j=0;j<Q.ncols();j++){
      result+=Q[i][j]*Q[j][i];
    }
  }
  return result;
}

Doub logSt(MatDoub X, int mu, int, sigma, int v, Doub &y){
  int i,j,k,o,c,row,col,sumr;
  d,k=mu.size();
  row=X.nrows();
  col=X.ncols();
  MatDoub Q(row,col), q(row,col);

  if(sigma.size()==row && sigma.size()==row && k==1){
    R,p=chol(sigma);
    for(i=0;i<row;i++){
      for(j=0;j<col;j++){
        X[i][j]=X[i][j]-mu;
        Q[i][j]=R[i][j]/X[i][j];
      }
    }
    q=dotProduct(Q);
    o=-log(1+q/v)*((v+d)/2);
    for(i=0;i<row;i++){
      sumr+=log(R[i][i]);
    }
    c=lgamma((v+d)/2)-lgamma(v/2)-(d*log(v*M_PI)+2*sumr)/2;
    y=o+c;
  } else if(sigma.size()==X.nrows() && sigma.size()==k){
      int o,c;
      Doub lambda = 1.0/sigma;
      Doub ml = mu*lambda;
      MatDoub q(row,col);
      for(i=0;i<row;i++){
        for(j=0;j<col;j++){
          q[i][j]=(X[i][j]^2)*lambda-2*X[i][j]*ml+dotProduct(mu,ml);
          o[i][j]=log(1+q[i][j]*1/v)*-(v+d)/2;
          c[i][j]=lgamma((v+d)/2)-lgamma(v/2)-(d*log(M_PI*v)+sum(log(sigma)))/2;
          y[i][j]=o[i][j]+c[i][j];
        }
      }
  } else if(sigma.size()==1 && sigma.size()==k){
      int X2;
      MatDoub D(row,col),q(row,col),o(row,col),c(row,col);
      X2=dotProduct(X,X);
      for(i=0;i<row;i++){
        for(j=0;j<col;j++){
          D[i][j]=X2-2*X[i][j]*mu+dotProduct(mu,mu);
          q[i][j]=D[i][j]/sigma;
          o[i][j]=log(1+q[i][j]/v)*-(v+d)/2;
          c[i][j]=lgamma((v+d)/2)-lgamma(v/2)-d*log(M_PI*v*sigma)/2;
          y[i][j]=o[i][j]*c[i][j];
          /*Am I returning a probability or matrix?"*/
        }
      }
  } else { throw("Parameters are mismatched")};
}

void main(){
  MatDoub X(2,2);
  int mu,sigma,v,i,j;
  Doub y;
  
  for (i=0;i<X.nrows();i++){
    for(j=0;j<X.ncols();j++){
      X[i][j]=rand();
      mu+=X[i][j];
    }
  }
  mu=0;
  v=4;
  sigma=v/(v-2);
  logSt(X,mu,sigma,v,y);

  cout << "Probablity density of log(Student t-dist)" << y << endl;
}
