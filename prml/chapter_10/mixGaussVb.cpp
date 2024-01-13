/*
 * @file mixGaussVb.cpp
 * @Description Variational Bayesian inference for Gaussian mixture
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[dxn]: Data Matrix
 * m[1xn]: Model Structure
 *Output:
 * label[1xn]: Cluster Label
 * Model: Model Structure
 * L: Variational Lower Bound
*/

int Xmean,d;

Doub psi(int x, Doub alpha){
    //Elogpi[i]=psi(0,alpha[i])-psi(0,sumalpha);
}

Doub logMvGamma(MatDoub X, int d){
  //Logarithm of Multivariance Gamma Function
  //Gamma(x)=pi^(d(d-1)/4) * PI_i=1 to d Gamma(x+(1-j)/2);
  //logGamma(x)=(d(d-1)/4)*log(pi)+sum_i=1 to d log(Gamma(x+(1-j)/2));
  int i,j,d=X.nrows(),n=X.ncols();
  MatDoub Y(d,n);
  VecDoub gamX(d);
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      gamX[i]+=gammaln(X[i][j]+(1-d/2));
    }
  }
  
}

template <class D>
struct Model : mixGaussVb {
  typedef D Dtype;
  int n,k;
  MatDoub alpha(n,k);
  MatDoub kappa(n,k);
  MatDoub m(n,k);
  MatDoub v(n,k);
  MatDoub M(n,k);
  MatDoub R(n,k);
  Mat3DDoub U(n,k,k);

  Model(MatDoub &alpha, MatDoub &kappa, MatDoub &m, int &v,int &M,MatDoub &R); 
  void init(MatDoub X, int m, mixGaussVb &prior){};
  void maximize(MatDoub X, mixGaussVb &posterior, mixGaussVb prior){};  
  void expect(MatDoub X, mixGaussVb model){};
  MatDoub lowerbound(MatDoub X, mixGaussVb posterior, mixGaussVb prior){};
}

template <class D>
Model<D>::mixGaussVb(MatDoub alpha, MatDoub kappa,MatDoub m,int v, int M, MatDoub R)
  : Model(alpha=1,kappa=1,m=Xmean,v=d+1,M=1){};

template <class D>
void Model<D>::init(MatDoub X, int m, mixGaussVb &prior){
  int i,j,m,n;
  m=X.nrows();
  n=X.ncols();
  if(m==1){
    return;
  } else if(m>1){
    for(i=0;i<m;i++){
      for(j=0;j<n;j++){
        prior.R[i][j]=rand();
      }
    }
  }
  else {
    std::cout << "Error: The m-input is invalid." << std::endl;
  }
}

template <class D>
void Model<D>::maximize(MatDoub X, mixGaussVb &posterior, mixGaussVb prior){
  int i,j,nk;
  MatDoub alpha0=prior.alpha;
  MatDoub kappa0=prior.kappa;
  MatDoub m0 = prior.m;
  int v0 = prior.v;
  MatDoub M0 = prior.M0;
  MatDoub R = prior.R;
  int n=R.nrows();
  int k=R.ncols();
  for(i=0;i<n;i++){
    for(j=0;j<k;j++){
      nk+=R[i][j];
    }
  }
  nk/=(n*k);
  MatDoub alpha = alpha0+nk;
  MatDoub kappa = kappa0+nk;
  int v = v0 + nk;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      m[i][j]=(kappa0*m0+X[i][j]*R[i][j])/kappa;
    }
  }
  Mat3DDoub U(n,n,k,0);
  VecDoub logW(k,0);
  MatDoub r(k,n);
  for(i=0;i<n;i++){
    for(j=0;j<k;k++){
      r[j][k]=sqrt(R[i][j]);
    }
  } 
  MatDoub Xm(n,k),m0m(n,k);
  for(i=0;i<n;i++){
    for(j=0;j<k;i++){
      Xm[i][j]=(X[i][j]-m[i][j])*r[i][j];
      m0m[i][j]=m0[i][j]-m[i][j];
      M[i][j]=M0[i][j]+Xm[i][j]*Xm[j][i]+kappa0[i][j]*(m0m[i][j]*m0m[j][i]);
      choleksy(M);
      if(i==j){
        logW[j]+=-2*log(M[i][j]);
      }
    }
  }
};

