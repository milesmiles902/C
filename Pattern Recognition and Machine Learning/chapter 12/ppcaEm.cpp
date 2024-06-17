/*
 * @file ppcaEm.cpp
 * @Description Perform EM algorithm to maximize likelihood of probabilistic PCA model
 * @Eqns #12.43: lnp(X|mu,W,sig^2)=sum(ln(p(xn|W,mu,sig^2)))=-N*D/2ln(2pi)-N/2ln|C|-0.5*sum(x-mu)C^-1(x-mu)
 *       #12.44: lnp(X|W,mu,sig^2)=-N/2(Dln(2pi)+ln|C|+Tr(S/C)
 *       #12.54: E[z]=W/M(x-xbar);
 *       #12.55: E[zz]=sig^2/M+E[z]*E[z]
 *       #12.56: W=[sum(x-xbar)*E[z]]/[sum(E[zz])]
 *       #12.57: sig^2=(1/ND)*sum(|x-xbar|^2-2E[z]W(x-xbar)+Tr(E[zz]W*W))
 */

#include "nr3.h"
#include "cholesky.h"
#include <csmath>
#include <iostream>
#include <cstdlib>

/*
 *Input:
 * X[dxn]: Data Matrix
 * m: Dimension of Target Space
 *Output:
 * W[dxm]: Weight Matrix
 * mu[dx1]: Mean Vector
 * beta: precision vector (inverse of variance)
 * llh: loglikelihood
*/

tor(MatDoub A, MatDoub &temp, int p, int q, int n){
  int i,j,row,col;
  for(row=0;row<n;row++){
    for(col=0;col<n;col++){
      if(col!=m&&col!=q){
        temp[i][j++]=A[row][col];
        if(j==n-1){
          j=0;
          i++;
        }
      }
    }
  }
}

int determinant(MatDoub A,int n){
  int f,D=0;
  MatDoub temp(n,n);
  if(n==1)
    return A[0][0];
  int sign=1;
  for(f=0;f<n;f++){
    getCofactor(A,temp,0,f,n);
    D+=sign*A[0][f]*determinant(temp,n-1);
    sign=-sign;
  }
  return D;
}

int adjoint(MatDoub A, MatDoub adj,int n){
  int i,j,n=A.nrows(), sign = 1;
  MatDoub temp(n,n);
  if(n==1){
    adj[0][0]=1;
    return;
  }
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      getCofactor(A,temp,i,j,n);
      sign=((i+j)%2 == 0) ? 1 : -1;
      adj[j][i]=sign*determinant(temp,n-1);
    }
  }
}

MatDoub inverse(MatDoub A){
  int i,j,m=A.nrows(),n=A.ncols();
  MatDoub inv(m,n),adj(m,n);
  int det = determinant(A);
  adj=adjoint(A);
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      inv[i][j]=adj[i][j]/det;
    }
  }
  return inv;
}

void ppcaEM(MatDoub X, int m, MatDoub &W, VecDoub &mu, Doub &beta, Doub &llh){
  int i,j,k,iter,d=X.nrows(),n=X.ncols(),maxiter=500;
  MatDoub Xbar(d,d),r(d,d),XX(d,d),M(d,d),W(d,d,rand()),WX(d,d),T(d,d),TT(d,d),U(d,d),EZ(d,d),V(d,d),Ezz(d,d),WR(d,d),s(d,d,1/rand()),sInv(d,d),invU(d,d),EZWX(d,d),WRWR(d,d);
  VecDoub llh(maxiter);
  Doub mu,trInvCS,tol=0.0001;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      mu+=X[i][j];
    }
  }
  mu/=(d*n);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      Xbar[i][j]=X[i][j]-mu;
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        r[i][j]+=X[j][k]*X[k][j];
      }
    }
  }
  for(iter=2;iter<maxiter){
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          M[i][j]+=W[j][k]*W[k][j]
          if(k=0) M[i][j]+=s[i][j];
        }
      }
    }
    U=cholesky(M);
          
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          WX[i][j]+=W[j][k]*W[k][j];
        }
        if(i==j) logdetC+=2*log(U[i][j])+(d-m)*log(d-m)*log(s[i][j]);
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          T[i][j]+=U[k][j]/W[j][k];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<n;k++){
          TT[i][j]+=T[j][k]*T[k][j]; 
        }
      }
    }
    sInv=inverse(s);
    for(i=0;i<d;i++){
      for(j=0;j<n;j++){
        trInvCS+=(r[i][j]-TT[i][j])*n*sInv[i][j];
      }
    }
    llh[iter]=-n*(d*log(2*pi)+logdetC+trInvCS)/2;
    if(abs(llh[iter]-llh[iter-1])<tol*abs(llh[iter-1])) return;
    if(i=0;i<d;i++){
      if(j=0;j<d;j++){
        EZ[i][j]=M[i][j]/WX[i][j];
      }
    }   
    V=inverse(U);

    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;j++){
          Ezz[i][j]+=n*s[i][j]*(V[j][k]*V[k][j])+EZ[j][k]*EZ[k][j];
        }
      }
    }
    cholesky(Ezz);
    U=Ezz;
    invU=inverse(U);
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;j<d;k++){
          W[i][j]+=((X[j][k]*Ez[k][j])*invU[j][k])*invU[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;k++){
          WR[i][j]+=W[j][k]*U[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        for(k=0;k<d;k++){
          EZWX[i][j]+=EZ[j][k]*WX[k][j];
          WRWR[i][j]+=WR[j][k]*WR[k][j];
        }
      }
    }
    for(i=0;i<d;i++){
      for(j=0;j<d;j++){
        s[i][j]=(r[i][j]-2*EZWX[i][j])+WRWR[i][j]/(n*d);
      }
    }
  }
  beta=inverse(s);
}
