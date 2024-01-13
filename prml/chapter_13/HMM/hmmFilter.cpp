/*
 * @file hmmFilter.cpp
 * @Description HMM Forward Filtering Algorithm. The alpha returned by this function is normalized
 * @Eqn: #13.59: c*alpha(z)=p(x|z)*sum[alpha(z_n-1)*p(z_n|z_n-1)];
 */

#include "nr3.h"
#include "inverse.cpp"
#include <csmath>
#include <iostream>


/*
 *Input:
 * X[1xn]: Integer vector which is a sequence of observations
 * model: Model structure which contains
 *   model.s[kx1]: Start Probability Vector
 *   model.A[kxk]: Transition Matrix
 *   model.E[kxd]: Emission Matrix
 *Output:
 * alpha[kxn]: Matrix of posterior alpha
 * llh: loglikelihood
*/

void hmmFilter(VecDoub X, hmmModel model, MatDoub alpha, Doub llhlambda){
  int i,j,d=X.size();
  VecDoub llh(d),sMmean(d),AtalphaMean(d),s(d)=model.s;
  MatDoub M(d,d),Atalpha(d,d),AtalphaM(d,d),At(d,d),A(d,d)=model.A,E(d,d)=model.E;
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        M[i][j]+=E[j][k]*X[k][j];
      } 
    }
  }
  At=inverse(A); 
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
       sMmean[j]+=s[i][j]*M[i][j]; 
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      M[i][j]/=sMmean[i];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        Atalpha[i][j]+=At[j][k]*alpha[k][j]
      }
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<d;k++){
        AtalphaM[i][j]+=Atalpha[j][k]*M[k][j];
      }
      AtalphaMean[i]+=AtalphaM[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      AtalphaM[i][j]/=AtalphaMean[i];
      alpha[i][j]=AtAlphaM[i][j];
      llh[i]=AtalphaMean[i];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      if(llh[i]>0){
        llh+=log(llh[i]);
      }
    }
  }
}