template <class D>
int Model<D>::expect(MatDoub X, mixGaussVb model){
  int i,j,d,k;
  d=X.nrows();
  k=X.ncols();
  MatDoub alpha(d,k) = model.alpha;
  MatDoub kappa(d,k) = model.kappa;
  MatDoub m(d,k) = model.m;
  MatDoub v(d,k) = model.v;
  Mat3DDoub U(d,k,k,0) = model.U;
  MatDoub logW(d,k) = model.logW;
  VecDoub N(k);
  MatDoub EQ(d,k,0);
  Mat3DDoub Q(d,d,k);
  MatDoub ElogLambda(d,k),Elogpi(d,k),logRho(d,k),logR(d,k),R(d,k);
  Doub sumalpha;
  for(i=0;i<k;i++){
    //Transpose 3-D Matrix   
  }
  for(i=0;i<d;i++){
    for(j=0;j<k;j++){
      ElogLambda+=psi(0,0.5*(v[i][j]+1-i)i)+i*log(2)+logW[i][j];
      sumalpha+=alpha[i][j];
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<k;j++){
      Elogpi=psi(0,alpha)-psi(0,sumalpha); 
      logRho[i][j]=-0.5*EQ[i][j]-ElogLambda-d*log(2*PI())+Elogpi;
      logR[i][j]=logRho[i][j]-logsumexp //Is the second parameter columns?
      R[i][j]=power(e,logR[i][j]);
    }
  }
  model.logR=logR;
  model.R=R;
};

template <class D>
MatDoub Model<D>::lowerbound(MatDoub X, mixGaussVb posterior, mixGaussVb prior){
  int i,j,k,d,n;
  d=X.nrows();
  n=X.ncols();
  MatDoub alpha0(d,n)=prior.alpha;
  MatDoub kappa0(d,n)=prior.kappa;
  MatDoub v0(d,n)=prior.v;
  MatDoub logW0(d,n)=prior.logW;
  MatDoub alpha(d,n)=posterior.alpha;
  MatDoub kappa(d,n)=posterior.kappa;
  MatDoub v(d,n)=posterior.v;
  MatDoub logW(d,n)=posterior.logW;
  MatDoub R(d,n)=posteror.R;
  MatDoub logR(d,n)=posterior.logR;
  MatDoub Epz(d,n,0);
  MatDoub Eqz(d,d);
  MatDoub logCalpha0(d,n);
  MatDoub Eppi(d,n);
  MatDoub Eqpi(d,n);
  MatDoub sumalpha(d,n);
  MatDoub sumgamalpha(d,n);
  MatDoub Eqmu(d,n);
  MatDoub Eqmu(d,n);
  VecDoub k(n);
  MatDoub EpLambda(d,n);

  for(i=0;i<d;i++){
   for(j=0;j<n;j++);
     for(k=0;k<d;j++){
       Eqz[i][j]+=R[j][k]*logR[k][j];
       logCalpha0[i][j]=gammaln(n*alpha0[i][j])-n*gammaln(alpha0[i][j]);
       Eppi[i][j]=logCalpha0[j][k];
       sumalpha[i][j]+=alpha[i][j];
       sumgamalpha[i][j]+=gammaln(alpha[i][j]);
     } 
   }
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      logCalpha[i][j]=gammaln(sumalpha[i][j])-sumgamalpha;
      Eqpi[i][j]=logCalpha[i][j];
      Epmu[i][j]=0.5*d*n*log(kappa0[i][j]);
      Eqmu[i][j]=0.5*d*n*log(kappa[i][j]);
      logB0[i][j]=-0.5*v0[i][j]*(logW0[i][j]+d*log(2))-logMvGamma(0.5*v0[i][j],d);
      EpLambda[i][j]=n*logB0[i][j];
      logB[i][j]=-0.5*v[i][j].*(logW[i][j]+log(2))-logMvGamma(0.5*v[i][j],d);
      EqLambda+=logB[i][j];
      Epx[i][j]=-0.5*d*n*log(2*pi);
      L[i][j]=Epz[i][j]-Eqz[i][j]+Eppi[i][j]-Eqpi[i][j]+Epmu[i][j]+EpLambda[i][j]-EqLambda[i][j]+Epx[i][j]; 
    }
  }
  return L;
};

int main(){
  Int i,j,d,n;
  d=3;
  n=3;
  MatDoub X(d,n);
   
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
      Xmean+=X[i][j];
    }
  } 
  Xmean/=d*n;
  model(alpha,kappa,m,v,M,R);
  model.maximize();
  lowerBound();
}
