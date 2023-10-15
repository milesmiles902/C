/*
 * @file .cpp
 * @Description knPoly
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * X[mxn]: Data Matrix
 * Y[mxn]: Data Matrix
 * o: Order of Polynomial
 * c: Constant shift
 *Output:
 * K[nxn]: Kernel Matrix
*/

void knPoly(MatDoub X, MatDoub Y, Doub o, Doub c){
  int i,j,k,xrow=X.nrow(),xcol=X.ncol();
  MatDoub K(xrow,xcol);
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      for(k=0;k<xrow;k++){
        K[i][j]+=X[j][k]*Y[k][j];
      }
    }
  }
}

int main(){
  Int i,j,n,m,k;
  n=3;
  m=3;
  k=3;
  MatDoub X(m,n), Y(m,n);
  Doub o,c;
  o=2;
  c=1;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
      Y[i][j]=rand()%10;
    }
  } 
  knPoly(X,Y,o,c);
}
