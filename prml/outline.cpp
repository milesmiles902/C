/*
 * @file .cpp
 * @Description
 * @Eqns #
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
