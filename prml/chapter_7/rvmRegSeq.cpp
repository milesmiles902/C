/*
 * @file .cpp
 * @Description
 * @Eqns #22: S=phi*C^-1*phi; Q=phi*C^-1*t
 *       #7.104: q=alpha*Q/(alpha-S)
 *       #7.105: s=alpha*S/(alpha-S)
 *       #20: alpha=s^2/(q^2-s); q^2>s;
 *       #31b: k=(sigma+(talpha^-1-alpha)^-1)^-1
 *       #32  delta(L)=q^2/(S+[talpha^-1-alpha^-1]^]-1)-log{1+S[talpha^-1-alpha^-1]}
 *       #27  delta(L)=(q^2-S)/S+log(S/Q^2)
 *       #37  delta(L)=q^2/(S-alpha)-log(1-S/alpha)
 *       #33  tsigma=sigma-k*sigma*sigma^T
 *       #34  tmu=mu-k*mu*sigma
 *       #35  tS=S+k(beta*sigma*PHI*phi)^2
 *       #36  tQ=Q+k*mu(beta*sigma*PHI*phi)
 *       #28  tsigma=|sigma+beta^2*diag(sigma)*sigma*PHI*phi*phi^t*PHI*sigma      -beta^2*diag(sigma)*sigma*PHI*phi|
                     |-beta^2*diag(sigma)*(sigma*PHI*phi)^T                                 diag(sigma)            |
 *       #29  tmu=|mu-diag(mu)*beta*sigma*PHI*phi|
 *                |           diag(mu)           |
 *       #30  tS=S-diag(sigma)*(beta*PHI*diag(e))^2
 *       #38  tsigma=sigma-(1/diag(sigma()*sigma*sigma^t
 *       #39  tmu=mu-diag(mu)/diag(sigma)*sigma
 *       #40  tS=S+(1/sigma)(beta*sigma*PHI*phi)^2
 *       #41  tQ=Q+diag(mu)/diag(sigma)*(beta*sigma*PHI*phi)
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

struct form{
  int index;
  MatDoub w0;
  MatDoub w;
  MatDoub alpha;
  MatDoub beta;
}

/*
 *Input:
 * X[dxn]: Data
 * t[1xn]: Response
 *Output:
 * Model: Trained model Structure
 * llh: loglikelihood
*/

