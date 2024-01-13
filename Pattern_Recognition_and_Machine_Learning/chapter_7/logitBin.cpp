/*
 * @file .cpp
 * @description Logisitic regression for binary classification optimized by Newton-Raphson method.
 * @Eqn: 4.87-4.92
 */

#include "nr3.h"
#include "psplot.h"
#include <cmath>

void logitBin(MatDoub &X, VecDoub &y, int &lambda, int &alpha){
  Int t,i,j,k,m,n;
  Doub tol,epoch,sum,ay;
  m=X.nrows();
  n=X.ncols();
  VecDoub a(n),w(n),ww(n),z(n),r(n),llh(200);
  MatDoub g(m,n), Xw(m,n), H(m,m);

  tol=1e-4;
  epoch=200;
  
  for(i=0;i<n;i++)
    w[i]=rand()%10;

  for(i=0;i<epoch;i++)
    llh[i]=0;

  for(t=1;t<epoch;t++){
    for(i=0;i<m;i++){
      for(j=0;j<n;j++){
        a[j]=w[j]*X[i][j];    
        ww[i]+=w[j]*w[j];
        ay+=a[j]*y[j];
        sum+=log(1+exp(a[j]))-0.5*lambda*ww[j];
      }
    }
    llh[t]=(ay-sum)/n;
    if (abs(llh[t]-llh[t-1])<tol) return;
  
    for(i=0;i<n;i++)
      z[i]=1/(1+exp(-a[i]));
     
    for(i=0;i<m;i++){
      for(j=0;j<n;j++){
        g[i][j]=X[i][j]*(z[i]-y[i])+lambda*w[i];   
      }
      r[i]=z[i]*(1-z[i]);
    }
    
    for(i=0;i<m;i++){
      for(j=0;j<n;j++){
        Xw[i][j]=X[i][j]*sqrt(r[i]);
      }
    }
    
    for(i=0;i<m;i++){
      for(j=0;j<m;j++){
        for(k=0;k<n;k++){
          H[i][j]=Xw[i][k]*Xw[j][k]+lambda;
        }
      }
    }
    for(i=0;i<n;i++){
      for(j=0;j<m;j++){
        w[i]=w[i]-alpha*H[i][j]/g[i][j];
      }
    }
  }
  /*Test Output*/
  /**************
  std::cout << "X: " << std::endl;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      std::cout << X[i][j] << " ";
    } std::cout << std::endl;
  }
  std::cout << "Y: " << std::endl;
  for(i=0;i<n;i++)
    std::cout << y[i] << " " << std::endl;
  std::cout << "w: " << std::endl;
  for(i=0;i<n;i++)
    std::cout << w[i] << " " << std::endl;
  *****************/
  return 
}

int main(){
  int i,j,d,n,lambda,alpha;
  d=5; n=5;
  MatDoub X(d,n);
  VecDoub y(n);

  lambda=1;
  alpha=1;   

  for(i=0;i<d;i++) {
    for(j=0;j<n;j++){ 
      X[i][j]=rand()%20;
    }
    y[i]=0;
  }
  logitBin(X,y,lambda,alpha);
}
