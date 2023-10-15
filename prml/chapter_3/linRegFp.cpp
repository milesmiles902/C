/*
 * @file .cpp
 * @description Fit empirical Bayesian linear model with Mackay fixed point method
 * @Input
 *   X: d x n data
 *   t: 1 x n response
 *   alpha: prior parameter
 *   beta: prior parameter
 * @Output
 *   std::cout *variables*
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "nr3.h"
#include "cholesky.h"

void printMatDoub(MatDoub X){
  for(int i=0;i<X.nrows();i++){
    for(int j=0;j<X.ncols();j++){
      std::cout << X[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

Doub GaussianErrDist(Doub mu, double sig){
  int z0=0,z1=0;
  const Doub epsilon = numeric_limits<Doub>::min(); 
  Bool gen;
  gen=!gen;
  if(!gen)
    return z1*sig+mu;
  Doub u1,u2;
  do{
    u1=rand()*(1.0/RAND_MAX);
    u2=rand()*(1.0/RAND_MAX);
  } while (u1<=epsilon);
  z0=sqrt(-2.0*log(u1))*cos(2.0*M_PI*u2);
  //z1=sqrt(-2.0*log(u1))*sin(two_pi*u2);
  return z0*sig+mu;
}

Doub uniform(Doub min, Doub max){
  return (min+(rand()%static_cast<int>(max-min+1)));
}
void linRegFP(MatDoub X, VecDoub t, int d, int n, MatDoub alpha, MatDoub beta){
  int i,j,k,iter,maxiter;
  Doub xbar,tbar,tol,exp,logdetA,w0;  
  MatDoub XX(d,d),Xt(d,n),A(d,d),U(d,d),m(d,d),m2(d,n),V(d,d),trS(d,d),gamma(d,d);
  VecDoub llh(200); 
  maxiter=200;
  tol=pow(10,-4);

  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      xbar+=X[i][j];
    }
    tbar+=t[i];
  }
  xbar=xbar/(d*n);
  tbar=tbar/n;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      X[i][j]=X[i][j]-xbar;
    }
    t[i]=t[i]-tbar;
  }
  std::cout << "Xdif" << std::endl;
  printMatDoub(X);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      for(k=0;k<n;k++){
        XX[i][j]+=X[i][k]*X[j][k];
      }
      Xt[i][j]=X[i][j]*t[i];
    }
  }

  for(iter=1;iter<maxiter;maxiter++){
  
    std::cout << "Xt" << std::endl;
    printMatDoub(Xt);  
    std::cout << "XX" << std::endl;
    printMatDoub(XX); 
      for(i=0;i<d;i++){
        for(j=0;j<d;j++){
          for(k=0;k<d;k++){
            A[i][j]+=beta[i][k]*XX[k][j];
          }
          A[i][j]+=alpha[i][j];
          U[i][j]=A[i][j];
        }
      }
     std::cout << "U:" << std::endl;
     printMatDoub(U);
     std::cout << "A:" << std::endl;
     printMatDoub(A);
     Cholesky myCholesky(A);
     
     for(i=0;i<d;i++){
       for(j=0;j<d;j++){
         for(k=0;k<n;k++){
           m[i][j]=beta[i][j]*U[i][j]/(U[k][j]/Xt[i][j]);
          }
       }
     }
    
     for(i=0;i<d;i++){
       for(j=0;j<n;j++){
         for(k=0;k<n;k++){
           m2[i][j]+=m[i][j]*m[k][j];
         }
       }
     }
     for(i=0;i<d;i++){
       for(j=0;j<n;j++){
         for(k=0;k<d;k++){
           exp+=pow((t[i]-X[i][j]*m[k][j]),2);
         }
       }
     }

     for(i=0;i<d;i++){
       logdetA+=2*log(U[i][i]);
     }
      
     for(j=0;j<n;j++){
       std::cout << "alpha[" << iter << "][" << j << "]" << alpha[iter][j] << std::endl;
       std::cout << "beta[" << iter<< "][" << j << "]" << beta[iter][j] << std::endl;
       std::cout << "m2[" << iter << "][" << j << "]" << m2[iter][j] << std::endl;
       llh[iter]=0.5*(d*log(alpha[iter][j])+n*log(beta[iter][j])-alpha[iter][j]*m2[iter][j]*exp-logdetA-n*log(2*M_PI));
       std::cout << "abs(llh[iter]): " << abs(llh[iter]) << std::endl;
       std::cout << "llh[iter-1]: " << llh[iter-1] << std::endl;
       std::cout << "tol*abs(llh[iter-1])" << tol*llh[iter-1];
     }
     if (abs(llh[iter]-llh[iter-1] < tol*abs(llh[iter-1]))) break;
   }
   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       V[i][j]=U[j][i];
     }
   }

   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       for(k=0;k<d;k++){
         trS[i][j]=V[i][j]*V[k][j];
       }
     }
   }

   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       gamma[i][j]=d-alpha[i][j]*trS[i][j];
       alpha[i][j]=gamma[i][j]/m2[i][j];
       beta[i][j]=(n-gamma[i][j])/exp;
     }
   }
   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       w0+=tbar-m[i][j]*xbar;
     }
   }
  std::cout << "Data: " << std::endl;
  for(i=0;i<d;i++){
    for(j=0;j<n;j++){
      std::cout << X[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Data mean: " << xbar << std::endl;

  std::cout << "Model system: " << std::endl;
  for(i=0;i<n;i++){
    std::cout << t[i];
  }

  std::cout << "Model mean: " << tbar << std::endl;

  std::cout << "Model (w0): " << w0 << std::endl;
  std::cout << "Model (alpha): " << std::endl;
  printMatDoub(alpha);
  std::cout << "Model (beta): " <<  std::endl;
  printMatDoub(beta);
  std::cout << "Model (U): " << std::endl;
  printMatDoub(U);


} 

int main(){
   int i,j,d,n;
   MatDoub X(2,2),alpha(2,2),beta(2,2);
   VecDoub t(1);
   Doub var = GaussianErrDist(0,25);
   d=X.nrows();
   n=X.ncols();
   for(i=0;i<d;i++){
     for(j=0;j<d;j++){
       X[0][j]=pow(uniform(10,20),j);
       beta[i][j]=i+1;
       alpha[i][j]=i+1;
     }
     t[i]=rand()%5;
   }
   std::cout << "X" << std::endl;
   printMatDoub(X); 
   std::cout << "alpha" << std::endl;
   printMatDoub(alpha); 
   std::cout << "beta" << std::endl;
   printMatDoub(beta);
   linRegFP(X,t,d,n,alpha,beta);
}
