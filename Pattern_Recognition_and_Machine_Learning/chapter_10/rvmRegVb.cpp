/*
 * @file rvmRegVb.cpp
 * @Description Variational Bayesian inference for RVM regression
 * Input:
 *   X[dxn]: Data
 *   t[1xn]: Response
 *   prior: Prior parameter
 * Output:
 *   Model: Trained model strucutre
 *   Energy: Variational lower bound
 */

#include "nr3.h"

#include <csmath>
#include <iostream>

/* Input:
 *   X[dxn]: Data
 *   t[1xn]: Response
 *   prior: Prior parameter
 * Output:
 *   Model: Trained model strucutre
 *   Energy: Variational lower bound
 */
template <class D>
struct Model : mixGaussVb {  
  MatDoub a0=a;
  MatDoub b0=b;
  MatDoub c0=c;
  Model(MatDoub &a, MatDoub &b, MatDoub &c);
}

Model<D>::rvmRegVb(MatDoub a, MatDoub b, MatDoub c){};

void rvmRegVb(MatDoub X, VecDoub t, Model &prior, Model &posterior, Doub &energy){
  int i,j,m=X.nrows(),n=X.ncols(), 
  VecDoub idx(m);
  MatDoub dg(m,m),I(m,m,1), MatDoub XX(m,m),Xt(m,n);
  Doub xbar,tbar;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      xbar+=X[i][j];
    }
    tbar+=t[i];
  }
  xbar/=(m*n);
  tbar/=m;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]-=xbar;
    }
    t[i]-=tbar;
  }

  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      for(k=0;k<n;k++){
        XX[i][j]+=X[j][k]*X[k][j];
        Xt[j][m]+=X[j][k]*t[i];
      }
    }
  }  

  int iter,maxiter = 100;
  VecDoub energy(maxiter+1);
  Doub tol = 1*10^-8;
  posterior.a0=prior.a0+0.5;
  posterior.c0=prior.c0+0.5;
  Doub Ealpha = 1*10^-2;
  Doub Ebeta = 1*10^-2;
  MatDoub invS(m,m),U(m,m),Ew(m,m),Eq(m,m),KLw(m,m),w2(m,m),invU(m,m),dgS(m,m),KLalpha(m,m),e2(m,m),invUX(m,m),trXSX(m,m),d(m,m),KLbeta(m,m),Ewxbar(m,m);
  Doub const;
  for(iter=0;iter<maxiter;iter++){
    for(i=0;i<m,i++){
      for(j=0;j<m;j++){
        invS[i][j]=Ebeta[i][j]*XX[i][j]+Ealpha[i][j];
        U[i][j]=invS[i][j];
      }
    }
    cholesky(U);
    for(i=0;i<m;i++){ 
      for(j=0;j<m;j++){
        Ew[i][j]=Ebeta[i][j]*U[i][j]/U[j][i]*Xt[i][j];
        KLw[i][j]-=log(U[i][j]);
        w2[i][j]=Ew[i][j]*Ew[i][j];
        invU[i][j]=U[j][i];
        for(k=0;k<m;k++){
          dgS[i][j]+=invU[i][j]*invU[j][i];
        }
        posterior.b0=prior.b0+0.5*(w2[i][j]+dgS[i][j]);
        Ealpha[i][j]=posterior.a/posterior.b;
        KLalpha[i][j]-=posterior.a*(posterior.b);
        e2[i][j]+=(t[i]-Ew[j][i]*X[i][j])^2;
        invUX[i][j]=U[i][j]/X[i][j];
        for(k=0;k<m;k++){
          trXSX[i][j]+=invUX[j][m]*invUX[m][j];
        }
      }
    }
    for(i=0;i<m;i++){
      for(j=0;j<m;j++){
        posterior.d0[i][j]=prior.d0[i][j]+0.5*(e2[i][j]+trXSX[i][j]);
        Ebeta[i][j]=prior.c0[i][j]/prior.d0[i][j];
        KLbeta[i][j]=-prior.c0[i][j]*log(prior.d0[i][j]);
        energy[iter]+=KLalpha[i][j]+KLbeta[i][j]+KLw[i][j];
        if(energy[iter]-energy[iter-1] < tol*abs(energy[iter-1])) { break;}
      }
    } 
  }
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      const+=m*(gammaln(posterior.a0[i][j])-gammaln(prior.a[i][j])+prior.a0[i][j]*log(prior.b0[i][j]))+gammaln(posterior.c[i][j]-gammaln(prior.c0[i][j])+prior.c0[i][j]*log(prior.d0[i][j])+0.5*(m-n*log(2*pi));
    }
  }  
  for(i=1;i<iter;i++){
    energy+=energy[i]+const;
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      for(k=0;k<m;k++){
        Ewxbar[i][j]+=Ew[j][k]*xbar[k][j];
      }
    }
  }
  for(i=0;i<m;i++){
    for(j=0;j<m;j++){
      prior.w0[i][j]=tbar-Ewxbar[i][j];
    }
  }
  posterior.w0 = prior.w0;
  posterior.w0 = Ew;
  posterior.alpha = Ealpha;
  posterior.beta = Ebeta;
  posterior.a = prior.a;
  posterior.b = prior.b;
  posterior.c = prior.c;
  posterior.d = prior.d;
  posterior.xbar = prior.xbar;
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
  XXX(X,t,lambda);
}
