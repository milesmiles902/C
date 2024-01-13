/*
 * @file mixGaussVbPred.cpp
 * @Description Predict label and responsibiliy for Gaussian mixture model trained by VB;
 * @Equations 10.64: E[(x-mu)*DEL*(x-mu)] = D/B+v(x-m)*W*(x-m)
 *            10.65: ln(DEL_k) = E[ln[DEL]]=sum(psi[(v+1-i)/2]+Dln(2)+ln[W]
 *            10.66: ln(pi_k) = E[ln(pi_k)]=psi(alpha_k)-alpha(alpha);
 *            10.46: ln rho_nk = E[ln(pi_k)]+0.5*E[ln[DEL_k]]-D/2*ln(2pi); 
 *            10.49: r_nk = rho_nk / sum (rho_nj)
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

Doub psi(int x, Doub alpha){
  int i;
  Doub coef,val;
  coef=pow(-1,x+1)*fact(x);
  for(i=0;i<1000;k++){
     val+=pow(1/(i+alpha),x+1)
  }
  return val*coef;
}

/*
 *Input:
 * X[dxn]: Data Matrix
 * Model; Trained model structure output by the EM algorithm
 *Output:
 * label[1xn]: Cluster label
 * R[kxn]: Responsibility
*/

void mixGaussVbPred(MatDoub X, Model::mixGaussVb model, VecDoub &label, MatDoub &R){
  int i,j,k,m=X.nrows();
  Doub sumalpha;
  MatDoub alpha(m,m),kappa(m,m),m(m,m),v(m,m),U(m,m),logW(m,m),EQ(m,m,0),Q(m,m),QQ(m,m),Eloglambda(m,m),Elogpi(m,m),logRho(m,m),LogR(m,m),R(m,m);
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      Q[i][j]=U[j][i]/(X[i][j]-m[i][j]);
    }
  }
  for(i=0;i<m;i++){  
    for(j=0;j<m;j++){
      for(k=0;k<m;k++){
        QQ[i][j]+=Q[j][k]*Q[k][j];  
      }
    }
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      EQ[i][j]=m/kappa[i][j]+v[i][j]*QQ[i][j]; //10.64
    }
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      Eloglambda[i][j]+=psi(0,0.5*(v[i][j]+1]-m))+m*log(2)+logW[i][j];  
      sumalpha+=alpha[i][j];
    }
  }  
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      Elogpi[i][j]+=psi(0,alpha[i][j])-psi(0,sumalpha);
      logRho[i][j]=-0.5*(EQ[i][j]-(ElogLambda[i][j]-m*log(2*pi));
    }
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      logRho[i][j]=logRho[i][j]+Elogpi[i][j];
    }
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      logsumexp+=exp(logRho[i][j]);
    }
  }
  logsumexp=log(logsumexp);
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      logR[i][j]=logRho[i][j]-logsumexp;
      R[i][j]=exp(logR[i][j]);
    }
  } 
}

