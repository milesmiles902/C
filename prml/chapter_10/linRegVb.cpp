/*
 * @file linRegVb.cpp
 * @Description Variational Bayesian inference for linear regression
 * @Eqns #10.94: a=a0+M/2;
 *       #10.101: S=(E[a]+beta*phi*phi)^-1
 *       #10.100: m=beta*S*phi*t;
 *       #10.95:  b=b0+0.5*E[w*w];
 *       #10.102: E[a]=a/b;
 */

#include "nr3.h"
#include "cholesky.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 *X[dxn]: Data
 *t[1xn]: Response
 *Output:
 *model: Trained model Structure
 *energy: Variational Lower Bound
*/

void linRegVb(MatDoub X, VecDoub t, Doub prior, linRegVb &model, Doub &energy){
  int i,j,d,n,maxiter=100;
  MatDoub XX(d,d),Xt(d,n),Ealpha(d,d,1*10^-4),Ebeta(d,d,1*10^-4),invS(d,d,1*10^-4),U(d,d),Ew(d,d),invU(d,d),trS(d,d),b(d,d),KLalpha(d,d),invUX(d,d),TRXSX(d,d),d(d,d),KLbeta(d,d),Ebeta(d,d),value(d,d);
  Doub xbar,tbar,a,c,a0,b0,c0,d0,KLw,tol=1*10^-8;
  try{
    a0=prior.a;
    b0=prior.b;
    c0=prior.c;
    d0=prior.d;
  } catch{
    a0=1*10^-4;
    b0=1*10^-4;
    c0=1*10^-4;
    d0=1*10^-4;
  }
  for(i=0;i<n;i++){
    for(j=0;j<d;j++){
      xbar+=X[j][i];
    }
    tbar+=t[i];
  }
  xbar/=(d*n);
  tbar/=n;
  for(i=0;i<n;i++){
    for(j=0;j<d;j++){
      X[j][i]-=xbar;
    }
    t[i]-=tbar;
  }
  
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      for(k=0;k<d;k++){
        XX[i][j]=X[k][j]*X[j][k];
      }
    }
  }
  a=a0+d/2;
  c=c0+n/2;
  for(iter=1;iteR<maxiter;i++){
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        invS[i][j]=Ealpha[i][i]+Ebeta[i][j]*XX[i][j];
      }
    }
    cholesky(invS);
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        Ew[i][j]=Ebeta[i][j]*(U[i][j]/(U[j][i]/Xt[i]));
      }
      KLw-=log(U[i][i])
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;k++){
          w2[i][j]+=Ew[j][k]*Ew[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        invU[i][j]=U[j][i];
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;j++){
          trS[i][j]+=invU[k][j]*invU[j][k];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        b[i][j]=b0+0.5*(w2[i][j]+trS[i][j]);
        Ealpha[i][j]=a[i][j]/b[i][j];
        KLalpha[i][j]=-a[i][j]*log(b[i][j]);
        invUX[i][j]=U[j][i]/X[i][j];
        for(k=0;k<d;k++){
          e2+=pow((t[i]-Ew[j][k]*X[k][i]),2);
        }
      }
    }
    
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;k++){
          trXSX[i][j]+=invUX[j][k]*invUX[k][j];
        }
      }
    }
   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       d[i][j]=d0+0.5*(e2[i][j]+trXSX[i][j]);
       Ebeta[i][j]=c[i][j]/d[i][j];
       KLbeta[i][j]=-c[i][j]*log(d[i][j]);
       energy[iter]=Kalpha[i][j]+KLbeta[i][j]+Klw[i][j];
     }
   }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      value[i][j]=gammaln(a[i][j])-gammaln(a0)+gammaln(c[i][j])-gammaln(c0)+a0*log(b0)+c0*log(d0)+0.5*(d-n)*log(2*PI();
  for(i=0;i<iter;i++){
    energy[iter]+=;   //Review Material
  }
  model.w0=w0;
  model.w=Ew;
  model.alpha=Ealpha;
  model.beta=Ebeta;
  model.a=a;
  model.b=b;
  model.c=c;
  model.d=d;
  model.xbar=xbar;
    }
  } 
}
