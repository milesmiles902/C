/*
 * @file mixGaussEvidence.cpp
 * @Description Variational lower bound of the model evidence( log of marginal likelihood)
 * This function implements the method in the book Patterns and Recognition with Machine Learning. It is equivalent
 * to mixGaussVb function.
 * @Eqns #10.51: Nk=sum(r_nk);
 *       #10.52: xbar=sum(r_nk*x_n)/Nk
 *       #10.56: lnq(x)=(alpha0-1)sum(ln(x_k))+sum(sum(r_nk*ln(x_k))+const
 */

#include "nr3.h"
#include "cholesky.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 *prior: Structure containing prior values (alpha,kappa,m,v,M);
 *mode: Structure containing model values (alpha,kappa,m,v,U,R,logR);
 *Output:
 *
*/


Doub psi(int x, Doub alpha){
  int i;
  Doub coef,val;
  coef=pow(-1,x+1)*fact(x);
  for(i=0;i<1000;k++){
     val+=pow(1/(i+alpha),x+1)
  }
  return val*coef;
}


void mixGaussEvidence(mixGaussEvidence prior, mixGaussEvidence model, int lambda){
  int h,i,j,k,l,d;
  d=(model.U).nrows();
  k=(model.U).ncols();
  MatDoub U(d,k),U0(d,k),R(d,k),logR(d,k),Eqz(d,k),kappa(d,k),kappa0(d,k),m(d,k),m0(d,k),v0(d,k),v(d,k),logCalpha0(d,k),M0(d,k),sqrtR(d,k),Xs(d,k),V(d,d),Q(d,d),trSW(d,d);
  VecDoub nk(d),alpha(d),alpha0(d),Elogpi(d),Eqpi(d,n),logW(k,0),trSW(k,0),trM0W(k,0),xbarmWxbarm(k,0),mm0Wmm0(k,0),logW(d);
  Doub Epi,sumalpha,sumElogpi,Epz,sumlogUi;
  alpha0=prior.alpha;
  kappa0=prior.kappa;
  m0=prior.m;
  v0=prior.v;
  M0=prior.M;
  
  alpha=model.alpha;
  kappa=model.kappa;
  m=model.m;
  v=model.v;
  U=model.U;
  R=model.R;
  logR=model.logR;
  
  for(i=0;i<d;i++){
    for(j=0;j<k;j++){
      nk[i]+=R[i][k];
    }
    sumalpha+=alpha[i];
  }
  for(i=0;i<d;i++){
    Elogpi[i]=psi(0,alpha[i])-psi(0,sumalpha);
    Epz+=nk[i]*Elogpi[i];
    sumElogpi+=Elogpi[i];
  } 
  
  for(i=0;i<d;i++){
    for(j=0;j<k;j++){
      for(h=0;h<k;h++){
        Eqz[i][j]+=R[j][h]*logR[h][j];
      }
    }
  } 
  for(i=0;i<d;i++){
    for(j=0;j<k;j++){
      logCalpha0[i][j]=lgamma(k*alpha0[i][j])-k*lgamma(alpha[i][j]);
    }
  }
  for(i=0;i<d;i++){
    Eppi[i]=logCalpha0+(alpha0[i]-1)*sumElogpi;
    logCalpha[i]=lgamma(k*alpha0[i])-k*lgamma(alpha0[i]);
    Eqpi[i]+=(alpha[i]-1)*Elogpi[i]+logCalpha[i];
  }
  
  cholesky(M0);
  
  U0=M0;
  
  for(i=0;i<d;i++){
    for(j=0;j<k;j++){
      sqrtR[i][j]=sqrt(R[i][j]);
      for(h=0;h<k;h++){
        xbar[i]+=X[j][h]*R[h][j]/nk[i];
      }
    }
  }
  for(i=0;i<l;i++){
    Mat3DDoub Ui(d,k,i,0);  
    for(j=0;j<d;j++){
      for(h=0;j<k;h++){ 
        for(l=0;l<i;l++){
          if(l=0){
            Ui[j][h][l]=U[j][h];
          }
          if(j=h){
            if(h=l){
              sumlogUi+=-2*logUi[j][h][l];
            }
          }
        }
      }
    }
    for(j=0;j<d;j++){
      logW[j]=sumlogUi;
    } 
    for(j=0;j<d;j++){
      for(h=0;h<n;h++){
        Xs[j][h]=(X[j][h]-xbar[j])*sqrtR[h][j];
      }
    }
    for(j=0;j<d;j++){
      for(h=0;h<k;h++){
        for(l=0;l<d;l++){
          V[j][h]=Xs[h][l]*Xs[l][h]/nk[j];
        }
      }
    }
    cholesky(V);
    for(j=0;j<d;j++){
      for(h=0;h<k;h++){
        Q[j][h]=V[j][h]/Ui[j][h][i];
      }
    }
    for(j=0;j<k;j++){
      for(h=0;h<k;h++){
        for(l=0;l<k;l++){
          trSW[j][h]=Q[h][l]*Q[l][h];
        }
      }
    }
    //Inconsisten matrix dimensions from original in Matlab
  }
   
}

