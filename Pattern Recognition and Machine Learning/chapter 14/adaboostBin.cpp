/*
 * @file adaboostBin.cpp
 * @Description Adaboost for binary classification (weak learner: kmeans)
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * t[1xn]: Label (0/1)
 *Output:
 * model: Trained Model
*/

void adaboostBin(MatDoub X, VecDoub t, adaboostModel &model){
  int i,j,k,m,M=100,d=X.nrows(),n=X.ncols();
  Doub sumw;
  VecDoub w(n,1/n), Alpha(M,0),sumE(d),y(d);
  MatDoub T(d,d),E(d,d),c(d,d),e(d,d),w(d,d),cX(d,d),I(d,d);
  MatDoub3D Theta(d,d,M,0);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      Theta[i][j]=i;
      T[i][j]=i;
    }
    Alpha[i]=i;
  }
  for(m=0;m<M;i++){
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        if(w[i][j]>0){
          for(k=0;k<d;k++){
            E[i][j]+=w[j][k]*T[k][j];
          }
        } 
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        sumE[i]+=1/E[i][j];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){ 
        if(1/E[i][j]>0){
          for(k=0;k<d;k++){
            E[i][j]+=E[j][k]*sumE[i];
          }
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;k+){
          c[i][j]+=X[j][k]*e[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;k++){
          y[i]+=pow(c[j][k],2)-pow(X[k][j],2);
        }
      }
      y[i]=sqrt(y[i]);
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        Theta[i][j][m]=c[i][j];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        if(y!=t){
          I[i][j]=1;
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;j<d;k++){
          e[i][j]+=w[j][k]*I[k][j];
        }
      }
    }    
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        alpha[i][j]=log((1-e[i][j])/e[i][j])
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        w[i][j]=w[i][j]*pow(e,alpha[i][j]);
        sumw+=w[i][j];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        w[i][j]/=sumw;
      }
    }
    Alpha[m]=alpha; 
  }
  model.alpha=Alpha;
  model.theta=Theta;
}