void rvmRegSeq(MatDoub X, VecDoub t, MatDoub &model){
  int i,j,xrow,xcol,maxiter,idllh,jdllh,iAct;
  xrow=X.nrow();
  xcol=X.ncol();
  MatDoub XX(xrow,xcol),Xt(xrow,1),S(xrow,xcol),Q(xrow,1),s(xrow,xcol),q(xrow,xcol),theta(xrow,xcol),iNew(xrow,xcol),alpha(xrow,xcol),beta(xrow,xcol),delta(xrow,xcol),dllh(xrow,xcol),alpha_(xrow,xcol),Sigma(xrow,xcol),v(xrow,xcol),mu(xrow,xcol),rowe(xrow,xcol);
  MatBool iUse(xrow,xcol),iAdd(xrow,xcol),iDel(xrow,xcol); 
  Doub tol,xbar,tbar,index,maxdllh,rowmu,diagSigma;

  maxiter=1000;
  tol=1*10^-4;
  maxdllh=0;
  VecDoub llh(maxiter),phi(xrow),rowphi(xrow),iAct(xcol),rowSigma(xrow);
  
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      xbar+=X[i][j];
    }
    tbar+=t[i];
  }
  xbar/=(xrow*xcol);
  tbar/=t.size();
  
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      X[i][j]-=xbar;
    } 
    t[i]-=tbar;
  }
  tbar=0;
  for(i=0;i<xrow;i++){
    tbar+=t[i];
  }
  tbar/=(xrow);
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
    alpha[i][j]=0;
    beta[i][j]=1/(tbar*tbar);
    Sigma[i][j]=0;
    mu[i][j]=0;
    phi[j]=0;
    }
    iAct[i]=0;
  }
  index=0;
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      for(k=0;k<xrow;k++){
        XX[i][j]+=X[i][j]*X[k][j];
      }
      Xt[i][1]+=X[i][j]*t[i];
    }
  }
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;k++){
      S[i][j]=beta*XX[i][j];
      Q[i][j]=beta*Xt[i][1];    
    }
  }
  for(iter=0;i<maxiter;iter++){
    for(i=0;i<xrow;i++){
      for(j=0;j<xrow;j++){
        s[i][j]=S[i][j];
        q[i][j]=Q[i][j];
        if(i==index){
          s[index][j]=alpha*S[index][j]/(alpha-S[index][j]);
          q[index][j]=alpha*Q[index][j]/(alpha-Q[index][j]);
        }
        theta[i][j]=q[i][j]*q[i][j]-s[i][j];
        if(theta[i][j]>0){
          iNew[i][j]=theta[i][j];
        }
        iUse[i][j]=false;
        iUse[index][j]=true;
        iUpd[i][j]=(iNew[i][j]&iUse[i][j]);
        if(iNew[i][j]==iUpd[i][j]){iAdd[i][j]=iNew[i][j]};
        if(iUse[i][j]==iUpd[i][j]){iDel[i][j]=iUse[i][j]};
        dllh[i][j]=0;
      }
    }
    for(i=0;i<xrow;i++){
      for(j=0;j<xcol;j++){
        if(dllh[i][j]>maxdllh){
          maxdllh=dllh[i][j];
          idllh=i;
          jdllh=j;
        }
        if(iUpd[i][j]==true){
          delta[i][j]=1/alpha[i][j]-1/(pow(s[i][j],2)/theta[i][j]);
          alpha[i][j]=pow(s[i][j],2)/theta[i][j];
          dllh[i][j]=Q[i][j]*Q[i][j]*delta[i][j]/(S[i][j]*delta[i][j]+1)-log(S[i][j]*delta[i][j]);
          iAct=1;
        }
        if(iAdd[i][j]==true){
          dllh[i][j]=(Q[i][j]*Q[i][j]-S[i][j])/S[i][j]+log(S[i][j]/(Q[i][j]*Q[i][j]));
          iAct=2;
        }
        if(iDel[i][j]==true){
          dllh[i][j]=Q[i][j]*Q[i][j]/(S[i][j]-alpha[i][j])-log(-S[i][j]/alpha[i][j]);
          iAct=3;
      }
    }
    llh[iter]=maxdllh;
    if(llh[iter]<tol) { break;}
    
    switch(iAct){
      case 1:
        rowmu=mu[idllh][jdllh];
        for(i=0;i<xrow;i++){
          for(j=0;j<xcol;j++){
            alpha_=s[idllh][jdllh]*s[idllh][jdllh]/theta[idllh][jdllh];
            rowSigma[j]=Sigma[i][jdllh];
            diagSigma=Sigma[idllh][jdllh];
            kappa[i][j]=1/(diagSigma+1/(alpha_-alpha[idllh][jdllh];
            Sigma[i][j]=Sigma[i][j]-kappa[i][j]*(rowSigma[j]*rowSigma[j]);
            v[i][j]=beta[i][j]*X[i][j]*(phi[j]*rowSigma[j]);
            S[i][j]=S[i][j]+kappa[i][j]*v[i][j]*v[i][j];
            Q[i][j]=Q[i][j]+kappa[i][j]*rowmu[j]*v[i][j];
            alpha[i][j]=alpha_;
          }
        }
        break;
      case 2:
        for(i=0;i<xrow;i++){ 
          for(j=0;j<xcol;j++){
            alpha_=s[idllh][jdllh]*s[idllh][jdllh]/theta[idllh][jdllh];
            diagSigma=1/(alpha_+S[idllh][jdllh]);
            rowmu=diagSigma*Q[idllh][jdllh]; 
            rowphi[j]=X[idllh][j];
            v[i][j]=beta[i][j]*Sigma[i][j]*(phi[j]*rowphi[j]);
            off=-diagSigma*v[i][j];
            Sigma[i][j]=Sigma[i][j]+diagSigma*(v[i][j]*v[i][j]);//.....diagsigma
            mu[i][j]=mu[i][j]-rowmu*v[i][j];//rowmu
            rowe[i][j]=rowphi[j]-v[j][i]*Phi[i][j];
            v[i][j]=beta[i][j]*X[i][j]*rowe[j][i];
            S[i][j]=S[i][j]-diagSigma*v[i][j]*v[i][j];
            Q[i][j]=Q[i][j]-rowmu*v[i][j];
            alpha[idllh][jdllh]=alpha_;
          }
        }
        break;
      case 3:
        for(i=0;i<xrow;i++){
          for(j=0;j<xcol;j++){
            rowSigma=Sigma[i][jdllh];
            diagSigma=Sigma[iddh][jdllh];
            rowmu=mu[idllh][jdllh];
            Sigma[i][j]=Sigma[i][j]-(rowSigma*rowSigma)/diagSigma;
            mu[i][j]=mu[i][j]-rowmu*rowSigma/diagSigma;
            v[i][j]=beta[i][j]*X[i][j]*(Phi[i][j]*rowSigma);
            S[i][j]=S[i][j]+v[i][j]*v[i][j]/diagSigma;
            Q[i][j]=Q[i][j]+rowmu*v[i][j]/diagSigma;
            mu[idllh][jdllh]=0;
            Sigma[i][jdllh]=0;
            Sigma[idllh][j]=-;
            alpha[i][j]=0;     
          }
        }
        break;
    }
    for(i=0;i<xrow;i++){
      for(j=0;j<xcol;j++){
        Phi[i][j]=X[idllh][j];
      }
    } 
  }  
  model.w0=w0;
  model.w=mu;
  model.alpha=alpha;
  model.beta=beta;
}

int main(){
  Int i,j,n,m;
  n=3;
  m=3;
  MatDoub X(m,n);
  VecDoub t(n);
  form model;
  
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
    t[i]=rand()%10;
  } 
  rvmRegSeq(X,t,model);
}
