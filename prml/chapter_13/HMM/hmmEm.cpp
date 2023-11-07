/*
 * @file hmmEm.cpp
 * @Description EM algorithm to fit the parameters of Hmm model (aka Baum-Welch algorithm)
 * @Eqns #13.18: pi=gam(z)/sum[gam(z)]
 *       #13.19: A=sum[eta(z_{n-1},z_{n}]/sum[sum[z_{n-1},z_{n}]]
 *       #13.23: mu=sum[gam(z_{n})]*x_n/sum[gam(z)]
 *       #13.43: eta(z_{n-1},z_{n})=p(z_{n-1},z_{n}|X)
 *       #13.65: eta(z_{n-1},z_{n})=c_n*alpha(z_{n-1})*p(x|z)*p(z_{n}|z_{-1})*beta(z)
 *       #13.59: c_n*alpha(z_n)=p(x|z)*sum[alpha(z_{n-1})*p(z|z_{n-1}]
 *       #13.62: c_{n+1}*beta(z_n)=sum[beta(z_{n+1})*p(x_{n+1}|z_{n+1})**p(z_{n+1}|z_{n}]
 *       #13.64: gam(z)=alpha(z)*beta(z)
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 *
 *Output:
 *
*/

void XXX(MatDoub X, VecDoub t, int lambda){

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
