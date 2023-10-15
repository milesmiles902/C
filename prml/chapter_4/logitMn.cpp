/*
 * @file: .cpp
 * @Description: Multinomial regression for multiclass problem (Multinomial likelihood)
 * @Eqns: #4.92-4.105
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X(dxn) - Data Matrix
 * t(1xn) - label (1-k)
 *Output:
 * std::cout - model parameters
 * std::cout - graph
*/
void logitMn(X,T,lambda){
}

void newtonRaphson(MatDoub X, VecDoub t, int lambda){
  int h,i,j,k,d,n,dk,iter;
  d=X.nrows();
  n=X.nrows();
  k=t.size();
  
  Doub tol,maxiter, TlogY, Y;
  tol=1e-4;
  maxiter=100;
  llh[0]=0;
  dk=d*k;
  
  VecDoub iter(maxiter);
  MatDoub dg(dk,dk), T(k,n), W(d,k), WW(d,d), HT(d,k), A(k,n), Y(k,n), YminutT(k,n), G(d,k);
  
  for(iter=1;iter<maxiter;iter++){
    for(h=0;h<k;h++){
      for(i=0;i<k;i++){
        for(j=0;j<n;j++){
          A[h][i]=W[h][j]*X[j][i];
        }
      }
    }
    for(h=0;h<k;h++){
      for(i=0;i<n;i++){      
        logsumexp+=pow(e,A[i][j])
      }
    } logsumexp=log(logsumexp);
    for(h=0;h<k;h++){
      for(i=0;i<n;i++){ 
        T[i][j]=0;
        logY[i][j]=A[h][j]-logsumexp;
        TlogY+=T[i][j]*logY[i][j];
      }
    }  
    for(h=0;h<d;h++){
      for(i=0;i<d;i++){
        for(j=0;j<k;j++){
          WW[h][i]=W[h][j]*W[j][i];
        }
      }
    }
    for(h=0;h<d;h++){
      for(i=0;i<d;i++){
        llh[iter]+=TlogY-0.5*lambda*WW[i][j];
      }
    } if(abs(llh[iter]-llh[iter-1]) < tol) break;
    for(h=0;h<k;h++){
      for(i=0;i<n;n++){
        Y[i][j]=pow(e,logY[i][j]);
      }
    }
    for(h=0;h<k;h++){
      for(i=0;i<k;i++){
        r[i][j]=Y[i][j]*(1-Y[i][j]);
        for(j=0;j<n;j++){
          HT[h][j]=(X[h][j]-r[h][j])*X[j][i];
          YminusT[h][j]=Y[h][j]-T[h][j];
        }
      }
    }
    for(h=0;h<d;h++){
      for(i=0;i<d;i++){
        for(j=0;j<k;j++){
          G[h][j]=X[h][j]*YminusT[j][i]+lambda*W[h][j];
          W[h][j]=W[h][j]-H[h][j]/G[h][j];
        }
      }
    } 
  }
}



  a_k=w*phi;
  p(c|phi)=y(phi)=exp(a_k)/(sum(exp(a_k)));
  E(w1..wk)=-lnp(T|w1...wk)=-sum(sum(tn*lny));
  del.delE=-sum(y(I-y)phi*phi);
  
  delE(W)=sum(y-t)phi=PHI(Y-T);
  w(new)=w(old)-HdelE
  
}

int main(){
  Int i,j,n,m,lamda;
  n=3;
  m=3;
  MatDoub X(m,n);
  VecDoub t(n);
  
  lambda=2;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
    t[i]=rand()%10;
  } 
  logitMn(X,t,lambda);
}
