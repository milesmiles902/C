/*
 * @file kalmanFilter.cpp
 * @Description Kalman filter (forward algorithm for linear dynamic systems)
 * @Eqns #13.97: K=VC/(CVC+sigma)
 *       #13.94: mu=mu0+K(x-Cmu0)
 *       #13.95: V = (I-KC)V0
 *       #13.88: P = AVA+Gamma 
 *       #13.92: K = PC/(CPC+sigma)
 *       #13.89: mu = Amu+K(x-CAmu)
 *       #13.90: V = (I-KC)P
 *       #13.91: c = N(x|CAmu, CPC+sigma)
 */

#include "nr3.h"
#include "inverse.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * model: Model Structure
 *Output:
 * mu[qxn]: Matrix of latent mean mu=E[z]
 * V[qxqxn]: Latent covariance U=cov[z]
 * llh: Loglikelihood
*/

void forwardUpdate(Matdoub x, VecDoub &mu, MatDoub &V, MatDoub A, MatDoub G, MatDoub C, MatDoub S, ,Doub &llh){
  int i,j,k,d=X.nrows();n=X.ncols();
  MatDoub P(d,d),PC(d,d),R(d,d),K(d,d),Amu(d,d),CAmu(d,d),mu(d,d);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        P[i][j]+=A[j][k]*V[k][j]*A[k][j];
      }
      P[i][j]+=G[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        PC[i][j]+=P[j][k]*C[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;j<n;j++){
        R[i][j]+=C[j][k]*PC[k][j];
      }
      R[i][j]+=S[i][j];
    }
  }
  invR=r;
  inverse(R);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        K[i][j]+=PC[j][k]*invR[k][j];
        Amu[i][j]+=A[j][k]*mu[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        CAmu[i][j]+=C[j][k]*C[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      xCAmu[i][j]=x[i][j]-CAmu[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k+){
        mu[i][j]+=K[j][k]*xCAmu[k][j];
        KC[i][j]-=K[j][k]*C[k][j];
      }
      mu[i][j]+=Amu[i][j];
      KC[i][j]+=1;
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        V[i][j]+=KC[j][k]*P[k][j];
      }
    }
  }
  llh=logGauss(x,CAmu,R);
}

void kalmanFilter(MatDoub X, ldsModel model, MatDoub &mu, MatDoub &V, Doub llh){
  int i,j,k,l,d=X.nrows(),n=X.ncols();
  MatDoub PC(d,d),R(d,d),K(d,d),invR(d,d),A(d,d)=model.A, G(d,d)=model.G, C(d,d)=model.C, S(d,d)=model.S,mu(d,n,0),V(k,k),Cmu0(d,d),KC(d,d);
  VecDoub llh(n),mu0(d)=model.mu0;
  Doub P=model.P0;
  
  MatDoub3D V(d,d,n);
  
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        PC[i][j]+=P[j][k]*C[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        R[i][j]+=C[j][k]*PC[k][j];
      }
      R[i][j]+=S[i][j];
    }
  }
  invR=R;
  inverse(invR);  
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        K[i][j]+=PC[j][k]*invR[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        Cmu0[i][j]+=C[j][k]*mu0[k][j];
        KC[i][j]+=K[j][k]*C[k][j];
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        mu[i][j]+=K[j][k]*(X[k][j]-Cmu0[k][j]);
        V[i][j][k]=(1-KC[j][k])*P[k][j];
      }
      mu[i][j]+=mu0[i][j];
    }
  }
  llh[0]=logGauss(X,Cmu0,R);
  for(i=1;i<n;i++){
    forwardUpdate(X, &mu, &V, A, G, C, S, &llh);
  } 
}


