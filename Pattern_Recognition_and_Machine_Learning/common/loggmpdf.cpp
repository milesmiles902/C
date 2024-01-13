/*
 * @file loggmpdf.cpp
 * @Description Compute log pdf of a Gaussian mixture model
 */

#include "nr3.h"
#include "cholesky.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxd]: Input data
 * model: Parameters of a Gaussian
 *Output:
 * r: log(N(x|mu,sig^2)
*/

void loggausspdf(MatDoub X, Doub mu, MatDoub sigma,MatDoub &y){
  int i,j,k,d=X.nrows();
  MatDoub Q(d,d),q(d,d),c(d,d),y(d,d);
  Doub c;
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      X[i][j]-=mu;
    }
  }
  cholesky(sigma);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      Q[i][j]=sigma[i][j]/X[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        q[i][j]+=Q[j][k]*Q[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    c+=log(sigma[i][i]);
  }
  c+=d*log(2*pi)+2*c;
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      y[i][j]=-(c+q[i][j])/2;
    }
  }
}

void loggmpdf(MatDoub X, GaussModel model, Doub r){
  int i,j,k,d=X.nrows();
  MatDoub logRho(d,d),y(d,d),sig(d,d),w(d,d)=model.weight;
  MatDoub3D sigma(d,d,d)=model.sigma;
  Doub mu=model.mu;
  
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        sig(d,d)=sigma(j,k,i);
      }
      logRho[i][j]=loggausspdf(X,mu,sig,y);
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      logRho[i][j]+=log(w[i][j]);
    }
  }
  r=logsumexp(logRho);
  
}

