/*
 * @file .cpp
 * @brief Linear Regression
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "nr3.h"
#include "cholesky.h"

void linReg(MatDoub X, VecDoub t){
  Int d,n,i,j,k;
  Doub Xmean,tmean,var,beta,w0;
  d=X.nrows();
  n=X.ncols();
  MatDoub Xdif(d,n),XX(d,d),w(d,d);
  VecDoub tdif(n);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      Xmean+=X[i][j];
    }
    tmean+=t[i];
  }
  Xmean=Xmean/(d*n);
  tmean=tmean/d;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      Xdif[i][j]=X[i][j]-Xmean;
    }
    tdif[i]=t[i]-tmean;
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        XX[i][j]+=X[i][k]*X[j][k];
      }
    }
  }

  Cholesky myCholesky(XX);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      w[i][j]=XX[i][j]/(XX[j][i]/(Xdif[i][j]*tdif[i]));
    }
  }
  w0=tmean;
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      w0-=w[i][j]*Xmean;
    }
  }

  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      var+=(t[i]-w[i][j]*X[j][i]);
    } 
  } 
  var=var/d;
  beta=1/pow(var,2);
  std::cout << "Model components: " << std::endl;
  std::cout << "-Weights: " << std::endl;
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      std::cout << w[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "-Initial Weight: " << std::endl;
  std::cout << w0 << " " << std::endl;
  std::cout << "Data mean: " << std::endl;
  std::cout << Xmean << " " << std::endl;
  std::cout << "Precision: " << std::endl;
  std::cout << beta << " " << std::endl;
  std::cout << "Data: " << std::endl;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      std::cout << XX[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Model: ";
  for(i=0;i<d;i++){
    std::cout << t[i] << std::endl;
  }
}

Int main(){
  Int d=2,n=2,i,j;
  MatDoub X(d,n);
  VecDoub t(n);
  for (i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%5;
    }
    t[i]=rand()%5;
  }
  linReg(X,t);
}
