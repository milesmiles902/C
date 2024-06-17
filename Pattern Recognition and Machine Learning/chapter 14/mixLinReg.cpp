le mixLinReg.cpp
 * @Description Mixture of Linear Regression
 *  */

#include "nr3.h"
#include "cholesky.h"
#include <csmath>
#include <iostream>
#include <random>


/*
 *Input:
 * X[dxn]: Data Matrix
 * y[1xn]: Responding Vecor
 * k: Number of Mixture Components
 * Lambda: Regularization Parameter
 *Output:
 * Label[1xn]: Cluster Label
 * Model: Trained Model Structure
 * llh: Loglikelihood
 */

void mixLinReg(MatDoub X, VecDoub y, int k, int lambda, VecDoub &label, mixLinReg &model, Doub &llh){
  int i,j,l,m,Lambda=lambda,d=X.nrows(),n=X.ncols(),maxiter=500;
  MatDoub R(d,n),W(d,n,0),Xy(d,n),alpha(d,d),Xw(d,d),U(d,d),D(d,d),logRho(d,d),T(d,d),logR(d,d),XwXw(d,d),XyR(d,d),Wx(d,d);
  VecDoub nk(d);
  Doub tol=0.000001,
  for(i=0;i<d;i++){
    label[i]=rand();
    for(j=0;j<n;j++){
      X[i][j]+=1;
      R[i][j]=rand();
      Xy[i][j]=X[i][j]*y[i];
    }
    label[i]=rand();
  }
  beta=1;
  for(iter=2;iter<maxiter;iter++){
    for(i=0;i<d;i++){
      for(j=0;j<n;j++){
        nk[i]=R[j][i];
      }
      alpha=nk[i]/n;
    }
    for(l=0;l<k;l++){
      for(i=0;i<d;i++){
        for(j=0;j<n;j++){
          Xw[i][j]=X[i][j]*pow(R[l][j],0.5);
        }
      }
      for(i=0;i<d;i++){
        for(j=0;j<d;j++){
          for(k=0;k<n;k++){
            XwXw[i][j]+=Xw[j][k]*Xw[k][j];
          }
          XwXw[i][j]+=Lambda;
        }
      }
      U=cholesky(XwXw);
      for(i=0;i<d;i++){
        for(j=0;j<d;j++){
          for(k=0;k<n;k++){
           XyR[i][j]+=Xy[j][k]*R[k][j];
          }  
        }    
      }
      for(i=0;i<d;i++){
        for(j=0;j<d;j++){
          W[i][l]=U[i][j]/(U[j][i]/(XyR[l][i]);
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          Wx[i][j]+=W[j][k]*X[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        D[i][j]=pow(Wx[i][j]-y[i],2);
        logRho[i][j]=-0.5*beta[i][j]*D[i][j]+log(alpha[i][j]);
      }
    }  
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        T[i]+=exp(logRho[i][j]);
      }
      T[i]=log(T[i]);
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        logR[i][j]=logRho[i][j]-T[i];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        R[i][j]=exp(logR[i][j]);
      }
      llh[iter]+=T[i]/d;
    }
    if(abs(llh[iter]-llh[iter-1]) < tol*abs(llh[iter])) break;
  }
  model.alpha=alpha;
  model.beta=beta;
  model.W=W;
  model.label=label;
  
}
            
